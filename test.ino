int multiRedPin = 2;  // the PWM pin the LED is attached to
int multiGreenPin = 3;
int multiBluePin = 4;
int xPin = A0;
int yPin = A1;
int btnPin = 13;
int tick = 0;
bool pause = false;

void setup() {
    pinMode(multiRedPin, OUTPUT);
    pinMode(multiGreenPin, OUTPUT);
    pinMode(multiBluePin, OUTPUT);
    pinMode(btnPin, INPUT);
    Serial.begin(9600);
}

void loop() {
    tick++;
    if (tick % 500 == 0) {
        Serial.print("Tick: ");
        Serial.println(tick);
    }
    int btnVal = digitalRead(btnPin);
    int x = analogRead(xPin);
    int y = analogRead(yPin);
    if (x > 550 || y > 550) {
        digitalWrite(multiRedPin, HIGH);
    } else {
        digitalWrite(multiRedPin, LOW);
    }
    if (x < 500 || y < 500) {
        digitalWrite(multiBluePin, HIGH);
    } else {
        digitalWrite(multiBluePin, LOW);
    }
    delay(30);
}
