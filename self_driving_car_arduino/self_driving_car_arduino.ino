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

const int D0 = 0;   // Raspberry Pi Pin 21  LSB
const int D1 = 1;   // Raspberry Pi Pin 22
const int D2 = 2;   // Raspberry Pi Pin 23
const int D3 = 3;   // Raspberry Pi Pin 24  MSB

int a, b, c, d, data_dec;

void data()
{
  a = digitalRead(D0);
  b = digitalRead(D1);
  c = digitalRead(D2);
  d = digitalRead(D3);

  data_dec = 8 * d + 4 * c + 2 * b + a;
}

void setup() 
{
  pinMode(ENABLE_L, OUTPUT);
  pinMode(HIGH_L, OUTPUT);
  pinMode(LOW_L, OUTPUT);

  pinMode(ENABLE_R, OUTPUT);
  pinMode(HIGH_R, OUTPUT);
  pinMode(LOW_R, OUTPUT);

  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
}

void stop_car()
{
  // Left Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_L, LOW);
  digitalWrite(LOW_L, HIGH);

  // PWM Left
  analogWrite(ENABLE_L, 0);

  // Right Side Motor
  // Write only after testing the forward and backward direction
  digitalWrite(HIGH_R, LOW);
  digitalWrite(LOW_R, HIGH);

  // PWM Right
  analogWrite(ENABLE_R, 0);
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
  analogWrite(ENABLE_L, 160);

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
  analogWrite(ENABLE_L, 90);

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
  analogWrite(ENABLE_L, 50);

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
  analogWrite(ENABLE_R, 160);
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
  analogWrite(ENABLE_R, 90);
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
  analogWrite(ENABLE_R, 50);
}

void loop() 
{
  // Retrieve Data
  data();
  
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

  if(data == 0)
  {
    forward();
  }
  else if(data == 1)
  {
    right1();  
  }
  else if(data == 2)
  {
    right2();  
  }
  else if(data == 3)
  {
    right3();  
  }
  else if(data == 4)
  {
    left1();  
  }
  else if(data == 5)
  {
    left2();  
  }
  else if(data == 6)
  {
    left3();  
  }
  else if(data > 6)
  {
    stop_car(); 
  }
}
