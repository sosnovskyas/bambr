
// MOTOR A
#define A_ENABLE 5
#define A_MOTOR_1 6
#define A_MOTOR_2 7

// MOTOR B
#define B_ENABLE 8
#define B_MOTOR_1 9
#define B_MOTOR_2 10

// JOYSTICK
#define JOYSTICK_X A0
#define JOYSTICK_Y A1

void setup() {
  Serial.begin (9600);

  pinMode (A_ENABLE, OUTPUT);
  pinMode (A_MOTOR_1, OUTPUT);
  pinMode (A_MOTOR_2, OUTPUT);

  pinMode (B_ENABLE, OUTPUT);
  pinMode (B_MOTOR_1, OUTPUT);
  pinMode (B_MOTOR_2, OUTPUT);

}

void loop() {
  motorsControl(
    readAxis(JOYSTICK_X),
    readAxis(JOYSTICK_Y)
  );
}

int readAxis(int thisAxis) {
  int range = 12;  // output range of X or Y movement
  int threshold = range / 4;    // resting threshold
  int center = range / 2;       // resting position value

  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}

void motorsControl(int x, int y) {
  Serial.print(x);
  Serial.print(" - ");
  Serial.print(y);
  Serial.print(" - ");

  if ((x == 0) & (y == 0)) { // STOP
    Serial.println(" STOP");
    motor("A", "stop");
    motor("B", "stop");

  } else if ((x == 0)  & (y > 1)) { // FORWARD
    Serial.println ("FORWARD");

    motor("A", "forward");
    motor("B", "forward");

  }  else if ((x == 0)  & (y < -1)) { // BACK
    Serial.println ("BACK");

    motor("A", "back");
    motor("B", "back");

  } else if ((x > 1)  & (y == 0)) { // LEFT
    Serial.println ("LEFT");
    motor("A", "forward");
    motor("B", "back");

  }   else if ((x < -1)  & (y == 0)) { // RIGHT
    Serial.println ("LEFT");
    motor("A", "back");
    motor("B", "forward");

  } else {
    Serial.println ("else");
  }
}



void motor(char motor[], char direction[]) {
  int ENABLE;
  int MOTOR_1;
  int MOTOR_2;

  if (motor == "A") {
    ENABLE = A_ENABLE;
    MOTOR_1 = A_MOTOR_1;
    MOTOR_2 = A_MOTOR_2;
  } else if (motor == "B") {
    ENABLE = B_ENABLE;
    MOTOR_1 = B_MOTOR_1;
    MOTOR_2 = B_MOTOR_2;
  }

  if (direction == "forward") {
    digitalWrite (ENABLE, HIGH);
    digitalWrite (MOTOR_1, LOW);
    digitalWrite (MOTOR_2, HIGH);

  } else if (direction == "back") {
    digitalWrite (ENABLE, HIGH);
    digitalWrite (MOTOR_1, HIGH);
    digitalWrite (MOTOR_2, LOW);
  } else {
    digitalWrite (ENABLE, LOW);
  }
}
