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

byte binBuffer[5];

byte countCharInNumber[10] = {
  4,    //0 
  3,    //1
  4,    //2
  4,    //3
  4,    //4
  4,    //5
  4,    //6 
  4,    //7
  4,    //8
  4,    //9
};

byte numbers[100] = {
  6, //{0, 1, 1, 0} //0
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  6, //{0, 1, 1, 0}

  1, //{0, 0, 1} //1
  3, //{0, 1, 1}
  5, //{1, 0, 1}
  1, //{0, 0, 1}
  1, //{0, 0, 1}
  1, //{0, 0, 1}
  1, //{0, 0, 1}
  1, //{0, 0, 1}
  1, //{0, 0, 1}
  1, //{0, 0, 1}

  6, //{0, 1, 1, 0} //2
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  1, //{0, 0, 0, 1}
  2, //{0, 0, 1, 0}
  2, //{0, 0, 1, 0}
  4, //{0, 1, 0, 0}
  4, //{0, 1, 0, 0}
  8, //{1, 0, 0, 0}
  15, //{1, 1, 1, 1}

  6, //{0, 1, 1, 0} //3
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  1, //{0, 0, 0, 1}
  2, //{0, 0, 1, 0}
  1, //{0, 0, 0, 1}
  1, //{0, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  6, //{0, 1, 1, 0}

  1, // {0, 0, 0, 1} //4
  3, //{0, 0, 1, 1}
  3, //{0, 0, 1, 1}
  5, //{0, 1, 0, 1}
  5, //{0, 1, 0, 1}
  9, //{1, 0, 0, 1}
  15, //{1, 1, 1, 1}
  1, //{0, 0, 0, 1}
  1, //{0, 0, 0, 1}
  1, //{0, 0, 0, 1}

  15, //{1, 1, 1, 1} //5
  9, //{1, 0, 0, 1}
  8, //{1, 0, 0, 0}
  8, //{1, 0, 0, 0}
  8, //{1, 0, 0, 0}
  6, //{0, 1, 1, 0}
  1, //{0, 0, 0, 1}
  1, //{0, 0, 0, 1}
  9, //{1, 0, 0, 1}
  6, //{0, 1, 1, 0}

  6, //{0, 1, 1, 0} //6
  9, //{1, 0, 0, 1}
  8, //{1, 0, 0, 0}
  8, //{1, 0, 0, 0}
  8, //{1, 0, 0, 0}
  14, //{1, 1, 1, 0}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  6, //{0, 1, 1, 0}

  15, //{1, 1, 1, 1} //7
  1, //{0, 0, 0, 1}
  1, //{0, 0, 0, 1}
  1, //{0, 0, 0, 1}
  1, //{0, 0, 0, 1}
  2, //{0, 0, 1, 0}
  4, //{0, 1, 0, 0}
  8, //{1, 0, 0, 0}
  8, //{1, 0, 0, 0}
  8, //{1, 0, 0, 0}

  6, //{0, 1, 1, 0} //8
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  6, //{0, 1, 1, 0}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  6, //{0, 1, 1, 0}

  6, //{0, 1, 1, 0} //9
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  9, //{1, 0, 0, 1}
  7, //{0, 1, 1, 1}
  1, //{0, 0, 0, 1}
  1, //{0, 0, 0, 1}
  9, //{1, 0, 0, 1}
  6, //{0, 1, 1, 0}
};

int countCharInLetter[27] = {
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
  2,  //space
};

byte alphabetEng[270] ={
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

  1,    //space
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  Serial.println("strcomplete");
  Serial.println(inputString);
  stringComplete = false;
  getCommand();   //Формат команды: 1-4 команда, 5-7 красный, 8-10 зеленый, 11-13 синий, 14-15 режим, 16-... текст
  Serial.println(commandString);
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
  } else if (commandString.equals("UGLV")) {
    getColorToPrint();
    getModeToPrint();
    Serial.print(Rcolor);
    Serial.print(" | ");
    Serial.print(Gcolor);
    Serial.print(" | ");
    Serial.print(Bcolor+1);
    Serial.print(" | ");
    Serial.print(mode);
    String pic = getTextToPrint();
    printUgl(pic);
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

void printUgl(String text){
  Serial.println("xuy");
  int ptr = 0; 
      setBuffer(text[ptr]);
      Serial.print("xuy");
      Serial.println("xuy");
      for (int i=0; i<20; i++)
      {
        Serial.println("-----SHift1()-----");
        shift1();
        pixels.show();
        delay(50);
      }
      ptr += 1;
    for (int i=0; i<10; i++)
    {
      Serial.println("-------SHift3-----");
      shift3();
      pixels.show(); 
      delay(50);
    }
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
  //Serial.println(c);
  if ((c>='a')&&(c<='z')) initBuffer(c-'a', false);
  if ((c>='0')&&(c<='9')) initBuffer(c-'0', true);
  if (c == ' ') initBuffer(26, false);
}

void initBuffer(int a, bool isNumber){
  if (isNumber) countPtr = countCharInNumber[a]; 
    else countPtr = countCharInLetter[a];

  Serial.println("initBuffer");  
  for (int i = 0; i< 10; i++)
  {
    setBinBuffer(a*10+i, isNumber);
    for (int j = 0; j < countPtr; j++)
    {
      if ((mode == 1) || (mode == 3)) {buf[(i+1)*10-j-1] = binBuffer[countPtr - j - 1];
      if (buf[(i+1)*10-j-1]==1) Serial.println((i+1)*10-j-1);
      }
      if (mode == 2) buf[200+(i*10)+j] = binBuffer[j];
    }
  }
  countPtr += 1; //для пробела
}


void setBinBuffer(int a, bool isNumber)
{ 
  if (!isNumber) 
  {
  int temp = alphabetEng[a];
  for(int i=0; i<5; i++)
  {
    binBuffer[(5-1)-i] = temp % 2;
    temp = temp/2;  
  }
  }
  else 
  {
    int temp = numbers[a];
    int count = countCharInNumber[a/10];
    for(int i=0; i<count; i++)
    {
    binBuffer[(count-1)-i] = temp % 2;
    temp = temp/2;  
    }
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


void shift3()
{
  Serial.println("from shift3");
  for (int i = 300; i<390; i++)
  {
    buf[i] = buf[i+10]; 
  }
  for (int i=390; i<400; i++)
  {
    buf[i]=buf[i-190]; 
  }
  for (int i=200; i<290; i++){
    buf[i]=buf[i] = buf[i+10]; 
    lightLed(i-100, buf[i]);
  }
  for (int i=290; i<300; i++){
    buf[i]=0;
    lightLed(i-100, buf[i]);
  }
}

void shift4()
{
  Serial.println("from shift4");
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


