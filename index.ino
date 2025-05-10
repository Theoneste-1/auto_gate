#include <Servo.h>

// Pin assignments for clarity
const int RED_LED_GROUND_PIN = 7;    // Ground pin for red LED
const int BLUE_LED_GROUND_PIN = 8;   // Ground pin for blue LED
const int ULTRASONIC_TRIG_PIN = 2;   // Trigger pin for ultrasonic sensor
const int ULTRASONIC_ECHO_PIN = 3;   // Echo pin for ultrasonic sensor
const int RED_LED_PIN = 4;           // Red LED pin
const int BLUE_LED_PIN = 5;          // Blue LED pin
const int SERVO_CONTROL_PIN = 6;     // Servo motor control pin
const int BUZZER_PIN = 12;           // Buzzer pin

// Servo object for barrier control
Servo barrierServo;

// Variables for ultrasonic sensor readings
long echoDuration;                   // Duration of echo pulse
int objectDistance;                  // Calculated distance to object

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Configure pin modes
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);    // Set trigger pin as output
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);     // Set echo pin as input
  pinMode(RED_LED_PIN, OUTPUT);            // Set red LED pin as output
  pinMode(BLUE_LED_PIN, OUTPUT);           // Set blue LED pin as output
  pinMode(BUZZER_PIN, OUTPUT);             // Set buzzer pin as output
  pinMode(RED_LED_GROUND_PIN, OUTPUT);     // Set red LED ground pin as output
  pinMode(BLUE_LED_GROUND_PIN, OUTPUT);    // Set blue LED ground pin as output
  
  // Attach servo to its control pin
  barrierServo.attach(SERVO_CONTROL_PIN);
  barrierServo.write(0);                   // Initialize barrier to closed position
  
  // Set ground pins to LOW
  digitalWrite(RED_LED_GROUND_PIN, LOW);
  digitalWrite(BLUE_LED_GROUND_PIN, LOW);
  
  // Set initial system state
  digitalWrite(RED_LED_PIN, HIGH);         // Red LED on (idle state)
  digitalWrite(BLUE_LED_PIN, LOW);         // Blue LED off
  digitalWrite(BUZZER_PIN, LOW);           // Buzzer off
  Serial.println("System initialized. Red LED ON. Waiting for object detection...");
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  
  // Measure echo duration and calculate distance
  echoDuration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
  objectDistance = echoDuration * 0.034 / 2;  // Convert to centimeters
  
  // Log distance for debugging
  Serial.print("Distance: ");
  Serial.print(objectDistance);
  Serial.println(" cm");
  
  // Check if object is within detection range (0-15 cm)
  if (objectDistance > 0 && objectDistance <= 15) {
    Serial.println("Object detected within range!");
    
    // Update LED states
    digitalWrite(RED_LED_PIN, LOW);        // Turn off red LED
    digitalWrite(BLUE_LED_PIN, HIGH);      // Turn on blue LED
    
    // Activate buzzer with 10 beeps
    for (int i = 0; i < 10; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
    }
    
    // Open and close barrier
    barrierServo.write(90);               // Open barrier
    delay(5000);                          // Wait 5 seconds
    barrierServo.write(0);                // Close barrier
    
    // Reset to idle state
    digitalWrite(BLUE_LED_PIN, LOW);       // Turn off blue LED
    digitalWrite(RED_LED_PIN, HIGH);       // Turn on red LED
    digitalWrite(BUZZER_PIN, LOW);         // Turn off buzzer
    Serial.println("Resetting to idle: Red LED ON, Blue LED OFF, Buzzer OFF");
  } else {
    // No object detected or out of range
    digitalWrite(RED_LED_PIN, HIGH);       // Ensure red LED is on
    digitalWrite(BLUE_LED_PIN, LOW);       // Ensure blue LED is off
    digitalWrite(BUZZER_PIN, LOW);         // Ensure buzzer is off
    barrierServo.write(0);                 // Ensure barrier is closed
    Serial.println("No object detected - Red LED ON, Buzzer OFF");
  }
  
  // Short delay before next measurement
  delay(500);
}