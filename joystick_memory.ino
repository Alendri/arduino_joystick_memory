//DIGITAL OUTPUTS
int multiRedPin = 2;
int multiGreenPin = 3;
int multiBluePin = 4;
int bluePin = 5;
int yellowPin = 6;
int greenPin = 7;
int redPin = 8;
int whitePin = 9;
//PWM OUTPUTS
int buzz = 11;

//ANALOG INPUTS
int xPin = A0;
int yPin = A1;
//DIGITAL INPUTS
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

    delay(30);
}
