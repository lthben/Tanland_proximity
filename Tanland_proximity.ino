/* Author: Benjamin Low
 * Date: July 2015
 * Description: Infrared proximity sensor for ball detection passing
 * through a tube.
 */

int INITIAL_VALUE = 400; //need to calibrate with tube diameter
const int SENSITIVITY = 50; //need to calibrate. Difference in reading between initial value or no ball detected and when ball detected
int ball_count;
boolean is_same_ball;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0);
//  Serial.println(value);
  if (value < INITIAL_VALUE - SENSITIVITY && is_same_ball == false) {
    ball_count++;
    is_same_ball = true;
    Serial.println(ball_count);
  } else if (value > INITIAL_VALUE - SENSITIVITY && is_same_ball == true) {
    is_same_ball = false;
  }
  delay(50);
}
