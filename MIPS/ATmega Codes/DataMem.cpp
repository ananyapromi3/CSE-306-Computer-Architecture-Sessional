// DATA MEMORY
#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
unsigned char memArr[16];
int main(void)
{
  MCUCSR |= (1 << JTD);
  MCUCSR |= (1 << JTD);
  DDRA = 0xFF;
  DDRB = 0x00;
  DDRC = 0x00;
  DDRD = 0x0F;
  int clk_cur = 0;
  int clk_prev = 0;
  int memRead;
  int readData;
  int memWrite;
  int writeData;
  int addr;
  int dataout;
  int mem2Reg;
  for (int i = 0; i < 16; i++)
    memArr[i] = 0;
  while (1)
  {
    writeData = ((PINB & 0b11110000) >> 4) % 16;
    addr = PINB % 16;
    clk_prev = clk_cur;
    clk_cur = (PIND & 0b10000000) >> 7;
    mem2Reg = (PIND & 0b01000000) >> 6;
    memRead = (PIND & 0b00100000) >> 5;
    memWrite = (PIND & 0b00010000) >> 4;
    dataout = memArr[addr];
    if (mem2Reg == 0)
      PORTA = addr;
    else
      PORTA = memArr[addr];
    if (clk_prev == 0 && clk_cur == 1 && memWrite == 1)
      memArr[addr] = writeData;
    _delay_ms(10);
  }
}
