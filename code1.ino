#include <SPI.h>
#include <DMD.h>      
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
#include <Wire.h>
//#include "RTClib.h"

#define ROW_MODULE 2
#define COLUMN_MODULE 1
DMD dmd(ROW_MODULE, COLUMN_MODULE);

//RTC_DS3231 rtc;
//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//int h;
//int m;
//int y;
//int mth;
//int d;
//char bhour[6];
//char bdate[15];
//String strdate;
//String strhour;

char message[500];
char char_read;
byte pos_index = 0;
int i;            
char welcome_screen[] = "bonjour la pharmacie de japoma";

void p10scan()
{ 
  dmd.scanDisplayBySPI();
}

void setup()
{
  Serial.begin(9600);
  delay(500); // wait for console opening

//  if (! rtc.begin()) {
//    Serial.println("Couldn't find RTC");
//    while (1);
//  }

//  if (rtc.lostPower()) {
//    Serial.println("RTC lost power, lets set the time!");
//  
//  // Comment out below lines once you set the date & time.
//    // Following line sets the RTC to the date & time this sketch was compiled
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//  
//    // Following line sets the RTC with an explicit date & time
//    // for example to set January 27 2017 at 12:56 you would call:
//    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
//  }
  
  Timer1.initialize(1000);
  Timer1.attachInterrupt(p10scan);
  dmd.clearScreen( true );
  strcpy(message,welcome_screen);
}
void loop()
{

   if(Serial.available())
   {       
        for(i=0; i<199; i++)
        {
            message[i] = '\0';
            Serial.print(message[i]);
        }      
        pos_index=0;
    }

    while(Serial.available() > 0)
    {
       dmd.clearScreen( true );
       if(pos_index < (199)) 
       {         
           char_read = Serial.read();
           message[pos_index] = char_read;
           pos_index++;      
       } 
   }

//DateTime now = rtc.now();
//strdate="";
//y=now.year();
//mth=now.month();
//d=now.day();
//strhour="";
//h=now.hour();
//m=now.minute();
dmd.clearScreen( true );
//strdate=String(d)+"/"+String(mth)+"/"+String(y);
//if (((h) < 10) && ((m) < 10))
//     {
//       strhour="0"+String(h)+":"+"0"+String(m);
//     }
//if (((h) > 9) && ((m) > 9))
//     {
//       strhour=String(h)+":"+String(m);
//     }
//if (((h) > 9) && ((m) < 10))
//     {
//       strhour=String(h)+":"+"0"+String(m);
//     }
//if (((h) < 10) && ((m) > 9))
//     {
//       strhour="0"+String(h)+":"+String(m);
//     }
////str=String(h)+":"+String(min);
//strhour.toCharArray(bhour,6);
//strdate.toCharArray(bdate,15);
//p10.selectFont(Arial_Black_16);
//p10.drawMarquee(bhour,6,(32*ROW_MODULE)-135,1);
////p10.drawString( 1, 4, b, 5, GRAPHICS_NORMAL );
////delay(2000);
//
//p10.selectFont(Arial_Black_16);
//p10.drawMarquee(bdate,15,(32*ROW_MODULE)-80,0);
////p10.drawString( 1, 4, b, 5, GRAPHICS_NORMAL );
//delay(2000);


//   p10.clearScreen( true );
  
   dmd.selectFont(Arial_Black_16);
   dmd.drawMarquee(message,30,(32*ROW_MODULE)-1,0);
   long start=millis();
   long timer_start=start;
   boolean flag=false;
   while(!flag)
   {
     if ((timer_start+250) < millis()) 
     {
       flag=dmd.stepMarquee(-1,0);
       timer_start=millis();
     }
   }
}
