#include <ShiftRegister74HC595.h>

#define SDI1 7
#define SCLK1 6
#define LOAD1 5

#define R1 4
#define Y1 3
#define G1 2

#define SDI2 13
#define SCLK2 12
#define LOAD2 11

#define R2 10
#define Y2 9
#define G2 8

#define DIGITS 2

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595<DIGITS> sr1(SDI1, SCLK1, LOAD1);
ShiftRegister74HC595<DIGITS> sr2(SDI2, SCLK2, LOAD2);


int digit1, digit2;
uint8_t  digits[] = { B11000000, //0
                      B11111001, //1 
                      B10100100, //2
                      B10110000, //3 
                      B10011001, //4
                      B10010010, //5
                      B10000010, //6 
                      B11111000, //7
                      B10000000, //8
                      B10010000  //9
                    };
                        
void setup() {
  pinMode(R1, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(G1, OUTPUT);

  pinMode(R2, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(G2, OUTPUT);
}

void loop() {
  /*  1 - red 30s
      2 - gre 25s */
  digitalWrite(R1, HIGH);
  digitalWrite(G2, HIGH);
  for(int i = 30; i >= 5; i--) {
    showNumber(1, i);
    showNumber(2, i - 5);
    delay(1000);
  }
  
  /*  1 - red 5s
      2 - yel 5s */
  digitalWrite(G2, LOW);
  for (int i = 4; i >= 0; i--) {
    if (i % 2 == 0) digitalWrite(Y2, HIGH);
    else digitalWrite(Y2, LOW);
    showNumber(1, i);
    showNumber(2, i);
    delay(1000);
  }

  /*  1 - gre 25s
      2 - red 30s  */
  digitalWrite(R1, LOW);
  digitalWrite(Y2, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(G1, HIGH);
  for (int i = 30; i >= 5; i--) {
    showNumber(2, i);
    showNumber(1, i - 5);
    delay(1000);
  }

  /*  1 - yel 5s
      2 - red 5s */
  digitalWrite(G1, LOW);
  for (int i = 4; i >= 0; i--) {
    if (i % 2 == 0) digitalWrite(Y1, HIGH);
    else digitalWrite(Y1, LOW);
    showNumber(1, i);
    showNumber(2, i);
    delay(1000);
  }
  digitalWrite(Y1, LOW);
  digitalWrite(R2, LOW);
}

void showNumber(int index, int num)
{
    digit1 = num % 10 ;
    digit2 = (num / 10) % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {digits[digit2],digits[digit1]};
    if (index == 1)
      sr1.setAll(numberToPrint);
    else if (index == 2)
      sr2.setAll(numberToPrint);
}