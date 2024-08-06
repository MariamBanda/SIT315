// Define the pin connected to the PIR sensor's output
const int pirSensorPin = 2;
// Define the pin connected to the sound sensor's digital output (D0)
const int soundSensorPin = 3;
// Define the pin connected to the TMP36 temperature sensor's analog output (A0)
const int tempSensorPin = A0;
// Define the pins connected to the LEDs
const int ledPin1 = 12;
const int ledPin2 = 13;
const int ledPin3 = 11;

// Variables to store the current state of motion and sound detection
volatile bool motionDetected = false;
volatile bool soundDetected = false;

void setup() {
  // Set up the PIR sensor pin and sound sensor pin as inputs
  pinMode(pirSensorPin, INPUT);
  pinMode(soundSensorPin, INPUT);
  // Set up the LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  // Start Serial communication for monitoring
  Serial.begin(9600);

  // Attach interrupts to the PIR and sound sensor pins
  attachInterrupt(digitalPinToInterrupt(pirSensorPin), handleMotion, CHANGE);
  attachInterrupt(digitalPinToInterrupt(soundSensorPin), handleSound, CHANGE);
}

void loop() {
  // Read the temperature from the TMP36 sensor
  int tempReading = analogRead(tempSensorPin);
  float voltage = tempReading * 5.0 / 1024.0;
  float temperatureC = (voltage - 0.5) * 100.0;

  // Print the sensor states and temperature to the Serial Monitor
  Serial.print("Motion Detected: ");
  Serial.print(motionDetected);
  Serial.print(" | Sound Detected: ");
  Serial.print(soundDetected);
  Serial.print(" | Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  // Control all LEDs based on motion detection, sound detection, or temperature threshold
  if (motionDetected || soundDetected || temperatureC > 30.0) {
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

// Interrupt service routine to handle sound detection
void handleSound() {
  soundDetected = digitalRead(soundSensorPin) == HIGH;
}
