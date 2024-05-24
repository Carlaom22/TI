int ledPin1 = 6, ledPin2 = 7, ledPin3 = 8, ledPin4 = 9, ledPin5 = 10; 
int buttonPin = 5;

int lastButtonState = 0; 
int buttonPressCounter = 0; 
unsigned long tempo = 0; 

int tempojogo = 15000; 
void setup() {
  Serial.begin(9600); 

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(buttonPin, INPUT); 
}

void loop() {

  int randNumber = random(1, 31);
  int bit0 = bitRead(randNumber,0);
  int bit1 = bitRead(randNumber,1);
  int bit2 = bitRead(randNumber,2);
  int bit3 = bitRead(randNumber,2);
  int bit4 = bitRead(randNumber,4);

  digitalWrite(ledPin1, bit0);
  digitalWrite(ledPin2, bit1);
  digitalWrite(ledPin3, bit2);
  digitalWrite(ledPin4, bit3);
  digitalWrite(ledPin5, bit4);

  Serial.println("Tens 15 segundos para acertar"); 
  Serial.println(); 

  tempo = millis(); 
  int comeca = 1; 
  buttonPressCounter = 0; 
  Serial.println(buttonPressCounter);

  while (comeca && (millis() - tempo < tempojogo)) {
    int buttonState = digitalRead(buttonPin); 
    if (buttonState != lastButtonState) { 
      if (buttonState == HIGH) {
        buttonPressCounter = buttonPressCounter + 1; 
        Serial.println(buttonPressCounter); 
        if (buttonPressCounter > 31) buttonPressCounter = 0; 
      }
      delay(10);
    }

    lastButtonState = buttonState;
    unsigned long buttonPressTime = millis();
    while ((digitalRead(buttonPin) == HIGH ) && comeca) { 
      if (millis() - buttonPressTime > 1000)
        comeca = 0; 
    }
  }

  if (comeca && (buttonPressCounter == randNumber)) { 
    Serial.println("Vitória"); 

    
    for (int pin = 6; pin <= 10; pin++) {
      digitalWrite(pin, HIGH);
      delay(200);
    }
    for (int pin = 6; pin <= 10; pin++) {
      digitalWrite(pin, LOW);
      delay(200);
    }
    for (int pin = 10; pin >= 6; pin--) {
      digitalWrite(pin, HIGH);
      delay(200);
    }
    for (int pin = 10; pin >= 6; pin--) {
      digitalWrite(pin, LOW);
      delay(200);
    }

    Serial.println("-----------------------"); 
    Serial.println();
    comeca = 0;
  }

  else if (comeca) { 
    Serial.print("Errado, o número era: ");
    Serial.println(randNumber); 
    Serial.println("-----------------------");
    Serial.println(); 
    comeca = 0; 
  }
}
