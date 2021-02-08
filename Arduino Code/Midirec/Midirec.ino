//Author: GlucoseGuy
#include <Wire.h>
#include <ToneLib.h>
#include "frequens.h"
#define buzznum 6
//add some leds if u like
struct buzzers {
  int pin;
  int device;
};
buzzers buzz[] = {
  {2, 0},//specific the location and device name for buzzers
  {3, 1},
  {4, 2},
  {5, 3},
  {6, 4},
  {7, 5},
};
#define slaveAddress 0x08
byte dataArray[3];//three datas in array
Tone buzzer[buzznum];//maximun buzzer can held is up to six
void setup() {
  Wire.begin(slaveAddress);
  //Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  for (int i = 0; i < buzznum; i++) {
    buzzer[i].begin(buzz[i].pin);//begin buzzers
  }
}

void loop() {
}
void receiveEvent(int howmany) //howmany = Wire.write()executed by Master
//dataArray[0] for channel
//dataArray[1] for note
//dataArray[2] for device
{
  for (int i = 0; i < howmany; i++)
  {
    dataArray[i] = Wire.read();
    if (dataArray[0] == 1) {
      for (int i = 0; i < buzznum; i++) {//constantly scan through the buzzers
        if (buzz[i].device == dataArray[2]) {//check which device
          if (dataArray[1] > 0) {
            buzzer[i].play(freqVals[dataArray[1]]);
          } else {
            buzzer[i].stop();
          }
        }
      }
    }
  }
}
