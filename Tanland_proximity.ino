/* Author: Benjamin Low
 * Last update: 17 Aug 2015
 * Description: Infrared proximity sensor for ball detection passing
 * through a tube. A 5V arcade button is also connected. Button lights
 * up when pressed. For the button, serial writes "0" when not pressed, 
 * "1" when pressed. For the ball detection, writes "9" when ball 
 * detected.
 */

int INITIAL_VALUE = 400; //need to calibrate with tube diameter
const int SENSITIVITY = 50; //need to calibrate. Difference in reading between initial value or no ball detected and when ball detected
int ball_count;
boolean is_same_ball;

void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {

  int switchVal = digitalRead(7);

 if (switchVal == 1) {
        analogWrite(A1, 0);
        Serial.write(0);
 } else {
        analogWrite(A1, 255);
        Serial.write(1);
 }
        
  int value = analogRead(A0);
   Serial.println(value);
  if (value < INITIAL_VALUE - SENSITIVITY && is_same_ball == false) {
    is_same_ball = true;
   Serial.write(9);
  } else if (value > INITIAL_VALUE - SENSITIVITY && is_same_ball == true) {
    is_same_ball = false;
  }
  delay(10);

}
