// ALU
#define F_CPU 1000000
#include <util/delay.h>
#include <avr/io.h>
// 0 - add
// 1 - sub
// 2 - or
// 3 - and
// 4 - nor
// 5 - sl
// 6 - sr
// 7 - zero
unsigned char memArr[32];
int main(void)
{
  MCUCSR |= (1 << JTD);
  MCUCSR |= (1 << JTD);
  DDRA = 0XFF;
  DDRB = 0x00;
  DDRD = 0x00;
  PORTB = 0x00;
  PORTD = 0x00;
  int reg1;
  int reg2;
  int ALUout = 0;
  int ALUop;
  int beq_flag = 0;
  int bneq_flag = 0;
  int bsel = 0;
  while (1)
  {
    ALUop = PIND % 8;
    reg1 = PINB % 16;
    reg2 = ((PINB & 0b11110000) >> 4);
    beq_flag = (PIND & 0b00001000) >> 3;
    bneq_flag = (PIND & 0b00010000) >> 4;
    if (ALUop == 0)
      ALUout = (reg1 + reg2) % 16;
    else if (ALUop == 1)
      ALUout = (reg1 - reg2 + 16) % 16;
    else if (ALUop == 3)
      ALUout = (reg1 & reg2) % 16;
    else if (ALUop == 2)
      ALUout = (reg1 | reg2) % 16;
    else if (ALUop == 4)
      ALUout = (~(reg1 | reg2)) % 16;
    else if (ALUop == 5)
      ALUout = (reg1 << reg2) % 16;
    else if (ALUop == 6)
      ALUout = (reg1 >> reg2) % 16;
    else
      ALUout = 0;
    if (ALUout % 16 == 0 && beq_flag == 1)
      bsel = 1;
    else if (ALUout % 16 == 0 && beq_flag == 0)
      bsel = 0;
    else if (ALUout % 16 != 0 && bneq_flag == 1)
      bsel = 1;
    else if (ALUout % 16 != 0 && bneq_flag == 0)
      bsel = 0;
    PORTA = (ALUout & 0b00001111) | (bsel << 4);
    _delay_ms(10);
  }
}
