/*
 * Self Driving Car 
 * Arduino Setup
 * Written By - Sagnik Chakraborty
*/

// Left Side Motor
const int ENABLE_L = 5;
const int HIGH_L = 6;
const int LOW_L = 7;

// Right Side Motor
const int ENABLE_R = 10;
const int HIGH_R = 8;
const int LOW_R = 9;

void setup() 
{
  pinMode(ENABLE_L, OUTPUT);
  pinMode(HIGH_L, OUTPUT);
  pinMode(LOW_L, OUTPUT);

  pinMode(ENABLE_R, OUTPUT);
  pinMode(HIGH_R, OUTPUT);
  pinMode(LOW_R, OUTPUT);
}

void forward()
{
  // Left Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_L, LOW);
  digitalWrite(LOW_L, HIGH);

  // PWM Left
  analogWrite(ENABLE_L, 255);

  // Right Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_R, LOW);
  digitalWrite(LOW_R, HIGH);

  // PWM Right
  analogWrite(ENABLE_R, 255);
}

void backward()
{
  // Left Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_L, HIGH);
  digitalWrite(LOW_L, LOW);

  // PWM Left
  analogWrite(ENABLE_L, 255);

  // Right Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_R, HIGH);
  digitalWrite(LOW_R, LOW);

  // PWM Right
  analogWrite(ENABLE_R, 255);
}

void left1()
{
  // Left Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_L, LOW);
  digitalWrite(LOW_L, HIGH);

  // PWM Left
  analogWrite(ENABLE_L, 200);

  // Right Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_R, LOW);
  digitalWrite(LOW_R, HIGH);

  // PWM Right
  analogWrite(ENABLE_R, 255);
}

void left2()
{
  // Left Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_L, LOW);
  digitalWrite(LOW_L, HIGH);

  // PWM Left
  analogWrite(ENABLE_L, 160);

  // Right Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_R, LOW);
  digitalWrite(LOW_R, HIGH);

  // PWM Right
  analogWrite(ENABLE_R, 255);
}

void left3()
{
  // Left Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_L, LOW);
  digitalWrite(LOW_L, HIGH);

  // PWM Left
  analogWrite(ENABLE_L, 100);

  // Right Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_R, LOW);
  digitalWrite(LOW_R, HIGH);

  // PWM Right
  analogWrite(ENABLE_R, 255);
}

void right1()
{
  // Left Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_L, LOW);
  digitalWrite(LOW_L, HIGH);

  // PWM Left
  analogWrite(ENABLE_L, 255);

  // Right Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_R, LOW);
  digitalWrite(LOW_R, HIGH);

  // PWM Right
  analogWrite(ENABLE_R, 200);
}

void right2()
{
  // Left Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_L, LOW);
  digitalWrite(LOW_L, HIGH);

  // PWM Left
  analogWrite(ENABLE_L, 255);

  // Right Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_R, LOW);
  digitalWrite(LOW_R, HIGH);

  // PWM Right
  analogWrite(ENABLE_R, 160);
}

void right3()
{
  // Left Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_L, LOW);
  digitalWrite(LOW_L, HIGH);

  // PWM Left
  analogWrite(ENABLE_L, 255);

  // Right Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_R, LOW);
  digitalWrite(LOW_R, HIGH);

  // PWM Right
  analogWrite(ENABLE_R, 100);
}

void loop() 
{
  // For Moving Forward
  // forward();

  // For Moving Backward
  // backward();

  // Low Left Turn
  // left1();

  // Moderate Left Turn
  // left2();

  // High Left Turn
  // left3();

  // Low Right Turn
  // right1();

  // Moderate Right Turn
  // right2();

  // High Right Turn
  // right3();
}
