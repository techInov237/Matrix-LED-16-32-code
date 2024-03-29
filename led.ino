#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_Black_16_ISO_8859_1.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

DMD dmd(DISPLAYS_ACROSS,DISPLAYS_DOWN);

void ScanDMD()
{
  dmd.scanDisplayBySPI();
}

void setup() {
  Timer1.initialize(5000);
  Timer1.attachInterrupt(ScanDMD);

  dmd.clearScreen(true);
  Serial.begin(115200);
}

void loop() {
  dmd.clearScreen(true);
  dmd.selectFont( Arial_Black_16_ISO_8859_1);
  const char *MSG = "LES GARS C'EST PROP";
  dmd.drawMarquee (MSG, strlen(MSG), (32*DISPLAYS_ACROSS)-1, 0);
  long start = millis();
  long timer=start;

  while (1) {
    if ((timer+60) < millis() ) {
      dmd.stepMarquee(-1,0); 
      timer= millis(); }
    }
  

}
