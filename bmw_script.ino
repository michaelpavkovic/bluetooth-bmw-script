#include <Servo.h>
#include <String.h>

/*
 * BMW M3 Arduino Script by Michael Pavkovic
 */

Servo esc;
Servo steering;

const int ESC_PWM = 9;
const int STEERING_PWM = 10;
bool esc_armed = false;
String incoming;
char cmd;
int steering_val = 85, speed_val = 62;


void setup() {
  Serial.begin(9600);
  
  esc.attach(ESC_PWM);
  steering.attach(STEERING_PWM);

  // Arm the ESC
  esc.write(48);
  delay(4000);
  esc_armed = true;
}

void loop() {
  if (Serial.available() > 0) { // Serial will be available if it returns something greater than 0
    incoming = Serial.readStringUntil('\n');
    cmd = incoming.charAt(0);
    incoming.remove(0, 1);
    if (incoming.charAt(0) == '0')
      incoming.remove(0, 1);

    if (cmd == 'a')
      steering_val = incoming.toInt();
    else if (cmd == 'b')
      speed_val = incoming.toInt();

//    Serial.println(steering_val);
    steering.write(steering_val);
    esc.write(speed_val);
    
    delay(25);
  }
}
