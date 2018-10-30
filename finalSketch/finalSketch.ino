#include <Adafruit_NeoPixel.h>
#define PIN 6 // номер порта к которому подключен модуль
#define count_led 300 // количество светодиодов 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(250, PIN, NEO_GRB + NEO_KHZ800); //first number change does distance between colors
//void setup() {
//  pixels.begin();
//  for (int i=0; i<300; i++)
//{
//  pixels.setPixelColor(i, pixels.Color(0,0,10)); 
//}
//  pixels.show(); // Устанавливаем все светодиоды в состояние "Выключено"
//}

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";
String temp= ""; 

//int numberModule=3;
bool buf[401]; 

byte Rcolor = 0; 
byte Gcolor = 0; 
byte Bcolor = 0; 
byte mode = 0;

byte countPtr = 0; 

byte binBuffer[5];

byte countCharInNumber[0];
//byte countCharInNumber[10] = {
//  4,    //0 
//  3,    //1
//  4,    //2
//  4,    //3
//  4,    //4
//  4,    //5
//  4,    //6 
//  4,    //7
//  4,    //8
//  4,    //9
//};

byte numbers[0]; 
//byte numbers[100] = {
//  6, //{0, 1, 1, 0} //0
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  6, //{0, 1, 1, 0}
//
//  1, //{0, 0, 1} //1
//  3, //{0, 1, 1}
//  5, //{1, 0, 1}
//  1, //{0, 0, 1}
//  1, //{0, 0, 1}
//  1, //{0, 0, 1}
//  1, //{0, 0, 1}
//  1, //{0, 0, 1}
//  1, //{0, 0, 1}
//  1, //{0, 0, 1}
//
//  6, //{0, 1, 1, 0} //2
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//  2, //{0, 0, 1, 0}
//  2, //{0, 0, 1, 0}
//  4, //{0, 1, 0, 0}
//  4, //{0, 1, 0, 0}
//  8, //{1, 0, 0, 0}
//  15, //{1, 1, 1, 1}
//
//  6, //{0, 1, 1, 0} //3
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//  2, //{0, 0, 1, 0}
//  1, //{0, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  6, //{0, 1, 1, 0}
//
//  1, // {0, 0, 0, 1} //4
//  3, //{0, 0, 1, 1}
//  3, //{0, 0, 1, 1}
//  5, //{0, 1, 0, 1}
//  5, //{0, 1, 0, 1}
//  9, //{1, 0, 0, 1}
//  15, //{1, 1, 1, 1}
//  1, //{0, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//
//  15, //{1, 1, 1, 1} //5
//  9, //{1, 0, 0, 1}
//  8, //{1, 0, 0, 0}
//  8, //{1, 0, 0, 0}
//  8, //{1, 0, 0, 0}
//  6, //{0, 1, 1, 0}
//  1, //{0, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  6, //{0, 1, 1, 0}
//
//  6, //{0, 1, 1, 0} //6
//  9, //{1, 0, 0, 1}
//  8, //{1, 0, 0, 0}
//  8, //{1, 0, 0, 0}
//  8, //{1, 0, 0, 0}
//  14, //{1, 1, 1, 0}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  6, //{0, 1, 1, 0}
//
//  15, //{1, 1, 1, 1} //7
//  1, //{0, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//  2, //{0, 0, 1, 0}
//  4, //{0, 1, 0, 0}
//  8, //{1, 0, 0, 0}
//  8, //{1, 0, 0, 0}
//  8, //{1, 0, 0, 0}
//
//  6, //{0, 1, 1, 0} //8
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  6, //{0, 1, 1, 0}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  6, //{0, 1, 1, 0}
//
//  6, //{0, 1, 1, 0} //9
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  7, //{0, 1, 1, 1}
//  1, //{0, 0, 0, 1}
//  1, //{0, 0, 0, 1}
//  9, //{1, 0, 0, 1}
//  6, //{0, 1, 1, 0}
//};

//byte countCharInLetter[0];
byte countCharInLetter[23] = {
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
  //4,  //x
  //5,  //y
  //4,  //z 
  //2,  //space
  //1,  //!
  //2,  //,
  //1,  //.
  //4,  //?
};

byte alphabetEng[230] ={
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

  13, //{0, 1, 1, 0, 0},  //c
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

  //18, //{1, 0, 0, 1, 0},   //x
  //18, //{1, 0, 0, 1, 0},
  //18, //{1, 0, 0, 1, 0},
  //18, //{1, 0, 0, 1, 0},
  //18, //{1, 0, 0, 1, 0},
  //12, //{0, 1, 1, 0, 0},
  //12, //{0, 1, 1, 0, 0},
  //18, //{1, 0, 0, 1, 0},
  //18, //{1, 0, 0, 1, 0},
  //18, //{1, 0, 0, 1, 0},

  //17, //{1, 0, 0, 0, 1},   //y
  //17, //{1, 0, 0, 0, 1},
  //17, //{1, 0, 0, 0, 1},
  //17, //{1, 0, 0, 0, 1},
  //10, //{0, 1, 0, 1, 0},
  //10, //{0, 1, 0, 1, 0},
  //4,  //{0, 0, 1, 0, 0},
  //4,  //{0, 0, 1, 0, 0},
  //4,  //{0, 0, 1, 0, 0},
  //4,  //{0, 0, 1, 0, 0},

  //30, //{1, 1, 1, 1, 0},   //z
  //2,  //{0, 0, 0, 1, 0},
  //2,  //{0, 0, 0, 1, 0},
  //2,  //{0, 0, 0, 1, 0},
  //4,  //{0, 0, 1, 0, 0},
  //12, //{0, 1, 1, 0, 0},
  //8,  //{0, 1, 0, 0, 0},
  //16, //{1, 0, 0, 0, 0},
  //16, //{1, 0, 0, 0, 0},
  //30, //{1, 1, 1, 1, 0},

  //0,    //space
  //0,
  //0,
  //0,
  //0,
  //0,
  //0,
  //0,
  //0,
  //0,

  //16, //{1, 0, 0, 0, 0}  //!
  //16, //{1, 0, 0, 0, 0}
  //16, //{1, 0, 0, 0, 0}
  //16, //{1, 0, 0, 0, 0}
  //16, //{1, 0, 0, 0, 0}
  //16, //{1, 0, 0, 0, 0}
  //16, //{1, 0, 0, 0, 0}
  //16, //{1, 0, 0, 0, 0}
  //0,  //{0, 0, 0, 0, 0}
  //16, //{1, 0, 0, 0, 0}

  //0, //{0, 0, 0, 0, 0}  //,
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //24, //{1, 1, 0, 0, 0}
  //8, //{0, 1, 0, 0, 0}

  //0, //{0, 0, 0, 0, 0}  //.
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //16, //{1, 0, 0, 0, 0}

  //12, //{0, 1, 1, 0, 0}  //?
  //2, //{1, 0, 0, 1, 0}
  //2, //{0, 0, 0, 1, 0}
  //2, //{0, 0, 0, 1, 0}
  //2, //{0, 0, 0, 1, 0}
  //4, //{0, 0, 1, 0, 0}
  //8, //{0, 1, 0, 0, 0}
  //8, //{0, 1, 0, 0, 0}
  //0, //{0, 0, 0, 0, 0}
  //8, //{0, 1, 0, 0, 0}
};

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(20);
  Serial.print("setup");
  for(int i=0; i<300; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,5)); 
    //pixels.show();
  }
  for (int i =0 ;i<300;i++){
    buf[i]=0; 
  }
  pixels.show();
}

void loop() {
if(stringComplete)
{
  pixels.setPixelColor(1, pixels.Color(0,0,250));
  pixels.show();
  Serial.println("strcomplete");
  Serial.println(inputString);
  stringComplete = false;
  getCommand();   //Формат команды: 1-4 команда, 5-7 красный, 8-10 зеленый, 11-13 синий, 14-15 режим, 16-... текст
  getColorToPrint();
  getModeToPrint();
  //Serial.print(Rcolor);
  //Serial.print(" | ");
  //Serial.print(Gcolor);
  //Serial.print(" | ");
  //Serial.print(Bcolor+1);
  //Serial.print(" | ");
  Serial.print(mode);
  Serial.println(commandString);
  if (commandString.equals("SNAK")){
    for (int i=0; i<count_led; i++)
    {
      getColorToPrint();
     if (i != 0) {
      lightLed(i-1, 0);
      lightLed(i, 1);
     }
     pixels.show();
     delay(50);
    }
    pixels.show();
    lightLed(count_led-1, 0);
    delay(50);
    pixels.show();
  }else  if(commandString.equals("TEXT")) {
    getColorToPrint();
    getModeToPrint();
    //Serial.print(Rcolor);
    //Serial.print(" | ");
    //Serial.print(Gcolor);
    //Serial.print(" | ");
    //Serial.print(Bcolor);
    //Serial.print(" | ");
    ///Serial.print(mode);
    String text = inputString.substring(16,inputString.length()-2);
    //Serial.print(" | ");
    //Serial.print(text);
    printText(text);
  } else if (commandString.equals("UGLV")) {
    getColorToPrint();
    getModeToPrint();
    //Serial.print(Rcolor);
    //Serial.print(" | ");
    //Serial.print(Gcolor);
    //Serial.print(" | ");
    //Serial.print(Bcolor+1);
    //Serial.print(" | ");
    Serial.print(mode);
    String pic = inputString.substring(16,inputString.length()-2);
    Serial.print(pic);
    printUgl(pic);
  }
  
  inputString = "";
}

}

void getColorToPrint(){
  if(inputString.length()>0)
  {
     temp = inputString.substring(5,8);
     Rcolor = temp.toInt();
     temp = inputString.substring(8,11); 
     Gcolor = temp.toInt();
     temp = inputString.substring(11,14); 
     Bcolor = temp.toInt();
  }
}

void getModeToPrint(){
  if(inputString.length()>0)
  {
     temp = inputString.substring(14,16); 
     mode = temp.toInt();
  }
}

void getCommand()
{
  if(inputString.length()>0)
  {
     commandString = inputString.substring(1,5);
  }
}

//String getTextToPrint()
//{
//  //Serial.print("len - ");
//  //Serial.println(inputString.length());
//  String value = inputString.substring(16,inputString.length()-2);
//  return value;
//}

void printUgl(String text){
  int ptr = 0; 
  int i;
  //setPicBuffer(text);
  int shiftAdd = 0; 
  if (mode == 4 ) shiftAdd = count_led;
  int j;
    for (i=0; i<10; i++)
    {
      int l = i*4;
      int r = (i+1)*4;
      Serial.print(l);
      Serial.print(" ");
      Serial.print(r); 
      temp = text.substring(l, r); 
      int row = temp.toInt();
      Serial.println(text);
      Serial.println(row);
      for (j=9; j>=0; j--)
      {
        Serial.print(row%2);
        Serial.print("->buf."); 
        Serial.println(i*10+(9-j)+shiftAdd);
        buf[i*10+(9-j)+shiftAdd] = row % 2; 
        row = row / 2; 
        Serial.println("!");
      }
      Serial.println("e_J");
    }
  Serial.println("e_I");
  delay(10);
  //Serial.println(text);
  //end set pic buffer
  Serial.print("init");
  delay(15);
  if (mode == 3)
  {
      for (i=0; i<20; i++)
      {
        Serial.println("-----SHift1()-----");
        shift1();
        pixels.show();
        delay(50);
      }
      ptr += 1;
    for (i=0; i<20; i++)
    {
      Serial.println("-------SHift3-----");
      shift3();
      pixels.show(); 
      delay(50);
    }
  }
  else 
  {
    for (i=0; i<20; i++){
      shift4(); 
      pixels.show(); 
      delay(150); 
    }
    for (i=0; i<20; i++){
      shift2();
      pixels.show();
      delay(150);
    }
  }
}

//void setPicBuffer(String pic){
//  int shiftAdd = 0; 
//  if (mode == 4 ) shiftAdd = count_led;
//  int j;
//    for (int i=0; i<10; i++)
//    {
//      int row = (pic.substring(i*4, (i+1)*4)).toInt();
//      Serial.println(pic);
//      Serial.println(row);
//      for (j=9; j>=0; j--)
//      {
//        Serial.print(row%2); 
//        buf[i*10+j+shiftAdd] = row % 2; 
//       row = row / 2; 
//      }
//    }
//    Serial.println(pic);
//}

void printText(String text)
{
    int ptr = 0; 
    int i;
    for (i = 0; i<count_led; i++) buf[i]==0; 
    Serial.print(" lenoftext ");
    Serial.print(text.length());
    while (ptr < text.length())
    {
      setBuffer(text[ptr]);
      for (i=0; i<countPtr; i++)
      {
        Serial.print("-------SHIFT!!!");
        Serial.print('\n');
        if (mode == 1) shift1();
        if (mode == 2) shift2(); 
        pixels.show();
        delay(150);
      }
      ptr += 1;
    }
    for (i=0; i<count_led/10; i++)
    {
      //Serial.print("-------SHIFT!!!");
      //Serial.print('\n');
      if (mode == 1) shift1();
      if (mode == 2) shift2(); 
      pixels.show(); 
      delay(150);
    }
}

void setBuffer(char c)
{
  Serial.println(c);
  if ((c>='a')&&(c<='z')) initBuffer(c-'a', false);
  if ((c>='0')&&(c<='9')) initBuffer(c-'0', true);
  if (c == ' ') initBuffer(26, false);
  
  if (c == '!') initBuffer(27, false); 
  if (c == ',') initBuffer(28, false); 
  if (c == '.') initBuffer(29, false); 
  if (c == '?') initBuffer(30, false);
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
      Serial.print(binBuffer[countPtr - j - 1]); 
      }
      if ((mode == 2) || (mode == 4)) buf[count_led+(i*10)+j] = binBuffer[j];
    }
    Serial.println("");
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
  for (int i=count_led+99; i >= 0; i--){
      
      if ((i>=100)&&(i%10==0)) buf[i]=buf[i-91]; 
      if ((i>=100)&&(i%10!=0)) buf[i]=buf[i-1];
      if ((i<100)&&(i%10==0)) buf[i]=0; 
      if ((i<100)&&(i%10!=0)) buf[i]=buf[i-1];
      if (i>=100) lightLed(i-100, buf[i]);
   }
   
   buf[0]=0; 
}

void shift2()
{
  for (int i=0; i < count_led+99; i++){
      if ((i<count_led)&&((i+1)%10==0)) buf[i]=buf[i+91]; 
      if ((i<count_led)&&((i+1)%10!=0)) buf[i]=buf[i+1];
      if ((i>=count_led)&&((i+1)%10==0)) buf[i]=0; 
      if ((i>=count_led)&&((i+1)%10!=0)) buf[i]=buf[i+1];
      if (i<count_led) lightLed(i, buf[i]);
   }
}


void shift3()
{
  int i;
  //Serial.println("from shift3");
  for (i = 300; i<390; i++)
  {
    buf[i] = buf[i+10]; 
    if (count_led>200) lightLed(i-100, buf[i]);
  }
  for (i=390; i<400; i++)
  {
    buf[i]=buf[i-190]; 
    if (count_led>200) lightLed(i-100, buf[i]);
  }
  for (i=200; i<290; i++){
    buf[i]=buf[i] = buf[i+10]; 
    lightLed(i-100, buf[i]);
  }
  for (i=290; i<300; i++){
    buf[i]=0;
    lightLed(i-100, buf[i]);
  }
}

void shift4()
{
  int i;
  Serial.println("shift4");
  delay(5);
  for (i=199; i>=100; i++)
  {
    if (i<110) buf[i] = buf[i+100];
      else buf[i] = buf[i-10];
    lightLed(i, buf[i]);
  }
  for (i=299; i>=200; i++)
  {
    if (i<210) buf[i] = buf[i+100];
      else buf[i] = buf[i-10];
    lightLed(i, buf[i]);
  }
}


void lightLed(int i, int state){
  if (state == 1) {pixels.setPixelColor(i, Rcolor, Gcolor, Bcolor);
  ///Serial.print(i);
  //Serial.print(" ");
  //Serial.print(Rcolor);
  //Serial.print(Gcolor);
  //Serial.print(Bcolor);
  //Serial.print('\n');
  }
  else pixels.setPixelColor(i, 0, 0, 0);
  //pixels.show();
  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    Serial.println(inChar);
    // add it to the inputString:
    inputString.concat(inChar);
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    Serial.println(inputString.length());
    if (inChar == '@') {
      stringComplete = true;
    }
  }
}


