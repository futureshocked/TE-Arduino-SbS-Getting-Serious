int analogPin = A0; // connected to the AOUT pin of the MiCS-2714 module
int ledPin = 13; // built-in LED
int threshold = 183; // set your threshold value based on your requirements

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // initializes serial communication
}

void loop() {
  int analogValue = analogRead(analogPin);

  Serial.print("NO2 level: ");
  Serial.println(analogValue);

  if(analogValue > threshold) {
    Serial.println("High NO2 concentration detected! Possible leakage.");
    digitalWrite(ledPin, HIGH); // Turn the LED on
  } else {
    digitalWrite(ledPin, LOW); // Turn the LED off
  }
  
  delay(1000); // delay for a second
}