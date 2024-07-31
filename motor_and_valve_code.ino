// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
const int relayPin1 = 5;
const int relayPin2 = 6;

void setup() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(relayPin1, OUTPUT);
    pinMode(relayPin2, OUTPUT);
    // Turn off motors and valves - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(relayPin1, HIGH);
    digitalWrite(relayPin2, HIGH);
}

void loop() {
    directionControl();
    //speedcontrol();
    delay(1000);
}

// This function lets you control spinning direction of motors and valve operation
void directionControl() {
    // Open valve 1
    digitalWrite(relayPin1, LOW);
    delay(100); // Brief delay to ensure valve 1 is open before starting motor

    // Set motor to maximum speed and direction to take water from valve 1
    analogWrite(enA, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(10000); // Keep motor running with valve 1 open for 5 seconds

    // Turn off motor and close valve 1
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0);
    digitalWrite(relayPin1, HIGH);
    delay(1000); // Wait for 1 second before switching valves

    // Open valve 2
    digitalWrite(relayPin2, LOW);
    delay(100); // Brief delay to ensure valve 2 is open

    // Set motor to maximum speed and direction to take water from valve 2
    analogWrite(enA, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(10000); // Keep motor running with valve 2 open for 10 seconds

    // Turn off motor and close valve 2
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0);
    digitalWrite(relayPin2, HIGH);

    // Add any additional delay if needed before the next cycle
    delay(1000);
}


// This function lets you control speed of the motors
void speedControl() {
	// Turn on motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	
	// Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++) {
		analogWrite(enA, i);
		
		delay(20);
	}
	
	// Decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i) {
		analogWrite(enA, i);
		
		delay(20);
	}
	
	// Now turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	
}
