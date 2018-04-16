#include <Adafruit_NeoPixel.h>
#define PIN 6 // номер порта к которому подключен модуль
#define count_led 200 // количество светодиодов 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(count_led, PIN, NEO_GRB + NEO_KHZ800); //first number change does distance between colors
void setup() {
  pixels.begin();
  for (int i=0; i<200; i++)
{
  pixels.setPixelColor(i, pixels.Color(0,0,0)); 
}
  pixels.show(); // Устанавливаем все светодиоды в состояние "Выключено"
}
void loop() {
for (int i=0; i<200; i++)
{
  if (i != 0) pixels.setPixelColor(i-1, pixels.Color(0,0,0));  
  pixels.setPixelColor(i, pixels.Color(0,0,250));
  pixels.show();
  delay(50);
}
 pixels.show();
}
