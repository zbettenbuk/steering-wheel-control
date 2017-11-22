//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 4; //green
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 1; //yellow
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 0;  //blue

const int analogPin = 1;  // confusing pin numbering on Adafruit Trinket
const float r1 = 640;
const int vin = 5;
int lastButton = -1;

// These OHM values are from a Suzuki steering wheel. Feel free to customize.
// Please note that the order of the array is also the order of the digital buttons
// on the circuit
// You can also add 2 more buttons, as we use a 8-out shift register, but you also have to extend the circuit respectively.
const int BUTTON_VALUES[] = {
  57, //mute
  424, //mode
  133, //vol up
  243, //vol down
  760, //seek up
  1570 //seek down
};

int getButton(int resistance) {
  for (int b = 0; b < 6; b++) {
    int diff = resistance - BUTTON_VALUES[b];
    if (abs(diff) < BUTTON_VALUES[b] * 0.25) {
      return b + 1;
    }
  }
  return 0;
}

void turnOffAll() {
  for (int i = 0; i < 8; i++) {
    registerWrite(i, LOW);
  }
}

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  turnOffAll();
}

// code partially based on http://www.circuitbasics.com/arduino-ohm-meter/

void loop() {
  int raw = analogRead(analogPin);
  if(raw) {
    float buffer= raw * vin;
    float vout = (buffer) / 1024.0;
    buffer = (vin/vout) - 1;
    int r2 = r1 * buffer;
    int button = getButton(r2);
    if (button != lastButton) {
      turnOffAll();
      registerWrite(button, HIGH);
      lastButton = button;
    }
  }
  delay(10);
}

// This method sends bits to the shift register
// code from https://www.arduino.cc/en/Tutorial/ShftOut12

void registerWrite(int whichPin, int whichState) {
// the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

}
