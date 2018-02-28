
#include <LiquidCrystal.h>
const int out=3;
const int in=2;
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(out,OUTPUT);
  pinMode(in,INPUT);
  // number of columns and rows
   lcd.begin(16, 2);
}
void loop() {
  // put your main code here, to run repeatedly:
  long dur;
  long dis;
  long inches;
  long cm;
  digitalWrite(out,LOW);
  delayMicroseconds(2);
  digitalWrite(out,HIGH);
  delayMicroseconds(10);
  digitalWrite(out,LOW);
  dur=pulseIn(in,HIGH);
  // Serial.println(String(dur));
  // convert the time into a distance
    inches = microsecondsToInches(dur);
    cm = microsecondsToCentimeters(dur);
    lcd.print("Inches: ");
    lcd.print(inches);
    lcd.setCursor(0,1) ; 
    lcd.print("Cm: ");
    lcd.print(cm);
    
      
    Serial.print(inches);
    Serial.print(" in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
  delay(1000);
  lcd.clear();
}
  long microsecondsToInches(long microseconds) {
    // According to Parallax's datasheet for the PING))), there are
    // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
    // second).  This gives the distance travelled by the ping, outbound
    // and return, so we divide by 2 to get the distance of the obstacle.
    // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
  }
  long microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
  return microseconds / 29 / 2;
  }
