
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
 
double thisTime, lastTime;
float temperatureC, setpointC;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Setup...");
  pinMode (encoderCLK,INPUT);
  pinMode (encoderDT,INPUT);
  pinMode (encoderSW, INPUT);

  if(display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println("Display setup OK");
  }  
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();          // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text

  setpointC = 38;
}
 
void loop() 
{
  sensors.requestTemperatures(); 
  temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(temperatureC);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");

  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Setpoint: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(setpointC);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");

  display.display();
}
