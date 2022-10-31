// Dies ist der Arduino Sketch für einen FarbLEDRing von Jan R. Ziebart
// Ich übernehme keinerlei Haftung für irgendwas, Zerstörung von Chips, Epileptische Anfälle, gestorbene Elfen und dergleichen.
// Diese Software ist lizenziert unter Creative Commons unter Nennung des Inhabers.
// Ganz großen Dank an Rui Santos, der mich hierzu z.T. inspiriert hat und auf dessen Arbeit dieser Sketch aufbaut.
// Normaler ESP32:
// Board: ESP32 Dev Module
// Port: der letzte, oft COM8 oder 9
// 80MHz Flash
// Upload:921600
// Variante für den Einbau in eine LAterne!


// Includes First //////////////////////////////////////////////////////////////////
#include <Adafruit_NeoPixel.h>  // for the Pixels...

// Constants Second ////////////////////////////////////////////////////////////////
#define LEDSPIN               14 // The Pin where the 470k Resistor leads to the First DIN of the LEDs
#define MAXLEDS               12  // the Number of Neopixels attached. Cannot be defined while runtime.

// Variables Third /////////////////////////////////////////////////////////////////
int         i=50;                             // the Superstar of Counting Variables
uint8_t LEDBrightness = 90;                     // the LED Brighntess for starters
uint8_t Colorhelper = 0;                     // A cycling Variable for the COlorwheel.
int Mode = 0;                           // Mode tells us which Programm to run NOW.

// Objects Fourth //////////////////////////////////////////////////////////////////
Adafruit_NeoPixel strip = Adafruit_NeoPixel(MAXLEDS, LEDSPIN, NEO_GRB + NEO_KHZ800);

// Finally Setup //////////////////////////////////////////////////////////////////
void setup() {
   // // // Setup the Serial Connection for Debugging
  Serial.begin(115200);
  Serial.println(" Hello! I am alive!");
 // Initialise the LED Strip
 strip.setBrightness(LEDBrightness);
 strip.show();     
}

// the Main Loop. //////////////////////////////////////////////////////////////////////////////////////////
void loop() {
if (Colorhelper > 254) {
    Colorhelper = 0; 
    Mode++;
   strip.setBrightness(LEDBrightness);
    }
    delay(10);
 switch (Mode) {
  case 0:
    SwellFire(1); 
    break;
 case 1:
    MultiFire(17);
    break;
 case 2:
    MultiFire(5);
    break;
 case 3:
    MultiFire(10);
    break;
 case 4:
    MultiFire(30); 
    break;
  case 5:
    MultiFire(50);
    break;
 case 6:
    MultiFire(5);
    break;
 case 7:
    MultiFire(120);
    break;
 case 8:
    MultiFire(17);
    break;
 case 9:
    MultiFire(2);
    break;
 case 10:
    MultiFire(10);
    break;
 case 11:
    MultiFire(30); 
    break;
  case 12:
    MultiFire(50);
    break;
 case 13:
    MultiFire(5);
    break;
 case 14:
   SwellColor(50);
   break;  
 case 15:
   SwellColor(120);
   break;
 case 16:
   MultiColor(50);
   break;
 default:
    Mode = 0;
    break;
    }
  Colorhelper++; // Set the next Cyclecolor!
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
 WheelPos = 255 - WheelPos;
 if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
 if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t FireWheel(byte WheelPos) {
 WheelPos = 255 - WheelPos;
if(WheelPos < 85) {
    return strip.Color(255 - WheelPos, WheelPos, 0);
    }
 if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos  , 85 - WheelPos,0);
    }
    WheelPos -= 170;
    return strip.Color(170+ WheelPos , 10, 0);
}

////////////////// FIRST MODE ////////////////////////////FireColorWheel///////////////////
void MultiFire(uint8_t _wait){
 uint8_t _i = 0; // the Pointer to the Wanted LED
 for(_i=0;_i < MAXLEDS ;_i++) {
      strip.setPixelColor(_i, FireWheel(Colorhelper+ _i*5));
      }
   strip.show();
   delay(_wait);
}

////////////////// SECOND MODE ////////////////////////////MULTICOLOR GLOBAL RAINBOW ///////////////////
void MultiColor(uint8_t _wait) {
// REMINDER WHEEL -> 0..255 GIVES A COLORPOINT OF THE RAINBOW.
uint8_t _i = 0; // the Pointer to the Wanted LED
 for(_i=0;_i < MAXLEDS ;_i++) {
      Serial.print("I ist gerade:");
      Serial.println(_i);
      strip.setPixelColor(_i, Wheel((_i * 256 / MAXLEDS+ Colorhelper) & 255));
      }
   strip.show();
   delay(_wait);
} 
////////////////// THIRD MODE ////////////////////////////SWELL GLOBAL RAINBOW ///////////////////
void SwellFire(uint8_t _wait) {
// REMINDER WHEEL -> 0..255 GIVES A COLORPOINT OF THE RAINBOW.
uint8_t _Bright = Colorhelper & 60;
uint8_t _i = 0; // the Pointer to the Wanted LED
 for(_i=0;_i < MAXLEDS ;_i++) {
      strip.setPixelColor(_i, FireWheel((Colorhelper+ _i*10) &255 ));
      }
   strip.setBrightness(_Bright& LEDBrightness);
   strip.show();
   delay(_wait);
} 
////////////////// THIRD MODE ////////////////////////////SWELL GLOBAL RAINBOW ///////////////////
void SwellColor(uint8_t _wait) {
// REMINDER WHEEL -> 0..255 GIVES A COLORPOINT OF THE RAINBOW.
uint8_t _Bright = 50  + (Colorhelper & 30);
uint8_t _i = 0; // the Pointer to the Wanted LED
 for(_i=0;_i < MAXLEDS ;_i++) {
      strip.setPixelColor(_i, Wheel(Colorhelper &255 ));
      }
   //strip.setBrightness(_Bright & LEDBrightness);
   strip.show();
   delay(_wait);
}
