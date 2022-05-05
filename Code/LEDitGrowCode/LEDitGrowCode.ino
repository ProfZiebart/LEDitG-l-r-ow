// Dies ist der Arduino Sketch für einen FarbLEDRing von Jan R. Ziebart
// Ich übernehme keinerlei Haftung für irgendwas, Zerstörung von Chips, Epileptische Anfälle, gestorbene Elfen und dergleichen.
// Diese Software ist lizenziert unter Creative Commons unter Nennung des Inhabers.
// Ganz großen Dank an Rui Santos, der mich hierzu z.T. inspiriert hat und auf dessen Arbeit dieser Sketch aufbaut.
// Normaler ESP32:
// Board: ESP32 Dev Module
// Port: der letzte, oft COM8 oder 9
// 80MHz Flash
// Upload:921600


// Includes First //////////////////////////////////////////////////////////////////
#include <Adafruit_NeoPixel.h>  // for the Pixels...

// Constants Second ////////////////////////////////////////////////////////////////
#define LEDSPIN               12 // The Pin where the 470k Resistor leads to the First DIN of the LEDs
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
    delay(50);
    }
 switch (Mode) {
  case 0:
    MultiColor(15); 
    break;
  case 1:
    MultiColor(17);
    break;
 case 2:
    MultiColor(20);
    break;
  case 3:
    SwellColor(20);
    break;
  case 4:
    MonoColor(15);
    break;
  case 5:
    MonoColor(20);
    break;
  case 6:
    MonoColor(25);
    break;
  case 7:
    MonoColor(30);
    break;
  case 8:
    MultiColor(40);
    break;
  case 9:
    MultiColor(30);
    break;
  case 10:
    MultiColor(20);
    break;
  case 11:
    MultiColor(10);
    break;
  case 12:
    MultiColor(5);
    break;
  case 13:
    MultiColorInvert(5);
    break;
  case 14:
    MultiColorInvert(10);
    break;
  case 15:
    MultiColorInvert(15);
    break;
  case 16:
    MultiColorInvert(20);
    break;
  case 17:
    MultiColorInvert(25);
    break;
  case 18:
    MultiColor(100);
    break;
  case 19:
    MonoColor(100);
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

////////////////// FIRST MODE ////////////////////////////MONOCOLOR///////////////////
void MonoColor(uint8_t _wait){
 uint8_t _i = 0; // the Pointer to the Wanted LED
 for(_i=0;_i < MAXLEDS ;_i++) {
      strip.setPixelColor(_i, Wheel(Colorhelper));
      }
   strip.show();
   delay(_wait);
}

////////////////// SECOND MODE ////////////////////////////MULTICOLOR GLOBAL RAINBOW ///////////////////
void MultiColor(uint8_t _wait) {
// REMINDER WHEEL -> 0..255 GIVES A COLORPOINT OF THE RAINBOW.
uint8_t _i = 0; // the Pointer to the Wanted LED
 for(_i=0;_i < MAXLEDS ;_i++) {
      strip.setPixelColor(_i, Wheel((_i * 256 / MAXLEDS+ Colorhelper) & 255));
      }
   strip.show();
   delay(_wait);
} 
////////////////// THIRD MODE ////////////////////////////SWELL GLOBAL RAINBOW ///////////////////
void SwellColor(uint8_t _wait) {
// REMINDER WHEEL -> 0..255 GIVES A COLORPOINT OF THE RAINBOW.
uint8_t _Bright = Colorhelper & 30;
uint8_t _i = 0; // the Pointer to the Wanted LED
 for(_i=0;_i < MAXLEDS ;_i++) {
      strip.setPixelColor(_i, Wheel((Colorhelper) & 255));
      }
   strip.setBrightness(_Bright& LEDBrightness);
   strip.show();
   delay(_wait);
} 
////////////////// FOURTH MODE ////////////////////////////MULTICOLOR GLOBAL RAINBOW INVERT///////////////////
void MultiColorInvert(uint8_t _wait) {
// REMINDER WHEEL -> 0..255 GIVES A COLORPOINT OF THE RAINBOW.
uint8_t _i = 0; // the Pointer to the Wanted LED
 for(_i=0;_i < MAXLEDS ;_i++) {
      strip.setPixelColor(MAXLEDS-_i-1, Wheel(256-((_i * 256 / MAXLEDS+ Colorhelper) & 255)));
      }
   strip.show();
   delay(_wait);
} 
