
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int val=0;
int read=A0;
int power=7;
int led=8;
int sensorMax=950;
int percent;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(power,OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite(power, LOW);
  
}

void loop() {
  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  lcd.print("Value:");
  lcd.print(readSoil());
  lcd.setCursor(0,1) ; 
  lcd.print("Percentage:");
  lcd.print(percentage());
  lcd.print("%");
  lcd.display();
  delay(500);  
  lcd.clear();
}

int readSoil()
{

    digitalWrite(power, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds 
    val = analogRead(read);//Read the SIG value form sensor 
    digitalWrite(power, LOW);//turn D7 "Off"
    if(val>=50)
    {
      digitalWrite(led, HIGH);
    }
    else
    {
      digitalWrite(led,LOW);
    }
    return val;//send current moisture value
}
int percentage()
{
if(val==900)
{
  percent=100;
}
if (val<900)
{
  percent=val*100/900;
}
return percent;
  
}

