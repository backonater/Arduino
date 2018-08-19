//Current Version: 0.3a//
/* CHANGELOG: 
 *  
 *  0.3a Alpha build -IN PROGRESS
 *  
 *  
 *  
 *    +Add Digi pot write code\dependancies
 *  
 *  
 *  0.2a: Alpha build -COMPILED
 *     -No LED code
 *     -Digital Pots no code
 *     -no sensor wires
 *     - Physical Pots have no "meaning"
 *     -wattage has no way to display
 *     -millis timing not implemented
 *     
 *     +Reoganized code layout 
 *     +simplified code
 *     +Add serial support
 *     +"Grayed out" potential useful code 
 *     +Voltage\Ameprage code given their own class 
 *     +Add code for calculating wattage
 *  
 *  
 *  
 * 0.1a: Alpha build -COMPILED
 *     - 2 Digital Pots not coded
 *     -volt sensor not wired
 *     -hall effect sensor not wired\ coded
 *     -status light not coded
 *     
 *     +imported i2c LCD library + run temp code
 *     +barebone volt sensor code imported
 *     +barebone hall effect code imported
 *     +FastLed library import\ run temp code
 *     +Analog pots wire\coded
 *     
 * 
 * 
 * 
 * POTENTIAL ADDITIONS: 
 *  ~Button to cycle LCD screens
 *  ~Add internal temp sensor
 *  ~Add a relay to combat accidental voltage changes
 *  ~Add a lock button
 *
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>
#include <SPI.h>

CRGBPalette16 currentPalette;
#define DATA_PIN 3
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
LiquidCrystal_I2C lcd(0x27,20,4);

byte VoltInPin = A3; //Volt physical pot input
byte AmpInPin= A2; //Raw data from A2
int VoltPotPin = A0; //Volt physical pot input
int AmpPotPin = A1; // AMp physical pot input


int CurrentSetVolt=0;
//int UpdateSetVolt=0;
int CurrentSetAmp=0;
//int UpdateSetVolt=0;

byte address = 0x11; 
int CSV= 4;
int CVA=  ;
int i=0;





/*int LockButton = 2;
int csV = 9;
int csA= 10;
int VoltPotPin = A0; //Volt physical pot input
int AmpPotPin = A1; // AMp physical pot input
int AmpSensor = A2; //amp module intput
int VoltageDivider = A3; //voltage divider input
#define DATA_PIN 3
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
LiquidCrystal_I2C lcd(0x27,20,4);
int t=0;
int CurrentWattage = 0;
int SetVoltage = 0;
int SetAmprage = 0;
int VoltPotVal =0; //not constant data from A0
int AmpPotVal =0; //not constant data from A1
int CurrentVoltage=0; // not constant data from voltage divider
int CurrentAmprage=0;
int AmpModuleRaw=0; //Raw data from A2
int VoltDividerRaw=0; //Raw data from A3
unsigned long previousMillis = 0;
const long interval = 10;
*/
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

lcd.init();
 Serial.print("Version: 0.2 Alpha Build");
 Serial.print("Calibrating-Booting");
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("    Power Supply   ");
  lcd.setCursor(0,1);
  lcd.print("Version: 0.2 Alpha");
  lcd.setCursor(0,2);
  lcd.print("Calibrating-Booting");


SPI.begin();
 digitalPotVoltageWrite(0x00);
 digitalPotAmperageWrite(0x00);
   delay(1000);
 
      // adjust  wiper in the  Mid point  .
   digitalPotVoltageWrite(0x80);
   digitalPotAmperageWrite(0x80);
   delay(1000);

   // adjust Lowest Resistance .
   digitalPotVoltageWrite(0xFF);
   digitalPotAmperageWrite(0xFF);
   delay(1000);


LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(255);
// lcd.clear();

pinMode(VoltInPin, INPUT);  
pinMode(AmpInPin, INPUT);
pinMode (CSV, OUTPUT);
pinMode (CSA, OUTPUT);


}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }


void loop() {
   
Serial.print("Voltage:");
Serial.println(getVoltage());
Serial.print("Amperage:");
Serial.println(getAmps());
  lcd.setCursor(0,0);
  lcd.print("Voltage:");
  lcd.print( getVoltage());
  lcd.setCursor(0,1);
  lcd.print("Amperage:");
  lcd.print( getAmps());
  lcd.setCursor(0,2);
  lcd.print("Set Voltage:");
  lcd.print(VoltSet());
  lcd.setCursor(0,3);
















}


float getVoltage(){
 const float R1 = 30000.0; //  
   const float R2 = 7500.0; // 
   float value = analogRead(VoltInPin);
   float vout = (value * 5.0) / 1024.0; // see text
   float vin = vout / (R2/(R1+R2)); 
  return vin;
 }

float getWatt(){
  float watt = getVoltage()+ getAmps();
  return watt;
}





float getAmps( ){
  float average = 0;
  for(int i = 0; i < 1000; i++) {
    average = average + (.0264 * analogRead(A0) -13.385) / 1000;//this is 
    //for the 5A mode, if 20A or 30A mode, need to modify this formula to 
    //(.19 * analogRead(A0) -25) for 20A mode and 
    //(.044 * analogRead(A0) -3.78) for 30A mode
    delay(3);
}
}

float VoltSet(){
int SetV= map(VoltPotPin, 0, 1023, 0, 255);
if (SetV != CurrentSetVolt){
 CurrentSetVolt == SetV;
}
  return SetV;
  }


float AmpSet(){
int SetA= map(AmpPotPin, 0, 1023, 0, 255);
if(SetA != CurrentSetAmp){
  CurrentSetAmp == SetA;
   }
 return SetA;
}
  

int digitalPotVoltageWrite(int value)
{
  digitalWrite(CSV, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CSV, HIGH);
}


int digitalPotAmperageWrite(int value)
{
  digitalWrite(CSA, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CSA, HIGH);
}



  
