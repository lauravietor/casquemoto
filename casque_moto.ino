int const photoRPin = A2;
int const buttonPin = A1;
int const potPin = A0;

int ledGPin = 10;
int ledRPin = 11;


void setup() {
  Serial.begin(9600);

  pinMode(ledGPin, OUTPUT);
  pinMode(ledRPin, OUTPUT);

  digitalWrite(ledGPin, LOW);
  digitalWrite(ledRPin, LOW);
}


void loop() {
  int photoRVal = analogRead(photoRPin);
  if (photoRVal > 900) {
    digitalWrite(ledGPin, HIGH);

    int buttonVal = analogRead(buttonPin);
    if (buttonVal > 950) {
      digitalWrite(ledRPin, HIGH);

      int potVal = analogRead(potPin);
      Serial.print("Position : ");
      Serial.println(potVal);
    }
    else {
      digitalWrite(ledRPin, LOW);
    }
  }
  else {
    digitalWrite(ledGPin, LOW);
  }

  delay(100);
}
