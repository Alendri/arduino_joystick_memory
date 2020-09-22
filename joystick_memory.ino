//DIGITAL OUTPUTS
const int multiRedPin = 4;
const int multiGreenPin = 3;
const int multiBluePin = 2;
const int bluePin = 8;
const int yellowPin = 6;
const int greenPin = 7;
const int redPin = 5;
const int whitePin = 9;
//PWM OUTPUTS
const int buzzPin = 10;

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
const int xPin = A0;
const int yPin = A1;
//DIGITAL INPUTS
const int btnBlPin = 11;
const int btnBkPin = 12;
const int btnRePin = 13;

int lastReState = 0;
int lastBkState = 0;
int lastBlState = 0;

unsigned long lastReDbncTime = 0;
unsigned long lastBkDbncTime = 0;
unsigned long lastBlDbncTime = 0;
const int debounceTime = 30;

//The time of the previously entered correct input.
unsigned long lastWin = 0;
//The time stamp of the last failed input.
unsigned long lastFail = 0;
//The time the player has to respond.
int timeout = 3000;

int playmode = 0;

int goal = 0;
byte inputVal = 0;
bool playing = false;
//Waiting for player to release buttons.
bool waiting = false;

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
        lastFail = 0;
        goal = random(1, 8);
        Serial.print("Goal: ");
        Serial.println(goal);
    }
    if (!playing && analogRead(yPin) > 1000) {
        goal = 0b111;
        playmode = 1;
    }

    if (playing && inputVal == goal && !waiting) {
        //Progress in game.
        lastWin = ms;
        waiting = true;
        lastFail = 0;
        int new_goal = 0;
        new_goal = random(1, 8);
        while (new_goal == goal) {
            new_goal = random(1, 8);
        }
        goal = new_goal;
    } else if (playing && playmode == 1 && inputVal > 0 && inputVal != goal && !waiting) {
        //Fail timeout start.
        lastFail = ms;
    } else if (waiting && inputVal == 0) {
        waiting = false;
    }

    if (playing && ms - lastWin > timeout) {
        //Fail 1.
        Serial.println("fail 1");
        playing = false;
        goal = 0;
        tone(buzzPin, 300, 600);
    }
    if (playing && playmode == 1 && lastFail > 0 && ms - lastFail > 100) {
        //Fail 2.
        Serial.println("fail 2 ");
        lastFail = 0;
        playing = false;
        goal = 0;
        tone(buzzPin, 300, 600);
    }

    digitalWrite(redPin, goal == 1 || goal == 5);
    digitalWrite(greenPin, goal == 2 || goal == 6);
    digitalWrite(yellowPin, goal == 3);
    digitalWrite(bluePin, goal == 4 || goal == 6 || goal == 5);
    digitalWrite(whitePin, goal == 7);

    delay(1);
}
