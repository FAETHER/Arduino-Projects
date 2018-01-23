#define UP true   //start with these settings
#define DOWN false

int led =11;
int led2=10;
int led3=9;
int led4=6;
int led5=5;
byte ledPins[] = {
  11, 10, 9, 6, 5, }; //mode 3 array
  byte ledPins2[] ={11, 10, }; //mode 4 array
  byte i =0; //mode 3 array index
  byte i4=0;// mode 4 array index
  int LEDstate=0x01; //start with 00000001 in binary which is just 1 in decimal same x will be used for array index (IMPORTANT!)
  byte LEDpins[] ={11, 10, 9, 6, 5 };//mode 5 array
  byte LEDpins2[] ={11, 10, 9, 6, 5 };
  boolean direction=UP;//set up direction as the starting one
int pushbutton = 2;
int pushbuttonValue = 0;
unsigned long time = 0;         // the last time the output pin was toggled
int debounce = 250; 
int blinkInterval4=150;
int blinkInterval6=120;
int blinkInterval = 500; //half a second. 
unsigned long blinkMillis =0;//blinkMillis will store the time in milliseconds that I changed my LED state (blinked) last.
unsigned long blinkMillis2 =0;
int ledState =LOW; //is my LED on or off? 0 for off, 1 for on. 
int lastbuttonval =0;
int count=0; //start count from 0
bool printline=true; //just to contol the serial monitor
int brightness = 0;    // how bright the LED is
int potpin = A0;
int potread;
float potwrite;

void setup() {
  Serial.begin(9600);
 
  for (int x=0; x < 5; x++) // starts value x. checks that the value is <5 (number is based on the length of an array) . Increments value by 1 with every loop.
  pinMode(LEDpins[x], OUTPUT);
  pinMode(ledPins[i], OUTPUT); //for is not used.  this array everything included in loop
  pinMode(potpin, INPUT);
  pinMode(pushbutton, INPUT);
  
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
}
void Potentiomerter(){
  {potread=analogRead(potpin);
    potwrite=(255./1023.)*potread;} //arduino reads pot only to 1023 val. Based on this knowledge graph has been used to figure out the formula to convert 1023 max reading to 255. 
    // divide 255 by 1023 and multiply by the current(IMPORTANT!) reading. Remember to put a dot when using float integers.
     // Serial.print("pot val "); is off because it loads cpu too much
  //Serial.println(potwrite);
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
 analogWrite(led2, 0);// I changed this because the gl. val "blink" has been completely removed. 
analogWrite(led3, 0);
 analogWrite(led4, 0);
analogWrite(led5, 0);
    }
  else{
    count++; //count even if the statement is not true to avoid count skips.
      analogWrite(led, 0);
 analogWrite(led2, 0);
analogWrite(led3, 0);
 analogWrite(led4, 0);
analogWrite(led5, 0);
     
      Serial.print("number of button pushes: ");
      Serial.println(count);}
lastbuttonval=pushbuttonValue; //return the old value to the current
        
        if (count >=7 ) { // the reset count after 6 pushes
    ledState=LOW;
potwrite=!potwrite;
count=!count ;
  Serial.println("got to count reset ");
  } 
   if (count==3){ // this makes sure everything is off before starting array modes.
   ledState=!ledState;
potwrite=!potwrite;
  }                                            
    time= millis();    
                                                   
    }                                                      

}
void mode1(){
   if (count ==1){
   if(printline==true){ //makes serial input the line only once.
         Serial.println("got to mode 1 ");
           printline=false;}

  
 analogWrite(led, potwrite);
  analogWrite(led2, potwrite);
  analogWrite(led3, potwrite);
  analogWrite(led4, potwrite);
analogWrite(led5, potwrite);    
   }
      
}

   void  mode2(){   
   
if (millis() - blinkMillis > blinkInterval && count==2){ //mode 2 blink all.
   blinkMillis=millis();
   if(printline==false){ //makes serial input the line only once.
         Serial.println("got to mode 2 ");
           printline=true;}
     if (ledState == LOW) {
      ledState = potwrite;
      Serial.println(" = 1 ");
    } else {
      ledState = LOW;
       Serial.println(" = 0 ");
    }
analogWrite(led, ledState);
 analogWrite(led2, ledState);
analogWrite(led3, ledState);
 analogWrite(led4, ledState);
analogWrite(led5, ledState);
 
  }
   
   }

  void mode3(){
if(count==3 ){
  if(printline==true){ //makes serial input the line only once.
         Serial.println("got to mode 3 ");
           printline=false;}

    if (millis() - blinkMillis > blinkInterval) {
    blinkMillis = millis();

    if ( i < sizeof(ledPins) - 1 ) {
      // Turn off previous led
     
      digitalWrite(ledPins[i], LOW);

      // Turn on the next led. notice that ++ before i increments and returns the old value.
      analogWrite(ledPins[++i ], potwrite);
    }

    else if  (i == sizeof(ledPins) - 1 )   {
      // if i will == to 5(length of array) -1 start array over again
      i = 0;
     
      analogWrite(ledPins[i ], potwrite); 
      digitalWrite(ledPins[ sizeof(ledPins) - 1 ], LOW); //turns off everything not supposed to be on
      // (NOTE!) the starting point of an array will be at the last led that was turned off. I did not bother making it start from 1-5.
    }
  }
}
  }
  
  void mode4(){
if(count==4 ){   //same code as 3 but shorter array.
  if(printline==false){ //makes serial input the line only once.
         Serial.println("got to mode 4 ");
           printline=true;}
  if (millis() - blinkMillis > blinkInterval4) {
   blinkMillis = millis();

   if ( i4 < sizeof(ledPins2) - 1 ) {
      // Turn off previous led
     
      digitalWrite(ledPins2[i4], LOW);

      // Turn on the next led
      analogWrite(ledPins2[++i4 ], potwrite);
    }

    else if  (i4 == sizeof(ledPins2) - 1 )   {
 
      i4 = 0;
     
      analogWrite(ledPins2[i4 ], potwrite);
      digitalWrite(ledPins2[ sizeof(ledPins2) - 1 ], LOW);
      
    }
  }
}
  }

  void mode5(){
if(count==5){
  if(printline==true){ //makes serial input the line only once.
Serial.println("got to mode 5 ");
printline=false;}

    for (int x=0; x < 5; x++)
  // analogWrite(LEDpins[x], bitRead(LEDstate,x));
 
  
  if(bitRead(LEDstate,x)==1){
  analogWrite(LEDpins[x],potwrite); 
    }else{
      analogWrite(LEDpins[x],0); }
    
 
  
  if (millis() - blinkMillis > blinkInterval) {
    blinkMillis = millis();

  if (direction==UP) {
      // Use "<<" to "bit-shift" everything to the left once
      LEDstate = LEDstate << 2;
     
      // 0x20 is the "last" LED, another shift makes the value 0x40
      if (LEDstate == 0x40) {
        // turn on the one before "0x40" and reverse direction
        LEDstate = 0x20; //return to lower value
        direction = DOWN;
        
      }
      Serial.print("LEDstate: "); //used for timing needs.
      Serial.println(LEDstate,BIN);
      Serial.print("direction: ");
      Serial.println(direction);
      
    }
    else {
      // use ">>" to "bit-shift" all bits in LEDstate once to the right
     LEDstate = LEDstate >> 1;
      // This means we ran out of bits!
      if (LEDstate == 0x00) {
         Serial.print("run out of bits ");
        LEDstate = 0x01; // restart array. restart direction.
        direction = UP;
       
      }
       
    }
  }
}
  }
  void mode6(){
    
    if(count==6 ){
       if(printline==true){ //makes serial input the line only once.
         Serial.println("got to mode 6 ");
           printline=false;}
   for (int i=0; i < 5; i++) 
   
    if (millis() - blinkMillis > blinkInterval6) {
    blinkMillis = millis();
   
   int n = random(0, 5);  // Integer from 0 to 5
 // brightness = brightness + fadeAmount;
 analogWrite(LEDpins2[n],potwrite);
    }
       if (millis() - blinkMillis2 > blinkInterval4) {
    blinkMillis2 = millis();
     int n = random(0, 5);
// if(digitalRead(i)==HIGH){

analogWrite(LEDpins2[n],0);
 
  
  }
  
    
  }
  }
  
  
  void loop(){ //nice little tweaks, mode order can be changed here.
    {Potentiomerter();}  
    {countbutton();}
    {mode1();}
    {mode2();}
    {mode3();}
    {mode4();}
    {mode5();}
    {mode6();}
  }




 
