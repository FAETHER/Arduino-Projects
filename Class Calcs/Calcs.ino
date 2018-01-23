#include <math.h>
int i=0;
class math
{
  public:
 math(double a, double b);

double mult();
double add();
double sub();
double div();
  
  private:
  double _a;
  double _b;

};

math::math(double a, double b)
{
  _a=a;
   _b=b;

}

double math::mult(){
  return (_a * _b);
}
double math::add(){
  return (_a + _b);
}
double math::sub(){
  return (_a - _b);
}
double math::div(){
  return (_a)/(_b);
}

math math1(5, 2);
math math2(18,11);
math math3(2,2);

void setup(){
  Serial.begin(9600);
}

void loop(){
    Serial.println(" ");
    Serial.println("add ");
Serial.println(math1.add());
Serial.println(math2.add());
Serial.println(math3.add());
  Serial.println("sub ");
Serial.println(math1.sub());
Serial.println(math2.sub());
Serial.println(math3.sub());
  Serial.println("mult ");
Serial.println(math1.mult());
Serial.println(math2.mult());
Serial.println(math3.mult());
  Serial.println("div ");
Serial.println(math1.div());
Serial.println(math2.div());
Serial.println(math3.div());
  Serial.println(" ");


for(int x=i; x<5; x++){ //this will run only 5 times
    digitalRead(5);
    Serial.println("x value:  ");
    Serial.println(x);
if(x==4)
i=6;
//break;

}
  

}




