/* Author: Benjamin Low
 * Last update: 17 Aug 2015
 * Description: Infrared proximity sensor for ball detection passing
 * through a tube. Constantly serial writes the sensor value from 0-255.
 * A lower value means ball is detected.
 * A 5V arcade button is also connected. Button lights
 * are controlled by an external program through the serial port.
 * Serial writes to port to external program whenever button status changes.
 */

//For testing purposes only
int INITIAL_VALUE = 400; //need to calibrate with tube diameter
const int SENSITIVITY = 50; //need to calibrate. Difference in reading between initial value or no ball detected and when ball detected
int ball_count;
boolean is_same_ball;

//For actual program
int sensor_value;
int switch_status, prev_switch_status;
boolean is_led_on;

void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  switch_status = prev_switch_status = HIGH;
}

void loop() {

  serialEvent();

  read_switch();

  sensor_value = analogRead(A0);
  sensor_value = map(sensor_value, 0, 500, 0, 255);
  sensor_value = constrain(sensor_value, 2, 255);
  Serial.write(sensor_value);
  //      Serial.println(sensor_value);

  //run_test(); //for testing purposes with Processing GUI

  run_led(); //controlled by external command

  delay(20);
}

void run_led() {
  if (is_led_on == true) {
    analogWrite(A1, 255);
  } else if (is_led_on == false) {
    analogWrite(A1, 0);
  }
}

void serialEvent() {
  char inChar;

  while (Serial.available()) {
    inChar = (char)Serial.read();
  }
  if (inChar == '1') {
    is_led_on = true;
  } else if (inChar == '0') {
    is_led_on = false;
  }

}

void read_switch() {
  switch_status = digitalRead(7);

  if (switch_status != prev_switch_status) {

    if (switch_status == HIGH) {
        Serial.write(0);
//      Serial.println("off");
      delay(100); //to allow the Flash program to sample fast enough
    } else {
        Serial.write(1);
//      Serial.println("on");
      delay(100); //to allow the Flash program to sample fast enough
    }
  }

  prev_switch_status = switch_status;
}


void run_test() {
  if (sensor_value < INITIAL_VALUE - SENSITIVITY && is_same_ball == false) {
    is_same_ball = true;
    ball_count++;
    Serial.write(9); //assuming "9" means a ball detected
  } else if (sensor_value > INITIAL_VALUE - SENSITIVITY && is_same_ball == true) {
    is_same_ball = false;
  }
}

