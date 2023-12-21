#include "Adafruit_NeoPixel.h"
#include "TM1637Display.h"
#include "RTClib.h"

#define Display_CLK 4
#define Display_DIO 3
#define LED        7 

#define Minute_Button 6
#define Hour_Button 5

bool parse=false;
bool config=false;
int Hour=-1;
int Minute=-1;
int Minute_before=0;
int flag=0;
RTC_DS3231 rtc;

//========================USEFUL VARIABLES=============================
int Display_backlight = 3;
int led_brightness = 255; // Adjust it 0 to 255
#define NUMPIXELS 3
//===================================================================== 

TM1637Display Display(Display_CLK, Display_DIO);
// When setting up the NeoPixel library, we tell it how many pixels,
Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);

void setup() {

  pinMode(Minute_Button, INPUT_PULLUP);
  pinMode(Hour_Button, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  Display.setBrightness(Display_backlight);
  pixels.setBrightness(led_brightness);

  Serial.begin(9600);       // initializes the Serial connection @ 9600 baud

rtc.begin();
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}

void loop() {
  
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();


      // switch on the ring in blue
  pixels.clear(); // Set all pixel colors to 'off'
//  //Back to the future 
    for(int i=0; i<3;i++){
  pixels.setPixelColor(i, pixels.Color(255,0,0));
  }
  pixels.show();

Display.showNumberDecEx(now.hour() ,0b01000000,true,2,0);
Display.showNumberDecEx(now.minute() ,0b01000000,true,2,2);

  if( digitalRead(Minute_Button) == false){

    Minute = Minute + 1;
    rtc.adjust(DateTime(now.year(), now.month(), now.day(),now.hour(), Minute, 0));;
    if(Minute > 58){Minute=-1;}
    delay(90);
    }

  if( digitalRead(Hour_Button) == false){
    Hour = Hour + 1;
    rtc.adjust(DateTime(now.year(), now.month(), now.day(),Hour, now.minute(), now.second()));;
    if(Hour > 22){Hour=-1;}
    delay(90);
  }


}
