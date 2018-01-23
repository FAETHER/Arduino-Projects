// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledred = 2;
int ledblue = 3;
int ledorange = 4;
int ledyellow = 5;
int ledgreen = 6;
int led7 = 7;
int led8 = 8;
int led10= 10;
int led11 = 11;
int button = 12;
int buttonState = 0;        // variable for reading the button status
int ledState = 0;           // variable for reading the led status
int phaseMode = 0;         //What mode it is in (all on? police sirens? etc.)
int policeSiren = 0;
int debounce = 1000;
unsigned long blinkMillis =0;  //stores the time in milliseconds that the LED state blinked last.
unsigned long time = 0; //time is the last time the output pin was toggled
int ledBlinking = 0;  //what color blinks next
int blink = 0; //says if it is blinking, 0 = no 1 = yes
int custom = 0; //custom variable
int blinkInterval =  500; //this will speed up the simulation because of it's lag

void setup() {
  // initialize the digital pin as an output.
  pinMode(ledred, OUTPUT);
  pinMode(ledblue, OUTPUT);
  pinMode(ledorange, OUTPUT);
  pinMode(ledyellow, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void LedsOff()
{
  digitalWrite (ledred, 0);
  digitalWrite (ledblue, 0);
  digitalWrite (ledorange, 0);
  digitalWrite (ledyellow, 0);
  digitalWrite (ledgreen, 0);
  digitalWrite (led7, 0);
  digitalWrite (led8, 0);
  digitalWrite (led10, 0);
  digitalWrite (led11, 0);
}

void LedsOn()
{

  digitalWrite (ledred, 1);
  digitalWrite (ledblue, 1);
  digitalWrite (ledorange, 1);
  digitalWrite (ledyellow, 1);
  digitalWrite (ledgreen, 1);
   digitalWrite (led7, 1);
  digitalWrite (led8, 1);
  digitalWrite (led10, 1);
  digitalWrite (led11, 1);  
}

void ledBlink(){

  //Begin Blink Code
  if (blinkInterval < millis() - blinkMillis){ 
    // if the LED is off it turns on and if it is on it turns it off
    if (ledState == 0) {
      ledState = 1;
       Serial.println(ledState);
    } else 
    {
      ledState = 0;
       Serial.println(ledState);
    }
    digitalWrite(ledred, ledState);
    digitalWrite(ledblue, ledState);
    digitalWrite(ledorange, ledState);
    digitalWrite(ledyellow, ledState);  //sets the leds to the state of ledState
    digitalWrite(ledgreen, ledState);
    blinkMillis=millis(); //log time in milliseconds
    
  }
}

void ledCycle(){
  if (millis() - blinkMillis > blinkInterval){
    if (ledBlinking==0){//cycling to red
      digitalWrite (ledred, 1);
      digitalWrite (ledblue, 0);
      digitalWrite (ledgreen, 0);
      digitalWrite (ledorange, 0);
      digitalWrite (ledyellow, 0);  
      ledBlinking=1;
    }
    else if (ledBlinking==1){//cycling to orange
      digitalWrite (ledred, 0);
      digitalWrite (ledblue, 0);
      digitalWrite (ledgreen, 0);
      digitalWrite (ledorange, 1);
      digitalWrite (ledyellow, 0);
      ledBlinking=2;
    }
    else if (ledBlinking==2){//cycling to green
      digitalWrite (ledred, 0);
      digitalWrite (ledblue, 0);
      digitalWrite (ledgreen, 1);
      digitalWrite (ledorange, 0);
      digitalWrite (ledyellow, 0);
      ledBlinking=3;
    }
    else if (ledBlinking==3){//cycling to yellow
      digitalWrite (ledred, 0);
      digitalWrite (ledblue, 0);
      digitalWrite (ledgreen, 0);
      digitalWrite (ledorange, 0);
      digitalWrite (ledyellow, 1);
      ledBlinking=4;
    }
    else if (ledBlinking==4){//cycling to blue
      digitalWrite (ledred, 0);
      digitalWrite (ledblue, 1);
      digitalWrite (ledgreen, 0);
      digitalWrite (ledorange, 0);
      digitalWrite (ledyellow, 0);
      ledBlinking=0;
    }
    blinkMillis=millis();

  }

}           

void PoliceSirens(){

  if (millis() - blinkMillis > blinkInterval){
  if (policeSiren==0){
    digitalWrite (ledred, 1);
    digitalWrite (ledblue, 0);
    digitalWrite (ledgreen, 0);
    digitalWrite (ledorange, 0);
    digitalWrite (ledyellow, 0);
    policeSiren=1;
  }
  else{
       digitalWrite (ledred, 0);
    digitalWrite (ledblue, 1);
    digitalWrite (ledgreen, 0);
    digitalWrite (ledorange, 0);
    digitalWrite (ledyellow, 0);
    policeSiren=0;
  }
  
  Serial.println(policeSiren);
  blinkMillis=millis();
  }

}

void CustomPoliceSirens(){
  if (millis() - blinkMillis > blinkInterval){
    if (custom==0){//custom pattern begins (green and yellow sirens
    digitalWrite (ledred, 0);
    digitalWrite (ledblue, 0);
    digitalWrite (ledgreen, 1);
    digitalWrite (ledorange, 0);
    digitalWrite (ledyellow, 1);
    custom=1;
    }
    else if (custom==1){//blue and orange sirens
    digitalWrite (ledred, 0);
    digitalWrite (ledblue, 1);
    digitalWrite (ledgreen, 0);
    digitalWrite (ledorange, 1);
    digitalWrite (ledyellow, 0);
    custom=2;
    }
    else if (custom==2){//red and green sirens
    digitalWrite (ledred, 1);
    digitalWrite (ledblue, 0);
    digitalWrite (ledgreen, 1);
    digitalWrite (ledorange, 0);
    digitalWrite (ledyellow, 0);
    custom=0;
    }
  blinkMillis=millis();
             }
             }

void readpushbutton(){
  buttonState = digitalRead (button);

  if (  buttonState == 1 &&      
      millis() - time > debounce){       // the time it takes you to take your hand off the button   
    //"millis() - time > debounce" is checking to see if "millis()" is greater than "debounce" (50) away from the last time I read a button press.

    if (phaseMode == 0) {phaseMode = 1;}
    else if (phaseMode == 1) {phaseMode = 2;}
    else if (phaseMode == 2) {phaseMode = 3;}//if I wasn't blinking set blink to 1 so that I start blinking
    else if (phaseMode == 3) {phaseMode = 4;}
    else if (phaseMode == 4) {phaseMode = 5;}
    else if (phaseMode == 5) {phaseMode = 0;}
    time= millis(); 
    Serial.println(phaseMode);
    Serial.println("Mode:");
  }         //logs current time in milliseconds to "time" to keep track of how long it has been since I pressed the button. 
}             
             
      void loop() {     
        readpushbutton();
        if (phaseMode==0) {LedsOff();}
        if (phaseMode==1) {LedsOn();}
        if (phaseMode==2) {ledBlink();}
        if (phaseMode==3) {ledCycle();}
        if (phaseMode==4) {PoliceSirens();}
        if (phaseMode==5) {CustomPoliceSirens();}
      }
