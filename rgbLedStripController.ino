const int LED_R = 11;
const int LED_G = 10;
const int LED_B = 9;
const int ON_BTN = 3;
boolean IS_RGB_ON = false;
boolean SERIAL_CONTROL_ENABLED = true;

void setRGB(int red, int green, int blue) {
	analogWrite(LED_R, red);
	analogWrite(LED_G, green);
	analogWrite(LED_B, blue);
	if (!red && !green && !blue) {
		IS_RGB_ON = false;
	} else {
		IS_RGB_ON = true;
	}
}

void blink(int k, int time_on=200, int time_off=300) {
	for (int i=1; i<=k; i++) {
		setRGB(255, 0, 0);
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
	pinMode(ON_BTN, INPUT_PULLUP);
	Serial.begin(9600);
}

void loop() {

	if (!digitalRead(ON_BTN)) {
		int counter = 0;
		while (!digitalRead(ON_BTN)) {
			counter++;
			if (counter == 20) {
				SERIAL_CONTROL_ENABLED = !SERIAL_CONTROL_ENABLED;
				SERIAL_CONTROL_ENABLED ? blink(1) : blink(2);
			}
			delay(50);
		}
		if (counter >= 20) {
			delay(200);
			return;
		}

		if (IS_RGB_ON) {
			setRGB(0, 0, 0);
			IS_RGB_ON = false;
		} else {
			setRGB(255, 70, 15);
			IS_RGB_ON = true;
		}
		delay(200);
	}

	if (Serial.available() > 0) {

		if (!SERIAL_CONTROL_ENABLED) return;

		char action = Serial.peek();

		if (action == 'd') {  // disable serial control
			SERIAL_CONTROL_ENABLED = false;
			blink(2);
			serialFlush();
			return;
		}

		int red = Serial.parseInt();
		int green = Serial.parseInt();
		int blue = Serial.parseInt();

		if (Serial.read() == '\n') {

			red = constrain(red, 0, 255);
			green = constrain(green, 0, 255);
			blue = constrain(blue, 0, 255);

			setRGB(red, green, blue);
		
			Serial.print(red, HEX);
			Serial.print(green, HEX);
			Serial.println(blue, HEX);
		}
	}
}
