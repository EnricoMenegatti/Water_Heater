void OLED_Setup()
{
if(display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    display.clearDisplay();          // Normal 1:1 pixel scale
    display.setTextColor(WHITE);        // Draw white text
    Serial.println("OLED setup OK!");
  } 
}

void OLED_Print()
{
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