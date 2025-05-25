// #include <MotorDriver.h>

#define bt  Serial1
#define checkIfBetween(value, min, max) (value >= min && value < max)
#define btMode  1

#define FR 1
#define FL 2
#define BL 3
#define BR 4

// MotorDriver run;

#define FORWARD   1
#define BACKWARD  2
#define RELEASE   3

#define D1EN1 10
#define D1IN1 6
#define D1IN2 7
#define D1IN3 8
#define D1IN4 9
#define D1EN2 11

#define D2EN1 12
#define D2IN1 3
#define D2IN2 2
#define D2IN3 5
#define D2IN4 4
#define D2EN2 13

int r = 0, theta = 0, x = 0, y = 0, turnL = 0, turnR = 0;
String serialStr = "";
int maxSpeed = 210;
int baseSpeed = 128;
int minSpeed = 0;

// void moveBot(int speed, int direction) {
//   direction %= 360;
//   // direction = constrain(direction, 0, 360);
//   speed = constrain(speed, 0, 100);
//   if(checkIfBetween(direction, 0, 90)) {
//     motorWrite(FR, baseSpeed);
//     motorWrite(BL, baseSpeed);
//     int offset = map(direction, 0, 90, -baseSpeed, baseSpeed);
//     motorWrite(FL, offset);
//     motorWrite(BR, offset);
//   } else if(checkIfBetween(direction, 90, 180)) {
//     motorWrite(FL, baseSpeed);
//     motorWrite(BR, baseSpeed);
//     int offset = map(direction, 90, 180, baseSpeed, -baseSpeed);
//     motorWrite(FR, offset);
//     motorWrite(BL, offset);
//   } else if(checkIfBetween(direction, 180, 270)) {
//     motorWrite(FR, -baseSpeed);
//     motorWrite(BL, -baseSpeed);
//     int offset = map(direction, 180, 270, baseSpeed, -baseSpeed);
//     motorWrite(FL, offset);
//     motorWrite(BR, offset);
//   } else if(checkIfBetween(direction, 270, 360)) {
//     motorWrite(FL, -baseSpeed);
//     motorWrite(BR, -baseSpeed);
//     int offset = map(direction, 270, 360, -baseSpeed, baseSpeed);
//     motorWrite(FR, offset);
//     motorWrite(BL, offset);
//   }
// }
void moveBot(int speed, int direction) {
  direction %= 360;
  // direction = constrain(direction, 0, 360);
  speed = constrain(speed, 0, 100);
  speed = map(speed, 0, 100, 0, 255);
  if(checkIfBetween(direction, 0, 90)) {
    motorWrite(FR, speed);
    motorWrite(BL, speed);
    int offset = map(direction, 0, 90, -speed, speed);
    motorWrite(FL, offset);
    motorWrite(BR, offset);
  } else if(checkIfBetween(direction, 90, 180)) {
    motorWrite(FL, speed);
    motorWrite(BR, speed);
    int offset = map(direction, 90, 180, speed, -speed);
    motorWrite(FR, offset);
    motorWrite(BL, offset);
  } else if(checkIfBetween(direction, 180, 270)) {
    motorWrite(FR, -speed);
    motorWrite(BL, -speed);
    int offset = map(direction, 180, 270, speed, -speed);
    motorWrite(FL, offset);
    motorWrite(BR, offset);
  } else if(checkIfBetween(direction, 270, 360)) {
    motorWrite(FL, -speed);
    motorWrite(BR, -speed);
    int offset = map(direction, 270, 360, -speed, speed);
    motorWrite(FR, offset);
    motorWrite(BL, offset);
  }
}
void stopBot() {
  motorWrite(FL, 0);
  motorWrite(FR, 0);
  motorWrite(BL, 0);
  motorWrite(BR, 0);
}
/*void motorWrite(byte nMotor, int speed) {
  speed = constrain(speed, -255, 255);
  if(speed > 0) {
    run.motor(nMotor, FORWARD, speed);
  } else if (speed < 0) {
    run.motor(nMotor, BACKWARD, abs(speed));
  } else {
    run.motor(nMotor, RELEASE, speed);
  }
}*/
void motor(byte nMotor, byte command, byte speed){
  switch(nMotor) {
    case 1:
      switch(command){
        case 1:   digitalWrite(D1IN1, HIGH); digitalWrite(D1IN2, LOW); break;
        case 2:   digitalWrite(D1IN1, LOW); digitalWrite(D1IN2, HIGH); break;
        default:  digitalWrite(D1IN1, LOW); digitalWrite(D1IN2, LOW); break;
      }
      analogWrite(D1EN1, speed);
    break;
    case 2:
      switch(command){
        case 1:   digitalWrite(D1IN3, HIGH); digitalWrite(D1IN4, LOW); break;
        case 2:   digitalWrite(D1IN3, LOW); digitalWrite(D1IN4, HIGH); break;
        default:  digitalWrite(D1IN3, LOW); digitalWrite(D1IN4, LOW); break;
      }
      analogWrite(D1EN2, speed);
    break;
    case 3:
      switch(command){
        case 1:   digitalWrite(D2IN1, HIGH); digitalWrite(D2IN2, LOW); break;
        case 2:   digitalWrite(D2IN1, LOW); digitalWrite(D2IN2, HIGH); break;
        default:  digitalWrite(D2IN1, LOW); digitalWrite(D2IN2, LOW); break;
      }
      analogWrite(D2EN1, speed);
    break;
    case 4:
      switch(command){
        case 1:   digitalWrite(D2IN3, HIGH); digitalWrite(D2IN4, LOW); break;
        case 2:   digitalWrite(D2IN3, LOW); digitalWrite(D2IN4, HIGH); break;
        default:  digitalWrite(D2IN3, LOW); digitalWrite(D2IN4, LOW); break;
      }
      analogWrite(D2EN2, speed);
    break;
  }
}
void motorWrite(byte nMotor, int speed) {
  speed = constrain(speed, -255, 255);
  if(speed > 0) {
    motor(nMotor, FORWARD, speed);
  } else if (speed < 0) {
    motor(nMotor, BACKWARD, abs(speed));
  } else {
    motor(nMotor, RELEASE, speed);
  }
}

void initSerial() {
  Serial.begin(115200);
  bt.begin(115200);
  Serial.println("Starting Bot");
  bt.println("Starting Bot");
}
void readBt() {
  if(btMode == 0) {
    while(bt.available()) {
      char k = bt.read();
      // Serial.print((int)k, HEX); Serial.print(" ");
      if((k >= 'A' && k <= 'Z') || (k >= 'a' && k <= 'z') || (k >= '0' && k <= '9') || k == ',' || k == '|' || k == '!') serialStr += k;
      if(k == '\n' || k == '!') serialStr = "";
    }
    if(serialStr != "")  Serial.println(serialStr);
    char data = serialStr.charAt(0);
      switch(data) {
        case 'F': 
          r = map(baseSpeed, 0, 255, 0, 100);
          theta = 90;
          break;
        case 'B':
          r = map(baseSpeed, 0, 255, 0, 100);
          theta = 270;
          break;
        case 'L':
          r = map(baseSpeed, 0, 255, 0, 100);
          theta = 180;
          break;
        case 'R':
          r = map(baseSpeed, 0, 255, 0, 100);
          theta = 0;
          break;
        case 'S': stopBot();  r = 0; theta = 0; break;
        case 'P': readBtPolar(); break;
        case 'C': readBtCartesian(); break;
        case 'T': readBtTurn(); break;
        default:;
      }
  } else {
    if(bt.available() > 0) {
      char cmd = bt.read();
      switch(cmd) {
        case 'f':
        case 'F':
          r = map(baseSpeed, 0, 255, 0, 100);
          theta = 90;
          break;
        case 'b':
        case 'B':
          r = map(baseSpeed, 0, 255, 0, 100);
          theta = 270;
          break;
        case 'l':
        case 'L':
          r = map(baseSpeed, 0, 255, 0, 100);
          theta = 180;
          break;
        case 'r':
        case 'R':
          r = map(baseSpeed, 0, 255, 0, 100);
          theta = 0;
          break;
        case 's':
        case 'S': stopBot();  r = 0; theta = 0; break;
        case '0': baseSpeed = (int)(maxSpeed * 0.1); break;
        case '1': baseSpeed = (int)(maxSpeed * 0.2); break;
        case '2': baseSpeed = (int)(maxSpeed * 0.3); break;
        case '3': baseSpeed = (int)(maxSpeed * 0.4); break;
        case '4': baseSpeed = (int)(maxSpeed * 0.5); break;
        case '5': baseSpeed = (int)(maxSpeed * 0.6); break;
        case '6': baseSpeed = (int)(maxSpeed * 0.7); break;
        case '7': baseSpeed = (int)(maxSpeed * 0.8); break;
        case '8': baseSpeed = (int)(maxSpeed * 0.9); break;
        case '9': baseSpeed = (int)(maxSpeed * 1.0); break;
      }
    }
  }
}
void readBtPolar() {
  String temp = "";
  while(bt.available()) {
    char k = bt.read();
    temp += k;
    if(k != '|' && k != ',') {
      if(k != '\n') serialStr += k;
    } else {
      // Serial.print((String)k + "~");
      if(k == ',') r = serialStr.toInt();
      if(k == '|') theta = serialStr.toInt();
      // Serial.println(serialStr);
      serialStr = "";
    }
  }
  // Serial.println(temp);
  r = constrain(r, 0, 100);
}
void readBtCartesian() {
  while(bt.available()) {
    char k = bt.read();
    if(k != '|' && k != ',') {
      if(k != '\n') serialStr += k;
    } else {
      // Serial.print((String)k + "~");
      if(k == ',') x = serialStr.toInt();
      if(k == '|') y = serialStr.toInt();
      // Serial.println(serialStr);
      serialStr = "";
    }
  }
}
void readBtTurn() {
  while(bt.available()) {
    char k = bt.read();
    if(k != '|' && k != ',') {
      if(k != '\n') serialStr += k;
    } else {
      // Serial.print((String)k + "~");
      // if(k == ',') turnL = serialStr.toInt();
      if(k == '|') turnR = serialStr.toInt();
      // Serial.println(serialStr);
      serialStr = "";
    }
  }
}

void setup() {
  initSerial();
  stopBot();
}

void loop() {
  readBt();
  if(r > 0) moveBot(r, theta);
  else stopBot();
  // Serial.print(r); Serial.print(" ");
  // Serial.print(theta); Serial.print(" ");
  // Serial.print(turnL); Serial.print(" ");
  // Serial.print(turnR); Serial.print(" ");
  // Serial.println();
}
