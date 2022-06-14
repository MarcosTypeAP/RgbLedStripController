// Config section
///////////////////////////////////////////////////////////
const int LED_R = 11;          // Red LED Pin
const int LED_G = 10;          // Green LED Pin
const int LED_B = 9;           // Blue LED Pin
const int BUTTON = 3;          // Button Pin
const int DEFAULT_R = 255; 	   // Default Red value
const int DEFAULT_G = 70;      // Default Green value
const int DEFAULT_B = 15;      // Default Blue value
const int PWM_RESOLUTION = 8;  // PWM resolution in Bits
///////////////////////////////////////////////////////////

const int MAX_PWM_VALUE = pow(2, PWM_RESOLUTION) - 1;
boolean is_strip_on = false;
boolean serial_control_enabled = true;

void setRGB(int red, int green, int blue) {
	analogWrite(LED_R, red);
	analogWrite(LED_G, green);
	analogWrite(LED_B, blue);
	if (!red && !green && !blue) {
		is_strip_on = false;
	} else {
		is_strip_on = true;
	}
}

void blink(int k, int time_on=200, int time_off=300) {
	for (int i=1; i<=k; i++) {
		setRGB(MAX_PWM_VALUE / 4, 0, 0);
		delay(time_on);
		setRGB(0, 0, 0);
		delay(time_off);
	}
}

void serialFlush(){
	while(Serial.available() > 0) {
		Serial.read();
	}
}

void setup() {
	pinMode(LED_R, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(LED_B, OUTPUT);
	pinMode(BUTTON, INPUT_PULLUP);
	Serial.begin(9600);
}

void loop() {

	if (!digitalRead(BUTTON)) {
		int counter = 0;
		while (!digitalRead(BUTTON)) {
			counter++;
			if (counter == 20) {
				serial_control_enabled = !serial_control_enabled;
				serial_control_enabled ? blink(1) : blink(2);
			}
			delay(50);
		}
		if (counter >= 20) {
			delay(200);
			return;
		}

		is_strip_on ? setRGB(0, 0, 0) : setRGB(DEFAULT_R, DEFAULT_G, DEFAULT_B);
		delay(200);
	}

	if (Serial.available() > 0) {

		if (!serial_control_enabled) return;

		char action = Serial.peek();

		if (action == 'd') {  // disable serial control
			serial_control_enabled = false;
			blink(2);
			serialFlush();
			return;
		}

		int red = Serial.parseInt();
		int green = Serial.parseInt();
		int blue = Serial.parseInt();

		if (Serial.read() == '\n') {

			red = constrain(red, 0, MAX_PWM_VALUE);
			green = constrain(green, 0, MAX_PWM_VALUE);
			blue = constrain(blue, 0, MAX_PWM_VALUE);

			setRGB(red, green, blue);
		
			Serial.print(red, HEX);
			Serial.print(green, HEX);
			Serial.println(blue, HEX);
		}
	}
}
