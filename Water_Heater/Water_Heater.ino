
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ONE_WIRE_BUS D3
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

bool EncoderSW_Pressed, encoderSW_state, encoderSW_detached, led_state;
float temperatureC, setpointC;
unsigned long prev_millis, prev_millis_led, prev_millis_encoderSWinterrupt, curr_millis;

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
  prev_millis_encoderSWinterrupt = millis();
  prev_millis_led = millis();
}
 
void loop() 
{
  curr_millis = millis();

  sensors.requestTemperatures(); 
  temperatureC = sensors.getTempCByIndex(0);
  //Serial.print(temperatureC);
  //Serial.println("ºC");

  setpointC = 38.0 + (encoderValue / 10.0);
  if(temperatureC <= setpointC - 0.5)
  {
    digitalWrite(heaterRele, HIGH);
  }

  if(temperatureC >= setpointC + 0.5)
  {
    digitalWrite(heaterRele, LOW);
  }

  OLED_Print();

  if(encoderSW_detached)
  {
    if(curr_millis - prev_millis_encoderSWinterrupt >= 500) 
    {
      prev_millis_encoderSWinterrupt = curr_millis;
      encoderSW_detached = false;
      attachInterrupt(digitalPinToInterrupt(encoderSW), Encoder_SW_Interrupt, RISING);
    }
  }

  if(curr_millis - prev_millis_led >= 1000) 
  {
    if(led_state)
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else 
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
    prev_millis_led = curr_millis;
    led_state = !led_state;
  }
}
