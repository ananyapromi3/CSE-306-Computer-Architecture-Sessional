// // REGISTER FILE
// #include <avr/io.h>
// #define F_CPU 1000000
// #include <util/delay.h>
// unsigned char regArr[16];
// // 0 -> zero
// // 1 -> t0
// // 2 -> t1
// // 3 -> t2
// // 4 -> t3
// // 5 -> t4
// // 6 -> sp
// int main(void)
// {
//   MCUCSR |= (1 << JTD);
//   MCUCSR |= (1 << JTD);
//   DDRA = 0XFF;
//   DDRB = 0x00;
//   DDRC = 0xFF;
//   DDRD = 0x00;
//   for (int i = 0; i < 16; i++)
//     regArr[i] = 0;
//   int currclk = 0;
//   int regwrite;
//   int reset;
//   int prevclk = 0;
//   int muxOut;
//   int reg1;
//   int reg2;
//   int regWrite;
//   int writeData;
//   while (1)
//   {
//     reg1 = PIND % 16;
//     muxOut = PINB % 16;
//     reg2 = ((PINB & 0b11110000) >> 4) % 16;
//     regWrite = (PIND & 0b00010000) >> 4;
//     reset = (PIND & 0b00100000) >> 5;
//     prevclk = currclk;
//     currclk = (PIND & 0b01000000) >> 6;
//     writeData = (PINC & 0xF0) >> 4;
//     PORTA = (regArr[0]);
//     PORTA = ((regArr[reg2] << 4) | regArr[reg1] % 16) % 256;
//     if (prevclk == 0 && currclk == 1 && regwrite == 1)
//       regArr[muxOut] = writeData;
//     if (reset == 1)
//       for (int i = 0; i < 16; i++)
//         regArr[i] = 0;
//   }
//   _delay_ms(10);
// }

// // INPUT
// // PINB[0-3] - MUX1output
// // PINB[4-7] - Reg2Addr
// // PIND[0-3] - Reg1Addr
// // PIND4 - regWrite
// // PIND5 - reset
// // PIND - CLK
// // OUTPUT
// // PINA[0-3] - ReadData1[0-3]
// // PINA[3-7] - ReadData2[0-3]
// // PINC[4-7] - WriteData[0-3]

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

unsigned char regArr[16];
// 0 -> zero lol
// 1 -> t0
// 2 -> t1
// 3 -> t2
// 4 -> t3
// 5 -> t4
// 6 -> sp

int main(void)
{
  MCUCSR |= (1 << JTD);
  MCUCSR |= (1 << JTD);

  DDRA = 0XFF;
  DDRB = 0x00;
  DDRC = 0x0F;
  DDRD = 0x00;

  for (int i = 1; i < 16; i++)
  {
    regArr[i] = 15 - i;
  }
  regArr[6] = 0;
  int currclk = 0;
  int regwrite;
  int showreg = 0;
  int reset;
  int prevclk = 0;

  while (1)
  {
    int b = PINB;
    int muxout = b % 16;
    int reg2 = b >> 4;
    int d = PIND;
    int reg1 = d % 16;
    int flg = PINC;
    prevclk = currclk;
    currclk = (d & 0b01000000) >> 6;
    regwrite = (d & 0b00010000) >> 4;
    reset = (d & 0b00100000) >> 5;
    int wb = flg >> 4;
    if (showreg == 1)
    {
      int in1 = PIND >> 4;
      PORTA = regArr[in1];
    }
    else
    {
      if (reset == 1)
      {
        for (int i = 0; i < 16; i++)
        {
          regArr[i] = 0;
        }
      }
      else
      {
        PORTA = ((regArr[reg2] << 4) | regArr[reg1] % 16) % 256;
        if (prevclk == 0 && currclk == 1 && regwrite)
        {
          regArr[muxout] = wb;
          PORTC = regArr[muxout] % 16;
        }
      }
    }
    _delay_ms(10);
  }
}
// Register File