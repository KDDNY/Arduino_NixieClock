#include <Arduino.h>
#include <Dictionary.h>
#include <NodeArray.h>

const int ser = 2;
const int clk = 3;
const int latch = 4;


Dictionary &tube1 = *(new Dictionary(3));
Dictionary &tube2 = *(new Dictionary(10));
Dictionary &tube3 = *(new Dictionary(6));
Dictionary &tube4 = *(new Dictionary(10));

void clkPulse(){
  digitalWrite(clk, HIGH);
  digitalWrite(clk, LOW);
}

void latchPulse(){
  digitalWrite(latch, HIGH);
  digitalWrite(latch, LOW);
}

void clear(){
  for (int i = 0; i < 32; i++){
    digitalWrite(ser, LOW);
    latchPulse();
  }
  clkPulse();
}

int bits[4] = {0,0,0,0};

int *getBits(int h1, int h2, int m1, int m2){
  String temp = String(h1);
  String temp1 = String(h2);
  String temp2 = String(m1);
  String temp3 = String(m2);
  bits[0] = tube1[temp].toInt();
  bits[1] = tube2[temp1].toInt();
  bits[2] = tube3[temp2].toInt();
  bits[3] = tube4[temp3].toInt();
  return bits;
}

void serLatch(){
  digitalWrite(latch, HIGH);
  digitalWrite(latch, LOW);
}

void putForward(int x){
  digitalWrite(ser, HIGH);
  serLatch();
  digitalWrite(ser, LOW);
  for(int i = 0; i < x; i++){
    serLatch();
  }
  clkPulse();
}

void display(int h1, int h2, int m1, int m2){
  int *pointer = getBits(h1, h2, m1, m2);
  for( int i = 0; i < 4; i++ )
    {
        for( int j = 0; j < 4 - 1; j++ )
        {
            if( *(pointer + j ) < *(pointer + j + 1 ) ){
              int temp = *(pointer + j );
              *(pointer + j ) = *(pointer + j + 1);
              *(pointer + j + 1) = temp;
            }
        }
    }
   putForward(*pointer - *(pointer+1)-1);
   putForward(*(pointer + 1) - *(pointer + 2)-1);
   putForward(*(pointer + 2) - *(pointer + 3)-1);
   putForward(*(pointer + 3));
}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ser, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  Serial.begin(9600);
  digitalWrite(ser, LOW);
  digitalWrite(clk, LOW);
  digitalWrite(latch, LOW);
  tube1("0","19");
  tube1("1","17");
  tube1("2","18");
  tube2("0","27");
  tube2("1","20");
  tube2("2","21");
  tube2("3","22");
  tube2("4","23");
  tube2("5","16");
  tube2("6","10");
  tube2("7","30");
  tube2("8","29");
  tube2("9","28");
  tube3("0","13");
  tube3("1","12");
  tube3("2","14");
  tube3("3","15");
  tube3("4","8");
  tube3("5","26");
  tube4("0","1");
  tube4("1","9");
  tube4("2","11");
  tube4("3","0");
  tube4("4","6");
  tube4("5","7");
  tube4("6","5");
  tube4("7","4");
  tube4("8","3");
  tube4("9","2");
  clear();
}

void loop() {
  display(random(0,3),random(0,10),random(0,6),random(0,10));
  delay(80);
  clear();
}
