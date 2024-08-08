// Define the pins
const int pirSensorPin = 2;    // PIR sensor output
const int tiltSensorPin = 3;   // Tilt sensor output
const int tempPin = A0;        // Temperature sensor input
const int ledPin1 = 12;        // LED 1
const int ledPin2 = 13;        // LED 2
const int ledPin3 = 11;        // LED 3

// Variables to store sensor states
volatile bool motionDetected = false;
volatile bool tiltDetected = false;
volatile int currentTemp = 0;  // Updated to be volatile

void setup() {
  // Set up PIR sensor and tilt sensor pins as inputs
  pinMode(pirSensorPin, INPUT);
  pinMode(tiltSensorPin, INPUT);
  
  // Set up LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // Set up temperature sensor pin as input
  pinMode(tempPin, INPUT);

  // Start Serial communication
  Serial.begin(9600);

  // Attach interrupts for PIR and tilt sensors using PCINT
  PCICR |= (1 << PCIE2); // Enable PCINT for group 2 (PCINT16-23)
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19); // Enable PCINT for pirSensorPin (pin 2) and tiltSensorPin (pin 3)

  // Timer interrupt setup for 2-second interval
  cli(); // Disable interrupts
  TCCR1A = 0; // Set entire TCCR1A register to 0
  TCCR1B = 0; // Set entire TCCR1B register to 0
  TCNT1  = 0; // Initialize counter value to 0
  // Set compare match register for 2-second increments
  OCR1A = 31249; // For 2 Hz frequency with 1024 prescaler
  // Turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // Enable interrupts
}

void loop() {
  // Print the sensor states
  Serial.print("Motion Detected: ");
  Serial.print(motionDetected);
  Serial.print(" | Tilt Detected: ");
  Serial.print(tiltDetected);
  Serial.print(" | Temperature: ");
  Serial.println(currentTemp);

  // Control LEDs based on motion and tilt detection
  if (motionDetected || tiltDetected) { 
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }

  // Control LED1 based on temperature sensor reading
  int tempSensorValue = analogRead(tempPin);
  currentTemp = tempSensorValue; // Update currentTemp with the latest value

  if (tempSensorValue > 176) {
    digitalWrite(ledPin1, HIGH); // LED1 for high temperature
  } else {
    digitalWrite(ledPin1, LOW);
  }

  // Small delay to avoid rapid updates
  delay(100);
}

// Timer interrupt service routine (ISR)
ISR(TIMER1_COMPA_vect) {
  digitalWrite(ledPin1, HIGH); // Turn on LED1
  delay(1000); // Keep the LED on for 1 second
  digitalWrite(ledPin1, LOW); // Turn off LED1
}

// Pin change interrupt service routine for PCINT2_vect (PCINT16-23)
ISR(PCINT2_vect) {
  // Handle motion detection
  motionDetected = digitalRead(pirSensorPin) == HIGH;
  
  // Handle tilt detection
  tiltDetected = digitalRead(tiltSensorPin) == LOW; // Assuming LOW means tilt detected
}
