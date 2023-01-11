
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ONE_WIRE_BUS D4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display 
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define encoderCLK D6
#define encoderDT D7
#define encoderSW D8

#define heaterRele D5
 
volatile int lastEncoded = 0;
volatile long encoderValue = 0;

bool EncoderSW_Pressed, ledBuiltin_state;
float temperatureC, setpointC;
unsigned long prev_millis, curr_millis;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Setup...");
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(heaterRele, OUTPUT);

  Encoder_Setup();
  OLED_Setup();

  Serial.println("Setup OK!");
  prev_millis = millis();
}
 
void loop() 
{
  sensors.requestTemperatures(); 
  temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");

  setpointC = 38 + (encoderValue / 10);
  if(temperatureC <= setpointC - 0,5)
  {
    digitalWrite(heaterRele, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if(temperatureC >= setpointC + 0,5)
  {
    digitalWrite(heaterRele, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }

  OLED_Print();

  curr_millis = millis();
  if(curr_millis - prev_millis >= 2000) 
  {
    prev_millis = curr_millis;
    ledBuiltin_state != ledBuiltin_state;
    digitalWrite(LED_BUILTIN, ledBuiltin_state);
  }
}
