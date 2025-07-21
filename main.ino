// Pin definitions
const int buttonPin = 2;
const int speakerPin = 8;

// Quindar tone settings
const int startToneFreq = 2525; //2525
const int endToneFreq = 2475; //2475
const int toneDuration = 250; // milliseconds

// Debounce settings
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // milliseconds

// Button state tracking
bool lastButtonState = HIGH;    // previous stable state
bool currentButtonState;        // current read state
bool buttonState = HIGH;        // debounced state

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // enable internal pull-up resistor
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // If the button state changed, reset the debounce timer
  if (reading != currentButtonState) {
    lastDebounceTime = millis();
  }

  currentButtonState = reading;

  // If the button state has remained stable for the debounce delay, accept it
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the state has changed (debounced), act on it
    if (currentButtonState != buttonState) {
      buttonState = currentButtonState;

      // Button just pressed
      if (buttonState == LOW) {
        tone(speakerPin, startToneFreq, toneDuration);
        delay(toneDuration);
      }

      // Button just released
      if (buttonState == HIGH) {
        tone(speakerPin, endToneFreq, toneDuration);
        delay(toneDuration);
      }
    }
  }
}
