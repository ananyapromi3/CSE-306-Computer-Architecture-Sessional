// CONTROL
#define F_CPU 1000000
#include <util/delay.h>
#include <avr/io.h>
unsigned char memArr[32];
int controlMem[16] = {0x001, 0x110, 0xb04, 0x006, 0x304, 0x406, 0x704, 0x104,
                      0x806, 0xd04, 0x240, 0x206, 0x606, 0x12c, 0x280, 0x504};
int main(void)
{
  MCUCSR |= (1 << JTD);
  MCUCSR |= (1 << JTD);
  DDRA = 0xFF;
  DDRB = 0x00;
  DDRD = 0x00;
  DDRC = 0xFF;
  PORTA = 0b11111111;
  PORTB = 0b00000000;
  PORTD = 0b00000000;
  PORTC = 0b00001111;
  while (1)
  {
    unsigned int opcode = PINB & 0b00001111;
    int controlOut = controlMem[opcode] % 256;
    PORTA = controlOut & 0xFF;
    controlOut = controlMem[opcode] >> 4;
    PORTC = controlOut & 0b11110000;
    _delay_ms(10);
  }
}
