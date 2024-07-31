// Define the pin connected to the PIR sensor's output
const int pirSensorPin = 2;
// Define the pin connected to the TMP36 temperature sensor's analog output (A0)
const int tempSensorPin = A0;
// Define the pins connected to the LEDs
const int ledPin1 = 12;
const int ledPin2 = 13;
const int ledPin3 = 11;

// Variable to store the current state of motion detection
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

  // Attach interrupt to the PIR sensor pin
  attachInterrupt(digitalPinToInterrupt(pirSensorPin), handleMotion, CHANGE);
}

void loop() {
  // Read the temperature from the TMP36 sensor
  int tempReading = analogRead(tempSensorPin);
  float voltage = tempReading * 5.0 / 1024.0;
  float temperatureC = (voltage - 0.5) * 100.0;

  // Print the sensor states and temperature to the Serial Monitor
  Serial.print("Motion Detected: ");
  Serial.print(motionDetected);
  Serial.print(" | Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  // Control all LEDs based on motion detection or temperature threshold
  if (motionDetected || temperatureC > 30.0) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }

  // Small delay to avoid rapid updates
  delay(500);
}

// Interrupt service routine to handle motion detection
void handleMotion() {
  motionDetected = digitalRead(pirSensorPin) == HIGH;
}
