//DIGITAL OUTPUTS
int multiRedPin = 4;
int multiGreenPin = 3;
int multiBluePin = 2;
int bluePin = 8;
int yellowPin = 6;
int greenPin = 7;
int redPin = 5;
int whitePin = 9;
//PWM OUTPUTS
int buzzPin = 10;

//Joystick input values:
// N  0, 512
// NE 0, 0
// E  512, 0
// SE 1023, 255
// S  1023, 512
// SW 1023, 1023
// W  512, 1023
// NW 0, 1023

//ANALOG INPUTS
int xPin = A0;
int yPin = A1;
//DIGITAL INPUTS
int btnBlPin = 11;
int btnBkPin = 12;
int btnRePin = 13;

bool pause = false;

void setup() {
    pinMode(multiRedPin, OUTPUT);
    pinMode(multiGreenPin, OUTPUT);
    pinMode(multiBluePin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(whitePin, OUTPUT);
    pinMode(buzzPin, OUTPUT);

    pinMode(btnBkPin, INPUT);
    pinMode(btnBlPin, INPUT);
    pinMode(btnRePin, INPUT);
    Serial.begin(115200);
}

int lastReState = 0;
int lastBkState = 0;
int lastBlState = 0;

unsigned long lastReDbncTime = 0;
unsigned long lastBkDbncTime = 0;
unsigned long lastBlDbncTime = 0;
unsigned long debounceTime = 50;

int goal = 0;
byte inputVal = 0b10000000;

void loop() {
    unsigned long ms = millis();

    int reRead = digitalRead(btnRePin);
    int blRead = digitalRead(btnBlPin);
    int bkRead = digitalRead(btnBkPin);
    lastReDbncTime = reRead == lastReState ? lastReDbncTime : ms;
    lastBlDbncTime = blRead == lastBlState ? lastBlDbncTime : ms;
    lastBkDbncTime = bkRead == lastBkState ? lastBkDbncTime : ms;
    if (ms % 3000 == 0) {
        Serial.print("Sec: ");
        Serial.println(ms / 1000);
        Serial.print("Input: ");
        Serial.println(inputVal, BIN);
    }

    if (ms - lastReDbncTime > debounceTime && reRead != bitRead(inputVal, 0)) {
        bitWrite(inputVal, 0, !bitRead(inputVal, 0));
    }
    if (ms - lastBkDbncTime > debounceTime && bkRead != bitRead(inputVal, 1)) {
        bitWrite(inputVal, 1, !bitRead(inputVal, 1));
    }
    if (ms - lastBlDbncTime > debounceTime && blRead != bitRead(inputVal, 2)) {
        bitWrite(inputVal, 2, !bitRead(inputVal, 2));
    }

    lastReState = reRead;
    lastBlState = blRead;
    lastBkState = bkRead;

    digitalWrite(multiRedPin, bitRead(inputVal, 0));
    digitalWrite(multiGreenPin, bitRead(inputVal, 1));
    digitalWrite(multiBluePin, bitRead(inputVal, 2));

    delay(1);
}
