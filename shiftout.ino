/*
This code lights up each LED connected to
a 74HC595 as determined by the binary value
of a counter.
*/

// Pin connected to SRCLK of 74HC595
int CLOCK = 10; // kiibil 11
// Pin connected to RCLK of 74HC595
int LATCH = 16; // kiibil 12
// Pin connected to SER of 74HC595
int DATA = 14; // kiibil 14

byte counter = 128;

int D[8] = {2,3,4,5,6,7,8,9};

byte PILT[8][8] = {
  { 0,1,1,1, 1,1,1,0},
  { 1,0,0,0, 0,0,0,1},
  { 1,0,1,0, 0,1,0,1},
  { 1,0,0,0, 0,0,0,1},
  
  { 1,1,0,0, 0,0,1,1},
  { 1,0,1,1, 1,1,0,1},
  { 1,0,0,0, 0,0,0,1},
  { 0,1,1,1, 1,1,1,0}
};


byte rida = 0;

unsigned long aeg;
unsigned long kaasaeg;
byte veerg,eveerg;

void setup() {
        int i;
        //set pins to output so you can control the shift register

        pinMode(LATCH, OUTPUT);
        pinMode(CLOCK, OUTPUT);
        pinMode(DATA, OUTPUT);

        for (i=0 ; i<8 ; i++ ) {
          pinMode(D[i],OUTPUT);
          digitalWrite(D[i],HIGH);
        }
        
        digitalWrite(D[0],LOW);
        
        //counter = 128;
        aeg = millis();
        veerg = 1;
        eveerg = 0;
        
}

void loop() {
        

      /*  kaasaeg = millis();
        if (aeg+100 < kaasaeg) {
          aeg = kaasaeg;
          veerg++;
          eveerg++;
          if (veerg == 8) veerg = 0;
          if (eveerg == 8) eveerg = 0;
        }
        */
        counter = 1 << rida;

        // take the latchPin low
        digitalWrite(LATCH, LOW);
        // shift out the bits:
        shiftOut(DATA, CLOCK, MSBFIRST, counter);
        
          digitalWrite(LATCH, HIGH);
       //   digitalWrite(D[veerg],LOW);
       //   digitalWrite(D[eveerg],HIGH);
        //take the latch pin high so the LEDs update:
        for (veerg = 0 ; veerg < 8 ; veerg ++ ) {
          if (PILT[rida][veerg]) {
            digitalWrite(D[veerg],LOW);
          } else {
            digitalWrite(D[veerg],HIGH);
          }
        }
       
        
        digitalWrite(LATCH, HIGH);
        // pause before next value:
        delay(2);
        
        rida++;
        if (rida==8) rida = 0;
}

