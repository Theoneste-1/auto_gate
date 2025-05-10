Arduino Ultrasonic Barrier Control System
Overview
This Arduino project implements an automated barrier control system using an ultrasonic sensor to detect objects within a specific range. The system controls LEDs, a servo motor (acting as a barrier), and a buzzer to provide visual and auditory feedback based on object detection.
Hardware Requirements

Arduino board (e.g., Uno, Nano)
HC-SR04 Ultrasonic Sensor
Servo Motor (e.g., SG90)
Red LED
Blue LED
Active Buzzer
Resistors (for LEDs, typically 220-330Ω)
Jumper wires
Breadboard or PCB for connections

Pin Connections



Component
Arduino Pin



Ultrasonic Trigger Pin
2


Ultrasonic Echo Pin
3


Red LED
4


Blue LED
5


Servo Motor Control
6


Red LED Ground
7


Blue LED Ground
8


Buzzer
12


How It Works

Initialization (setup)

Initializes serial communication at 9600 baud for debugging.
Configures pins for the ultrasonic sensor, LEDs, buzzer, and servo.
Sets ground pins for LEDs to LOW.
Attaches the servo to its pin and sets it to the closed position (0°).
Turns on the red LED to indicate the system is idle and ready.


Main Loop (loop)

Ultrasonic Sensing:
Sends a 10µs pulse via the trigger pin to the ultrasonic sensor.
Measures the echo pulse duration to calculate the distance to an object (in cm) using the formula: distance = duration * 0.034 / 2.


Object Detection:
If an object is detected within 0-15 cm:
Red LED turns off, blue LED turns on.
Buzzer beeps 10 times (100ms on/off cycles).
Servo rotates to 90° (opens barrier), waits 5 seconds, then returns to 0° (closes barrier).
System resets to idle state: blue LED off, red LED on, buzzer off.


If no object is detected or the object is beyond 15 cm:
Red LED remains on, blue LED and buzzer remain off.
Servo stays at 0° (closed).




Logs distance and system status to the Serial Monitor for debugging.
Waits 500ms before the next measurement cycle.



Code Structure

Libraries: Uses <Servo.h> for servo motor control.
Constants: Descriptive pin names (e.g., ULTRASONIC_TRIG_PIN, RED_LED_PIN) for clarity.
Variables:
echoDuration: Stores the ultrasonic echo pulse duration.
objectDistance: Stores the calculated distance in cm.


Functions:
setup(): Initializes hardware and system state.
loop(): Continuously monitors for objects and controls outputs.



Usage

Connect the hardware as per the pin connections table.
Upload the code to your Arduino using the Arduino IDE.
Open the Serial Monitor (9600 baud) to view distance measurements and system status.
Place objects within 15 cm of the ultrasonic sensor to trigger the barrier opening, LED changes, and buzzer.

Notes

Ensure the ultrasonic sensor is unobstructed for accurate readings.
Adjust the detection range (15 cm) by modifying the condition in the loop() function if needed.
The servo's 5-second open duration can be adjusted via the delay(5000) value.
Use appropriate resistors with LEDs to prevent damage.

Troubleshooting

No Serial Output: Verify the baud rate (9600) and USB connection.
Servo Not Moving: Check servo wiring and power supply (servos may require an external power source for stability).
Inaccurate Distance: Ensure no objects interfere with the ultrasonic sensor's line of sight.
Buzzer/LEDs Not Working: Confirm correct pin assignments and check for loose connections.

