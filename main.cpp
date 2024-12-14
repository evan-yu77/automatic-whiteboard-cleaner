#include <DCMotor.h>

int pushButton = 2;
int direction = 1;
int alternus = 0;
int pos = 0;
int movDelay;
const int MAX_POS = 250;
bool start = false;
bool hold = false;

DCMotor motor(pushButton);


// the setup routine runs once when you press reset:
void setup() {
  motor.attach(9);
  motor.write(0);
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  if (motor.off() == true) {
    if (pos > 0) {
      pos -= 1;
    }
    else if (digitalRead(pushButton) == 1) {
      motor.on(int speed = 3, int some_time = 5000); // time unknown 
      hold = true;
      movDelay = 0;
    }
  }

  else if (pos > MAX_POS) {
    pos = MAX_POS;
    motor.write(0);
    motor.off();
  }

  else {
    if ((digitalRead(pushButton) == 1) && (hold == true)) {
      alternus = 1;
    }
    else {
      hold = false;
      alternus = (digitalRead(pushButton)*(-2) + 1);
    }
    // print out the state of the button:
    if (movDelay == 0) {
        motor.write(motor.read() + alternus);
        pos += alternus;
        if (pos < 0) pos = 0;
        movDelay = 5;
    }
    else {
      movDelay -= 1;
    }
  }
  //Serial.println(pos);
  delay(1);

}
}
