//DIGITAL OUTPUTS
int multiRedPin = 4;
int multiGreenPin = 3;
int multiBluePin = 2;
int bluePin = 5;
int yellowPin = 6;
int greenPin = 7;
int redPin = 8;
int whitePin = 9;
//PWM OUTPUTS
int buzz = 10;

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

    pinMode(btnBkPin, INPUT);
    pinMode(btnBlPin, INPUT);
    pinMode(btnRePin, INPUT);
    Serial.begin(115200);
}

int lastReState = 0;
int lastBkState = 0;
int lastBlState = 0;
int reState = 0;
int bkState = 0;
int blState = 0;

unsigned long lastReDbncTime = 0;
unsigned long lastBkDbncTime = 0;
unsigned long lastBlDbncTime = 0;
unsigned long debounceTime = 50;

void loop() {
    unsigned long ms = millis();

    int reRead = digitalRead(btnRePin);
    int blRead = digitalRead(btnBlPin);
    int bkRead = digitalRead(btnBkPin);
    if (millis() % 1000 == 0) {
        Serial.print("Sec: ");
        Serial.print(millis() / 1000);
        Serial.print("  BtnRe: ");
        Serial.print(digitalRead(btnRePin));
        Serial.print("  BtnBk: ");
        Serial.print(digitalRead(btnBkPin));
        Serial.print("  BtnBl: ");
        Serial.println(digitalRead(btnBlPin));
        // Serial.print("\n");
        // Serial.print(analogRead(xPin));
        // Serial.print(", ");
        // Serial.println(analogRead(yPin));
    }

    lastReDbncTime = reRead == lastReState ? lastReDbncTime : ms;
    lastBlDbncTime = blRead == lastBlState ? lastBlDbncTime : ms;
    lastBkDbncTime = bkRead == lastBkState ? lastBkDbncTime : ms;

    if (ms - lastReDbncTime > debounceTime && reRead != reState) {
        reState = reRead;
        if (reState == 1) {
            //We have a btn press.
            Serial.println("reBtnPress");
        }
    }
    if (ms - lastBlDbncTime > debounceTime && blRead != blState) {
        blState = blRead;
        if (blState == 1) {
            //We have a btn press.
            Serial.println("blBtnPress");
        }
    }
    if (ms - lastBkDbncTime > debounceTime && bkRead != bkState) {
        bkState = bkRead;
        if (bkState == 1) {
            //We have a btn press.
            Serial.println("bkBtnPress");
        }
    }
    lastReState = reRead;
    lastBlState = blRead;
    lastBkState = bkRead;

    delay(1);
}
