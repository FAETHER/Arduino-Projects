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
  byte i =0;
  byte i4=0;
  int LEDstate=0x01; //start with 0001
  byte LEDpins[] ={11, 10, 9, 6, 5 };//mode 5 array
  boolean direction=UP;
int pushbutton = 2;
int blink = 0; //1 for yes 0 for no, we can also use true/false HIGH/LOW all of these will just be read as 0/1
int pushbuttonValue = 0;
unsigned long time = 0;         // the last time the output pin was toggled
int debounce = 250; 
int blinkInterval4=150;
int blinkInterval = 500; //half a second. 
unsigned long blinkMillis =0; //blinkMillis will store the time in milliseconds that I changed my LED state (blinked) last.
int ledState =LOW; //is my LED on or off? 0 for off, 1 for on. 
int lastbuttonval =0;
int count=0; //start count from 0
bool printline=true; //just to contol the serial monitor


void setup() {
  Serial.begin(9600);
 
    for (int x=0; x < 5; x++) // starts value x. checks that the value is <5. Increments value by 1.
    pinMode(LEDpins[x], OUTPUT);
    pinMode(ledPins[i], OUTPUT); //for this array everything included in loop

  pinMode(pushbutton, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
 
}
void loop(){
  
  
  pushbuttonValue = digitalRead (pushbutton);
  if (pushbuttonValue == HIGH &&                                
      millis() - time > debounce ) {
         
  if (pushbuttonValue =! lastbuttonval && pushbuttonValue == HIGH ){ // if button value is not == to last button val -count.
        
        count++;

      Serial.print("number of button pushes: "); //counts every button push.
      Serial.println(count);
    }
  else{
    count++; //count even if the statement is not true to avoid count skips.
   
     
      Serial.print("number of button pushes: ");
      Serial.println(count);}
lastbuttonval=pushbuttonValue; //return the old value to the current
  
 
   
  if (count ==1 ) {
 blink=30; //30 analog value && substitude to resistors
  Serial.print("got mode 1 ");
  } 
  

  
  if (count >=6 ) { // the reset count after 6 pushes
    blink=LOW;
count=!count ;
  Serial.print("got to count reset ");
  } 
   if (count==3){ // this makes sure everything is off before starting array modes.
    ledState=!ledState;
    blink=!blink;
  }

analogWrite(led, blink);
  analogWrite(led2, blink);
  analogWrite(led3, blink);
  analogWrite(led4, blink);
analogWrite(led5, blink);                                                                
    
    time= millis();    
                                                   
    }                                                      
 
       
if (millis() - blinkMillis > blinkInterval && count==2){ //mode 2 blink all.
   blinkMillis=millis();
   Serial.println("got to mode 2 ");
     if (ledState == LOW && blink == 30) {
      ledState = 30;
      Serial.print(" = 30 ");
    } else {
      ledState = LOW;
       Serial.print(" = 0 ");
    }
 
analogWrite(led, ledState);
 analogWrite(led2, ledState);
analogWrite(led3, ledState);
 analogWrite(led4, ledState);
analogWrite(led5, ledState);
  }
  
  
if(count==3 && blink==0){
  
Serial.println("got to mode 3 ");

    
    if (millis() - blinkMillis > blinkInterval) {
    blinkMillis = millis();

    if ( i < sizeof(ledPins) - 1 ) {
      // Turn off previous led
     
      digitalWrite(ledPins[i], LOW);

      // Turn on the next led. notice that ++ before i increments and returns the old value.
      analogWrite(ledPins[++i ], 30);
    }

    else if  (i == sizeof(ledPins) - 1 )   {
      // if i will == to 5(length of array) -1 start array over again
      i = 0;
     
      analogWrite(ledPins[i ], 30); 
      digitalWrite(ledPins[ sizeof(ledPins) - 1 ], LOW); //turns off everything not supposed to be on
      
    }
  }
}

  
if(count==4 && blink==0){   //same code as 3 but shorter array.
  Serial.println("got to mode 4 ");
  if (millis() - blinkMillis > blinkInterval4) {
   blinkMillis = millis();

   if ( i4 < sizeof(ledPins2) - 1 ) {
      // Turn off previous led
     
      digitalWrite(ledPins2[i4], LOW);

      // Turn on the next led
      analogWrite(ledPins2[++i4 ], 30);
    }

    else if  (i4 == sizeof(ledPins2) - 1 )   {
 
      i4 = 0;
     
      analogWrite(ledPins2[i4 ], 30);
      digitalWrite(ledPins2[ sizeof(ledPins2) - 1 ], LOW);
      
    }
  }
}

if(count==5 && blink==0){
  if(printline==true){ //makes serial input the line only once.
Serial.print("got to mode 5 ");
printline=false;}

    for (int x=0; x < 5; x++)
     digitalWrite(LEDpins[x], bitRead(LEDstate,x));
 

  
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
        LEDstate = 0x01; // restart array
        direction = UP;
       
      }
    }
  }
}
}   





 
