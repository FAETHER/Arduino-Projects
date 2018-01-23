class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  unsigned long buttonPressedTime;
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time
  int StartTimeDelay;
  Flasher(int pin, long on, long off, long startat)
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);     

    OnTime = on;
    OffTime = off;
    StartTimeDelay=startat;

    ledState = 0; 
    previousMillis = 0;
  }

  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
  unsigned long StartAtMillis = buttonPressedTime+StartTimeDelay;
   if(OffTime==0){
     digitalWrite(ledPin, HIGH);
   }else if(OnTime==0){
     digitalWrite(ledPin, LOW);
   }else if (currentMillis>=(StartAtMillis) &&
        ledState ==0)
        {
            if(((currentMillis - previousMillis) >= OffTime) || ((previousMillis - buttonPressedTime) <=StartTimeDelay))
      {
        previousMillis = currentMillis;
        ledState=HIGH;
        digitalWrite(ledPin, ledState);
      }
        }
    
    else if(ledState ==HIGH &&
            (currentMillis - previousMillis) >= OnTime
           )
    {
      previousMillis = currentMillis;
      ledState=LOW;
      digitalWrite(ledPin, ledState);
    }




  }

  void NewTimings(long on, long off, long startat)
  {
    OnTime = on;
    OffTime = off;
    StartTimeDelay=startat;

    ledState = 0;  
    previousMillis = millis();
  }  

};


Flasher led1(5, 0, 1000, 0);
Flasher led2(6, 0, 1000,0);
Flasher led3(9, 0, 1000,0);
Flasher led4(10, 0, 1000,0);
Flasher led5(11, 0, 1000,0);

void setup()
{
  Serial.begin(9600);
}

int mode;
int pushbuttonValue =0;
int pushbuttonpin =2;
unsigned long currentTime;
int debounce =250;
int runSinceIPressedButton =true;
void loop()
{
  led1.Update();
  led2.Update();
  led3.Update();
  led4.Update();
  led5.Update();
  pushbuttonValue = digitalRead (pushbuttonpin);
  if (  pushbuttonValue == HIGH && //if I read that my button is pressed...&& just means "and" 
      millis() - currentTime > debounce) {
    currentTime = millis();
    led1.buttonPressedTime = currentTime;
    led2.buttonPressedTime = currentTime;
    led3.buttonPressedTime = currentTime;
    led4.buttonPressedTime = currentTime;
    led5.buttonPressedTime = currentTime;
    mode++;
    runSinceIPressedButton = false;
    if (mode==6) {mode =0;}
  Serial.println(mode);
  }
  if (mode==0 && !runSinceIPressedButton){
    led1.NewTimings(0,100,0);
    led2.NewTimings(0,100,0);
    led3.NewTimings(0,100,0); //All Off
    led4.NewTimings(0,100,0);
    led5.NewTimings(0,100,0);
    runSinceIPressedButton = 1;
  }
  else if (mode==1 && !runSinceIPressedButton){
    led1.NewTimings(100,0,0);
    led2.NewTimings(100,0,0);
    led3.NewTimings(100,0,0);   //All On
    led4.NewTimings(100,0,0);
    led5.NewTimings(100,0,0);
    runSinceIPressedButton = 1;
  }else if(mode==2 && !runSinceIPressedButton){
    led1.NewTimings(500,500,0);
    led2.NewTimings(500,500,0);
    led3.NewTimings(500,500,0);   //All Blinking
    led4.NewTimings(500,500,0);
    led5.NewTimings(500,500,0);
    runSinceIPressedButton =1;
  }else if(mode==3 && !runSinceIPressedButton){
    led1.NewTimings(250,1000,0);
    led2.NewTimings(250,1000,250);
    led3.NewTimings(250,1000,500);   //Chasing
    led4.NewTimings(250,1000,750);
    led5.NewTimings(250,1000,1000);
    runSinceIPressedButton =1;
  }
}
