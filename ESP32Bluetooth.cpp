#include "BluetoothSerial.h"
#include <time.h>
 
BluetoothSerial SerialBT;

#define SplitData 255
#define DATASIZE 8 
#define FW 2
#define SW 4
#define TW 6



// Stick
#define joyX 32
#define joyY 33
// DATA [ [], [], [], [], [], [], [], []]
//         ^   ^
//        SD  DTR
// SD - SplitData
// DTR - DataTypeRequest
// [355] = [99][1]  (BigEndian)

byte DATA[8];

enum DTR{
  accell = 0,
};


void setup() {
  SerialBT.begin("ESP32");
  DATA[0] = SplitData;
  DATA[1] = accell;
  srand(time(NULL));   // Initialization, should only be called once.

}

void SetDATA(size_t posData, int word){
    for (int i = 0 ; i < 2; i++)
      DATA[posData++] = (word >> (i * 8));
}
 
void loop() {
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int  z = rand() % 5;
  
  SetDATA(FW, xValue);
  SetDATA(SW, yValue);
  SetDATA(TW,z);

  SerialBT.write(DATA, 8);
  delay(50);
}