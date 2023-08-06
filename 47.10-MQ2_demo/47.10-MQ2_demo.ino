int analogPin = A0; // connected to the A0 pin of the MQ-2 module
int digitalPin = 2; // connected to the D0 pin of the MQ-2 module
int gasDetectedPin = LED_BUILTIN; //If a gas is detected, the build-in LED will turn on.

void setup() {
  Serial.begin(9600); // initializes serial communication
  pinMode(analogPin, INPUT);
  pinMode(digitalPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int analogValue = analogRead(analogPin);
  bool digitalValue = digitalRead(digitalPin);

  digitalWrite(LED_BUILTIN, !digitalValue);

  Serial.print("Analog value: ");
  Serial.print(analogValue);
  Serial.print(", Digital value: ");
  Serial.println(digitalValue);

  delay(1000); // delay for a second
}