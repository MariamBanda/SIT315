// Define the pin connected to the PIR sensor's output
const int pirSensorPin = 2;
// Define the pins connected to the LEDs
const int ledPin1 = 12;
const int ledPin2 = 13;
const int ledPin3 = 11;

// Variable to store the current state of the LEDs
volatile bool motionDetected = false;

void setup() {
  // Set up the PIR sensor pin as an input
  pinMode(pirSensorPin, INPUT);
  // Set up the LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  // Start Serial communication for monitoring
  Serial.begin(9600);

  // Attach an interrupt to the PIR sensor pin, calling the handleMotion function
  attachInterrupt(digitalPinToInterrupt(pirSensorPin), handleMotion, CHANGE);
}

void loop() {
  // The main loop remains empty because we use an interrupt to handle the sensor

  // Print the sensor state to the Serial Monitor
  Serial.print("Motion Detected: ");
  Serial.println(motionDetected);

  // Control LEDs based on motion detection state
  if (motionDetected) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }

  // Small delay to avoid rapid on/off switching
  delay(500);
}

// Interrupt service routine to handle motion detection
void handleMotion() {
  motionDetected = digitalRead(pirSensorPin) == HIGH;
}
