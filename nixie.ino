#include <Dictionary.h>
#include <NodeArray.h>

const int ser = 2;
const int clk = 3;
const int latch = 4;

  int x = 0;
  int y = 0;
  int z = 0;

  int h1 = 1;
  int h2 = 1;
  int m1 = 2;
  int m2 = 2;
  
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
  tube1("0","22");
  tube1("1","21");
  tube1("2","26");
  tube2("0","27");
  tube2("1","12");
  tube2("2","18");
  tube2("3","30");
  tube2("4","29");
  tube2("5","19");
  tube2("6","17");
  tube2("7","28");
  tube2("8","23");
  tube2("9","13");
  tube3("0","14");
  tube3("1","10");
  tube3("2","15");
  tube3("3","1");
  tube3("4","8");
  tube3("5","20");
  tube4("0","2");
  tube4("1","9");
  tube4("2","0");
  tube4("3","5");
  tube4("4","16");
  tube4("5","11");
  tube4("6","7");
  tube4("7","4");
  tube4("8","6");
  tube4("9","3");
  clear();
 // putForward(2);
  }

void demo1(){
   if(x>2) x = 0;
    if(y>9) y = 0;
    if(z>5) z = 0;
    display(x,y,z,y);
    delay(500);
    clear();
    x++;
    y++;
    z++;
}

void clock(){
  display(h1,h2,m1,m2);
  delay(60000);
  m2++;
  if(m2 == 10){
    m2 = 0;
    m1++;
    if(m1 == 6){
      m1 = 0;
      h2++;
      if(h2 == 10){
        h2 = 0;
        h1++;
        if(h1 == 3) h1 = 0;
      }
    }
  }
  clear();
}

void loop() {
demo1();}
