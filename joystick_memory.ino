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

//SET bit
//var |= 1UL << bit;
//CLR bit
//var &= ~(1UL << bit);

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
int inputVal = 0;

void loop() {
    unsigned long ms = millis();

    int reRead = digitalRead(btnRePin);
    int blRead = digitalRead(btnBlPin);
    int bkRead = digitalRead(btnBkPin);
    if (ms % 3000 == 0) {
        Serial.print("Sec: ");
        Serial.println(ms / 1000);
        Serial.print("Input: ");
        Serial.println(inputVal);
    }

    lastReDbncTime = reRead == lastReState ? lastReDbncTime : ms;
    lastBlDbncTime = blRead == lastBlState ? lastBlDbncTime : ms;
    lastBkDbncTime = bkRead == lastBkState ? lastBkDbncTime : ms;

    if (ms - lastReDbncTime > debounceTime && reRead != (inputVal >> 0) & 1U) {
        // inputVal ^= 1UL << 0;
        if ((inputVal >> 0) & 1U) {
            Serial.println("reBtnPress");
            inputVal |= 1UL << 0;
        } else {
            inputVal &= ~(1UL << 0);
        }
    }
    if (ms - lastBkDbncTime > debounceTime && bkRead != (inputVal >> 1) & 1U) {
        // inputVal ^= 1UL << 1;
        if ((inputVal >> 1) & 1U) {
            Serial.println("bkBtnPress");
            inputVal |= 1UL << 1;
        } else {
            inputVal &= ~(1UL << 1);
        }
    }
    if (ms - lastBlDbncTime > debounceTime && blRead != (inputVal >> 2) & 1U) {
        // inputVal ^= 1UL << 2;
        if ((inputVal >> 2) & 1U) {
            Serial.println("blBtnPress");
            inputVal |= 1UL << 2;
        } else {
            inputVal &= ~(1UL << 2);
        }
    }

    lastReState = reRead;
    lastBlState = blRead;
    lastBkState = bkRead;

    digitalWrite(multiRedPin, (inputVal >> 0) & 1U);
    digitalWrite(multiGreenPin, (inputVal >> 1) & 1U);
    digitalWrite(multiBluePin, (inputVal >> 2) & 1U);

    delay(1);
}
