#define UP true   //start with these settings
#define DOWN false
bool printline=true; //just to contol the serial monitor
int potpin = A0;
int potread;
float potwrite;

void Potentiomerter(){
  {potread=analogRead(potpin);
    potwrite=(255./1023.)*potread;} //arduino reads pot only to 1023 val. Based on this knowledge graph has been used to figure out the formula to convert 1023 max reading to 255. 
    // divide 255 by 1023 and multiply by the current(IMPORTANT!) reading. Remember to put a dot when using float integers.
     // Serial.print("pot val "); is off because it loads cpu too much
  //Serial.println(potwrite);
}


class button
{
  public:
  int pushbutton = 2;
int pushbuttonValue = 0;
int debounce = 250; 
unsigned long blinkMillis =0;
int lastbuttonval =0;
int blinkInterval6=120;
int count=0; //start count from 0
int led;
unsigned long time = 0;
int ledState =LOW;
int mode1();

button(int pin )
{
  led=pin;
  
}

void countbutton(){
   pushbuttonValue = digitalRead (pushbutton);
  if (pushbuttonValue == HIGH &&                                
      millis() - time > debounce ) {
         
  if (pushbuttonValue =! lastbuttonval && pushbuttonValue == HIGH ){ // if button value is not == to last button val ----count.

        
       count++;

      Serial.print("number of button pushes: "); //counts every button push.
      Serial.println(count);
      analogWrite(led, 0); // Maybe not the most efficient way to make sure all leds are off between switching modes, but it does the job.

    }
  else{
  count++; //count even if the statement is not true to avoid count skips.
      analogWrite(led, 0);
     
      Serial.print("number of button pushes: ");
      Serial.println(count);}
lastbuttonval=pushbuttonValue; //return the old value to the current
        
        if (count >=8 ) { // the reset count after 6 pushes
    ledState=LOW;

count=!count ;
  Serial.println("got to count reset ");
  } 
   if (count>=3){ // this makes sure everything is off before starting array modes.
   ledState=!ledState;

//i=4; //reset the variable so that it starts from led 1    
        
    }  
    time= millis();     
 }                                           
}

  

};




int button::mode1(){
     if (count ==1){
   if(printline==true){ //makes serial input the line only once.
         Serial.println("got to mode 1 ");
           printline=false;}
if (millis() - blinkMillis > blinkInterval6){
  
 analogWrite(led, potwrite);

 blinkMillis=millis();
 
   }
   
}
}

button object(2);
 
   button led1(11);
   button led2(10);
   button led3(9);
   button led4(6);
   button led5(5);


void setup() {
 Serial.begin(9600);
 pinMode(potpin, INPUT);

}

void loop() {
  {Potentiomerter();}  

//object.countbutton();
/*
led1.clean();
led2.clean();
led3.clean();
led4.clean();
led5.clean();

led1.mode1();
led2.mode1();
led3.mode1();
led4.mode1();
led5.mode1();
*/
}
