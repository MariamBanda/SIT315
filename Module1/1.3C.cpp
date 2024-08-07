// Define the pin connected to the PIR sensor's output
const int pirSensorPin = 2;
// Define the pin connected to the tilt sensor's output
const int tiltSensorPin = 3;
// Define the pins connected to the LEDs
const int ledPin1 = 12;
const int ledPin2 = 13;
const int ledPin3 = 11;

// Variables to store the current state of motion detection and tilt detection
volatile bool motionDetected = false;
volatile bool tiltDetected = false;

void setup() {
  // Set up the PIR sensor pin and tilt sensor pin as inputs
  pinMode(pirSensorPin, INPUT);
  pinMode(tiltSensorPin, INPUT);
  // Set up the LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  // Start Serial communication for monitoring
  Serial.begin(9600);

  // Attach interrupts to the PIR sensor pin and tilt sensor pin
  attachInterrupt(digitalPinToInterrupt(pirSensorPin), handleMotion, CHANGE);
  attachInterrupt(digitalPinToInterrupt(tiltSensorPin), handleTilt, CHANGE);
}

void loop() {
  // Print the sensor states to the Serial Monitor
  Serial.print("Motion Detected: ");
  Serial.print(motionDetected);
  Serial.print(" | Tilt Detected: ");
  Serial.print(tiltDetected);
  Serial.println();

  // Control all LEDs based on motion detection or tilt detection
  if (motionDetected || tiltDetected) { 
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }

  // Small delay to avoid rapid updates
  delay(100);
}

// Interrupt service routine to handle motion detection
void handleMotion() {
  motionDetected = digitalRead(pirSensorPin) == HIGH;
}

// Interrupt service routine to handle tilt detection
void handleTilt() {
  // Adjusted to turn LEDs on when tilt is detected
  tiltDetected = digitalRead(tiltSensorPin) == LOW; // Assuming LOW means tilt detected
}
