// Define the pin connected to the PIR sensor's output
const int pirSensorPin = 2;
// Define the pins connected to the LEDs
const int ledPin1 = 12;
const int ledPin2 = 13;
const int ledPin3 = 11;

void setup() {
  // Set up the PIR sensor pin as an input
  pinMode(pirSensorPin, INPUT);
  // Set up the LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  // Start Serial communication for monitoring
  Serial.begin(9600);
}

void loop() {
  // Read the value from the PIR sensor
  int sensorValue = digitalRead(pirSensorPin);

  // Print the sensor value to the Serial Monitor
  Serial.print("PIR Sensor Value: ");
  Serial.println(sensorValue);

  // If motion is detected, turn on all LEDs
  if (sensorValue == HIGH) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else {
    // If no motion, turn off all LEDs
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }

  // Small delay to avoid rapid on/off switching
  delay(500);
}
