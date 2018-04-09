#include <Adafruit_NeoPixel.h>

#define PINFORMODULE 6 // номер порта к которому подключен модуль
#define count_led 6 // количество светодиодов 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(count_led, PINFORMODULE, NEO_GRB + NEO_KHZ800);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";

int numberModule=1;
bool buf[200]; 

int Rcolor = 0; 
int Gcolor = 0; 
int Bcolor = 0; 
int mode = 0;

int countPtr = 0; 

int countCharInLetter[2] = {
  3,
  3
};

bool alphabetRus[20][3] ={
  {0, 1, 0},
  {1, 1, 1},
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},

  {1, 1, 1},
  {1, 1, 1},
  {1, 0, 0},
  {1, 0, 0},
  {1, 1, 1},
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
  {1, 1, 1}
};

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.show();
}

void loop() {
if(stringComplete)
{
  stringComplete = false;
  getCommand();   //Формат команды: 1-4 команда, 5-7 красный, 8-10 зеленый, 11-13 синий, 14-15 режим, 16-... текст

  if(commandString.equals("TEXT"))
  {
    getColorToPrint();
    getModeToPrint();
    String text = getTextToPrint();
    printText(text);
  } else if (commandString.equals("LED1")){
    if(mode==0){
    pixels.setPixelColor(0, pixels.Color(0,150,0));
    pixels.show();
    mode = 1;
    }
   else {
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show();
    mode = 0; 
  }
  }
  
  inputString = "";
}

}

void getColorToPrint(){
  if(inputString.length()>0)
  {
     Rcolor = (inputString.substring(5,8)).toInt();
     Gcolor = (inputString.substring(8,11)).toInt();
     Bcolor = (inputString.substring(11,14)).toInt();
  }
}

void getModeToPrint(){
  if(inputString.length()>0)
  {
     mode = (inputString.substring(14,16)).toInt();
  }
}

void getCommand()
{
  if(inputString.length()>0)
  {
     commandString = inputString.substring(1,5);
  }
}

String getTextToPrint()
{
  String value = inputString.substring(16,inputString.length()-2);
  return value;
}

void printText(String text)
{
  if (mode == 1){
    int ptr = 0; 
    while (ptr < text.length())
    {
      setBuffer(text[ptr]);
      for (int i=0; i<countPtr; i++)
      {
        shift1();
      }
      ptr += 1;
    }
  }
}

void setBuffer(char c)
{
  if (c=='a') initBuffer(0);
}

void initBuffer(int a)
{
  countPtr = countCharInLetter[a];
  for (int i = 0; i< 10; i++)
  {
    for (int j = 0; j < countPtr; j++)
    {
      buf[(i+1)*10-j] = alphabetRus[a*10+i][countPtr - j -1];
    }
  }
  countPtr += 1; //для пробела
}

void shift1()
{
  for (int i=200; i >= 1; i++){
      if ((i-1 >= 100)&&((i-1) % 10 == 0)){
        buf[i] = buf[i-99];
      }
      else 
      {
        if ((i-1) >= 100) buf[i] = buf[i-1];
        else {
          if ((i-1) % 10 != 0) buf[i] = buf[i-1];
          else {
            buf[i] == 0;    
          }
        }
      }
   }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


