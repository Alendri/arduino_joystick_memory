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

int lastReState = 0;
int lastBkState = 0;
int lastBlState = 0;

unsigned long lastReDbncTime = 0;
unsigned long lastBkDbncTime = 0;
unsigned long lastBlDbncTime = 0;
int debounceTime = 30;

unsigned long lastWin = 0;
//The time the player has to respond.
int timeout = 3000;

int goal = 0;
byte inputVal = 0;
bool playing = false;

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

    randomSeed(analogRead(5));
}

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
        Serial.print(ms / 1000);
        Serial.print("  Input: ");
        Serial.print(inputVal, BIN);
        Serial.print(" ");
        Serial.println(inputVal);
        // Serial.print(analogRead(xPin));
        // Serial.print(" ");
        // Serial.println(analogRead(yPin));
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

    if (!playing && analogRead(yPin) < 100) {
        //Start a new game.
        playing = true;
        lastWin = ms;
        goal = random(1, 8);
        Serial.print("Goal: ");
        Serial.println(goal);
    }
    if (playing && analogRead(yPin) > 1000) {
        goal = 0;
        playing = false;
    }

    if (playing && inputVal == goal) {
        lastWin = ms;
        goal = random(1, 8);
    } else if (playing && ms - lastWin > timeout) {
        playing = false;
        goal = 0;
    }

    digitalWrite(redPin, goal == 1 || goal == 5);
    digitalWrite(greenPin, goal == 2);
    digitalWrite(yellowPin, goal == 3);
    digitalWrite(bluePin, goal == 4 || goal == 6 || goal == 5);
    digitalWrite(whitePin, goal == 7 || goal == 6);

    delay(1);
}
