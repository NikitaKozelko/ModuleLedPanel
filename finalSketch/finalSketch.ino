#include <Adafruit_NeoPixel.h>

#define PINFORMODULE 6 // номер порта к которому подключен модуль
#define count_led 200 // количество светодиодов 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(count_led, PINFORMODULE, NEO_GRB + NEO_KHZ800);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";

int numberModule=1;
bool buf[400]; 

int Rcolor = 0; 
int Gcolor = 0; 
int Bcolor = 0; 
int mode = 0;

int countPtr = 0; 

int countCharInLetter[26] = {
  3,  //a
  4,  //b
  4,  //c
  4,  //d
  3,  //e
  3,  //f
  4,  //g
  4,  //h
  3,  //i
  4,  //j 
  4,  //k
  3,  //L
  5,  //m
  4,  //n
  4,  //o
  4,  //p
  5,  //q 
  4,  //r
  4,  //s
  5,  //t
  4,  //u
  5,  //v
  5,  //w
  4,  //x
  5,  //y
  4,  //z 
};

byte binBuffer[5];

byte alphabetRus[260] ={
  8,  //{0, 1, 0, 0, 0},  //a
  28, //{1, 1, 1, 0, 0},
  20, //{1, 0, 1, 0, 0},
  20, //{1, 0, 1, 0, 0},
  20, //{1, 0, 1, 0, 0},
  20, //{1, 0, 1, 0, 0},
  28, //{1, 1, 1, 0, 0},
  20, //{1, 0, 1, 0, 0},
  20, //{1, 0, 1, 0, 0},
  20, //{1, 0, 1, 0, 0},

  28, //{1, 1, 1, 0, 0},  //b
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  28, //{1, 1, 1, 0, 0},
  30, //{1, 1, 1, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  28, //{1, 1, 1, 0, 0},

  13, //{0, 1, 1, 0, 0},//c
  18, //{1, 0, 0, 1, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  18, //{1, 0, 0, 1, 0},
  12, //{0, 1, 1, 0, 0},

  28, //{1, 1, 1, 0, 0}, //d
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  28, //{1, 1, 1, 0, 0},

  28, //{1, 1, 1, 0, 0},   //e
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  24, //{1, 1, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  28, //{1, 1, 1, 0, 0},

  28, //{1, 1, 1, 0, 0},   //f
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  28, //{1, 1, 1, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},

  12, //{0, 1, 1, 0, 0},   //g
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  22, //{1, 0, 1, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  12, //{0, 1, 1, 0, 0},

  18, //{1, 0, 0, 1, 0},   //H
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  30, //{1, 1, 1, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},

  28, //{1, 1, 1, 0, 0},   //i
  8,  //{0, 1, 0, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  28, //{1, 1, 1, 0, 0},

  6,  //{0, 0, 1, 1, 0},   //j
  2,  //{0, 0, 0, 1, 0},
  2,  //{0, 0, 0, 1, 0},
  2,  //{0, 0, 0, 1, 0},
  2,  //{0, 0, 0, 1, 0},
  2,  //{0, 0, 0, 1, 0},
  2,  //{0, 0, 0, 1, 0},
  2,  //{0, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  12, //{0, 1, 1, 0, 0},

  18, //{1, 0, 0, 1, 0},   //k
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  20, //{1, 0, 1, 0, 0},
  24, //{1, 1, 0, 0, 0},
  20, //{1, 0, 1, 0, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},

  16, //{1, 0, 0, 0, 0},   //L
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  20, //{1, 0, 1, 0, 0},
  28, //{1, 1, 1, 0, 0},

  17, //{1, 0, 0, 0, 1},   //M
  27, //{1, 1, 0, 1, 1},
  27, //{1, 1, 0, 1, 1},
  21, //{1, 0, 1, 0, 1},
  21, //{1, 0, 1, 0, 1},
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},

  18, //{1, 0, 0, 1, 0},   //N
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  26, //{1, 1, 0, 1, 0},
  26, //{1, 1, 0, 1, 0},
  22, //{1, 0, 1, 1, 0},
  22, //{1, 0, 1, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},

  12, //{0, 1, 1, 0, 0},   //O
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  12, //{0, 1, 1, 0, 0},

  28, //{1, 1, 1, 0, 0},   //P
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  28, //{1, 1, 1, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},

  12, //{0, 1, 1, 0, 0},   //Q
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  13, //{0, 1, 1, 0, 1},

  28, //{1, 1, 1, 0, 0},   //R
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  28, //{1, 1, 1, 0, 0},
  20, //{1, 0, 1, 0, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},

  14, //{0, 1, 1, 1, 0},   //S
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  2,  //{0, 0, 0, 1, 0},
  2,  //{0, 0, 0, 1, 0},
  30, //{1, 1, 1, 1, 0},

  31, //{1, 1, 1, 1, 1},     //T
  21, //{1, 0, 1, 0, 1},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},

  18, //{1, 0, 0, 1, 0},   //U
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  13, //{0, 1, 1, 0, 1},

  

  17, //{1, 0, 0, 0, 1},   //V
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  10, //{0, 1, 0, 1, 0},
  10, //{0, 1, 0, 1, 0},
  4,  //{0, 0, 1, 0, 0},
  
  17, //{1, 0, 0, 0, 1},   //w
  21, //{1, 0, 1, 0, 1},
  21, //{1, 0, 1, 0, 1},
  21, //{1, 0, 1, 0, 1},
  21, //{1, 0, 1, 0, 1},
  21, //{1, 0, 1, 0, 1},
  21, //{1, 0, 1, 0, 1},
  21, //{1, 0, 1, 0, 1},
  21, //{1, 0, 1, 0, 1},
  10, //{0, 1, 0, 1, 0},

  18, //{1, 0, 0, 1, 0},   //x
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  12, //{0, 1, 1, 0, 0},
  12, //{0, 1, 1, 0, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},
  18, //{1, 0, 0, 1, 0},

  17, //{1, 0, 0, 0, 1},   //y
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  17, //{1, 0, 0, 0, 1},
  10, //{0, 1, 0, 1, 0},
  10, //{0, 1, 0, 1, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},
  4,  //{0, 0, 1, 0, 0},

  30, //{1, 1, 1, 1, 0},   //z
  2,  //{0, 0, 0, 1, 0},
  2,  //{0, 0, 0, 1, 0},
  2,  //{0, 0, 0, 1, 0},
  4,  //{0, 0, 1, 0, 0},
  12, //{0, 1, 1, 0, 0},
  8,  //{0, 1, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  16, //{1, 0, 0, 0, 0},
  30, //{1, 1, 1, 1, 0},
};

void setup() {
  Serial.begin(9600);
  pixels.begin();
  for(int i=0; i<100; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
  }
  for (int i =0 ;i<300;i++){
    buf[i]=0; 
  }
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
    //Serial.print(Rcolor);
    //Serial.print(" | ");
    //Serial.print(Gcolor);
    //Serial.print(" | ");
    //Serial.print(Bcolor+1);
    //Serial.print(" | ");
    //Serial.print(mode);
    String text = getTextToPrint();
    //Serial.print(" | ");
    //Serial.print(text);
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
    int ptr = 0; 
    //Serial.print(" lenoftext ");
    //Serial.print(text.length());
    while (ptr < text.length())
    {
      setBuffer(text[ptr]);
      for (int i=0; i<countPtr; i++)
      {
        //Serial.print("-------SHIFT!!!");
        //Serial.print('\n');
        if (mode == 1) shift1();
        if (mode == 2) shift2(); 
        pixels.show();
        delay(50);
      }
      ptr += 1;
    }
    for (int i=0; i<20; i++)
    {
      //Serial.print("-------SHIFT!!!");
      //Serial.print('\n');
      if (mode == 1) shift1();
      if (mode == 2) shift2(); 
      pixels.show(); 
      delay(50);
    }
}

void setBuffer(char c)
{
  if (mode == 1) initBuffer1(c-'a');
  if (mode == 2) initBuffer2(c-'a');
}

void initBuffer1(int a)
{
  countPtr = countCharInLetter[a];
  Serial.print(" countPtr ");
  Serial.print(countPtr);
  for (int i = 0; i< 10; i++)
  {
    for (int j = 0; j < countPtr; j++)
    {
      setBinBuffer(a*10+i);
      buf[(i+1)*10-j-1] = binBuffer[countPtr - j - 1]; 
      //buf[(i+1)*10-j-1] = alphabetRus[a*10+i][countPtr - j -1];
      if (buf[(i+1)*10-j-1] == 1) {
        Serial.print((i+1)*10-j-1);
        Serial.print('\n');
      }
    }
  }
  countPtr += 1; //для пробела
}

void initBuffer2(int a)
{
  countPtr = countCharInLetter[a];
  Serial.print(" countPtr ");
  Serial.print(countPtr);
  for (int i = 0; i< 10; i++)
  {
    for (int j = 0; j < countPtr; j++)
    {
      setBinBuffer(a*10+i);
      buf[200+(i*10)+j] = binBuffer[j]; 
      //buf[(i+1)*10-j-1] = alphabetRus[a*10+i][countPtr - j -1];
      if (buf[(i+1)*10-j-1] == 1) {
        Serial.print((i+1)*10-j-1);
        Serial.print('\n');
      }
    }
  }
  countPtr += 1; //для пробела
}

void setBinBuffer(int a)
{
  int temp = alphabetRus[a];
  for(int i=0; i<5; i++)
  {
    binBuffer[(5-1)-i] = temp % 2;
    temp = temp/2;  
  }
}

void shift1()
{
  for (int i=299; i >= 1; i--){
      if ((i >= 100)&&(i % 10 == 0)){
        buf[i] = buf[i-91];
        if (buf[i]==1){
        //Serial.print(i);
        //Serial.print("<-");
        //Serial.print(i-91);
        //Serial.print('\n');
        }
      }
      else 
      {
        if (i >= 100) {
          buf[i] = buf[i-1];
          if (buf[i]==1){
          //Serial.print(i);
          //Serial.print("<-");
          //Serial.print(i-1);
          //Serial.print('\n');
          }
        }
        else {
          if (i % 10 != 0) {
            buf[i] = buf[i-1];
            if (buf[i]==1){
            //Serial.print(i);
            //Serial.print("<-");
            //Serial.print(i-1);
            //Serial.print('\n');
            }
          }
          else {
            buf[i] == 0;  
            if (buf[i]==1){
            //Serial.print(i);
            //Serial.print("<-");
            //Serial.print("000");
            //Serial.print('\n'); 
            }
          }
        }
      }
      if (i>=100) lightLed(i-100, buf[i]);
   }
   buf[0]=0; 
}

void shift2()
{
  for (int i=0; i < 299; i++){
      if ((i<200)&&((i+1)%10==0)) buf[i]=buf[i+91]; 
      if ((i<200)&&((i+1)%10!=0)) buf[i]=buf[i+1];
      if ((i>=200)&&((i+1)%10==0)) buf[i]=0; 
      if ((i>=200)&&((i+1)%10!=0)) buf[i]=buf[i+1];
      if (i<200) lightLed(i, buf[i]);
   }
}

void lightLed(int i, int state){
  if (state == 1) {pixels.setPixelColor(i, 5);
  Serial.print(i);
  Serial.print(" ");
  Serial.print(Rcolor);
  Serial.print(Gcolor);
  Serial.print(Bcolor);
  Serial.print('\n');
  }
  else pixels.setPixelColor(i, 0, 0, 0);
  //pixels.show();
  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '@') {
      stringComplete = true;
    }
  }
}


