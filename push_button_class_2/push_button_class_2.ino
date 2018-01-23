#define UP true   //start with these settings
#define DOWN false
bool printline=true; //just to contol the serial monitor
int potpin = A0;
int potread;
float potwrite;
int pushbutton = 2;
int pushbuttonValue = 0;
int debounce = 250;
int lastbuttonval =0;
unsigned long time = 0;
int count=0;

void countbutton(){

  
  pushbuttonValue = digitalRead (pushbutton);
  if (pushbuttonValue == HIGH &&                                
      millis() - time > debounce ) {
         
  if (pushbuttonValue =! lastbuttonval && pushbuttonValue == HIGH ){ // if button value is not == to last button val ----count.
        
        count++;

      Serial.print("number of button pushes: "); //counts every button push.
      Serial.println(count);
        analogWrite(6, 0); // Maybe not the most efficient way to make sure all leds are off between switching modes, but it does the job.
 analogWrite(5, 0);// I changed this because the gl. val "blink" has been completely removed. 
analogWrite(11, 0);
 analogWrite(10, 0);
analogWrite(9, 0);
    }
  else{
    count++; //count even if the statement is not true to avoid count skips.
 analogWrite(6, 0); // Maybe not the most efficient way to make sure all leds are off between switching modes, but it does the job.
 analogWrite(5, 0);// I changed this because the gl. val "blink" has been completely removed. 
analogWrite(11, 0);
 analogWrite(10, 0);
analogWrite(9, 0);

      Serial.print("number of button pushes: ");
      Serial.println(count);}
lastbuttonval=pushbuttonValue; //return the old value to the current
        
        if (count >=7 ) { // the reset count after 6 pushes
count=!count ;
  Serial.println("got to count reset ");
  } 
  
   if (count>=3){ // this makes sure everything is off before starting array modes.
  
  }                                            
    time= millis();    
                                                   
    }                                                      

}

class kyryl{
  
public:
int led;
//int blinkInterval6 =120;
int ledState=LOW;
unsigned long blinkMillis =0;
long  blinkInterval;

kyryl(int pin, long cheese )
{
  led=pin;
 blinkInterval=cheese;
}
void mode1(){
   if (count ==1){
   if(printline==true){ //makes serial input the line only once.
         Serial.println("got to mode 1 ");
           printline=false;}

  
 analogWrite(led, 40);
    
   }      
}
void mode2(){
if (millis() - blinkMillis > blinkInterval && count==2){ //mode 2 blink all.
   blinkMillis=millis();
   if(printline==false){ //makes serial input the line only once.
         Serial.println("got to mode 2 ");
           printline=true;}
     if (ledState == LOW) {
      ledState = 40;
      Serial.println(" = 1 ");
    } else {
      ledState = LOW;
       Serial.println(" = 0 ");
    }
analogWrite(led, ledState);

 
  }
}
void mode3(){
 if (count ==3){
   if(printline==true){ //makes serial input the line only once.
         Serial.println("got to mode 3 ");
           printline=false;}
if (millis() - blinkMillis > blinkInterval) {
 blinkMillis = millis();     
 
  for(int led; led<5; led++)

  analogWrite(led, 40);
  delay(500);
  Serial.println(led);
  
  }
}
}
};

kyryl led1(11, 550);
   kyryl led2(10, 300);
   kyryl led3(9, 100);
   kyryl led4(6, 700);
   kyryl led5(5, 250);


void setup() {
 Serial.begin(9600);
 pinMode(potpin, INPUT);

}

void loop() {
{countbutton();}

led1.mode1();
led2.mode1();
led3.mode1();
led4.mode1();
led5.mode1();

led1.mode2();
led2.mode2();
led3.mode2();
led4.mode2();
led5.mode2();

led1.mode3();
led2.mode3();
led3.mode3();
led4.mode3();
led5.mode3();
}
