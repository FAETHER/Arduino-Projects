const int ledPin1=10;
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int ledPin=11;  // Led pin at Arduino pin 9
int value;          // Store value from photoresistor (0-1023)
int brightness;
int ledPin2=9;
int ledPin3=6;
int ledPin4=5;

void setup(){
 pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 pinMode(ledPin3, OUTPUT);
 pinMode(ledPin4, OUTPUT);
}

void loop(){
  value = analogRead(pResistor);
  if (value > 500){
  analogWrite(ledPin, brightness);
  brightness= 15;
      for (int fadeValue = 0 ; fadeValue <= 15; fadeValue += 2) {  
 analogWrite(ledPin, fadeValue);
 delay (50);
    }

 for (int fadeValue = 20 ; fadeValue >= 0; fadeValue -= 2) {
 analogWrite(ledPin, fadeValue);
 delay(100);
 }
  }
  else{
    digitalWrite(ledPin, LOW); //Turn led on
  }

  value = analogRead(ledPin);
  if (value < 500) {
  analogWrite(ledPin1, brightness);
  brightness= 15;
  
   for (int fadeValue = 0 ; fadeValue <= 15; fadeValue += 2) {  
 analogWrite(ledPin1, fadeValue);
 delay (50);
   }
 for (int fadeValue = 20 ; fadeValue >= 0; fadeValue -= 2) {
 analogWrite(ledPin1, fadeValue);
 delay(100);
 }
   
  }
  value = analogRead(ledPin);
  if (value > 500){
  digitalWrite(ledPin1, LOW);
  }
  {
  delay(50); }

{
 analogWrite(ledPin2, brightness);
  brightness= 10;
  analogWrite(ledPin3, brightness);
  brightness= 10;
  analogWrite(ledPin4, brightness);
  brightness= 10;
}

{
  analogWrite(ledPin2, LOW);
  delay(500);
  analogWrite(ledPin2, HIGH);
  for(int i=0;i<3;i++);
  }
  {
     delay(500);
     analogWrite(ledPin3, LOW);
     delay(500);
     analogWrite(ledPin3, HIGH);
  }
  {
    delay(500);
     analogWrite(ledPin4, LOW);
     delay(500);
     analogWrite(ledPin4, HIGH);
  }
}
 


   

 
 

  
  

