#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

float Kp = 2.5;
float Ki = 0.3;
float Kd = 0;
int evl = 100;

long sensors_average = 0;
int sensors_sum = 0;
int sensors[] = {0, 0, 0, 0, 0};
int error_value;
int set_point = 15;
int x;
int y;
int integral;
int last_proportional;
 
void setup()
{
 Serial.begin(9600);
 
 ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
 ADCSRA |= (1 << ADPS2);
 
 delay(1000);
 
 /*sensors_average = 0;
 sensors_sum = 0;
 
 for (int i = 0; i < 5; i++)
 {
  sensors[i] = analogRead(i);
  sensors_average += sensors[i] * (i - 2) * 100L;
  sensors_sum += int(sensors[i]);
 }
 set_point = int(sensors_average / sensors_sum);*/
}


void loop()
{
  sensors_read();
  calc_pid();
  calc_turn();
  run_motors();
  //Serial.println(error_value);
  //delay(500);
}


void sensors_read()
{
  sensors_average = 0;
  sensors_sum = 0;
  for (int i = 0; i < 5; i++)
  {
    sensors[i] = analogRead(i);
    sensors_average += sensors[i] * (i - 2) * 100L;
    sensors_sum += int(sensors[i]);
  }
}


void calc_pid()
{
  int pos, proportional, derivative;
  pos = int(sensors_average / sensors_sum);
  proportional = pos - set_point;
  integral += proportional;
  if(integral > 50)
  {
    integral = 50;
  }
  if(integral < -50)
  {
    integral = -50;
  }
  derivative = proportional - last_proportional;
  last_proportional = proportional;
  error_value = int(proportional * Kp + integral * Ki + derivative * Kd);
  
  /*Serial.print(proportional);
  Serial.print(",");
  Serial.print(integral);
  Serial.print(",");
  Serial.print(derivative);
  Serial.print(",");*/
  
  if (error_value < -evl)
  {
    error_value = -evl;
  }
  if (error_value > evl)
  {
    error_value = evl;
  }
}



void calc_turn()
{
  if (sensors[0] < 20 || sensors[4] < 20)
  {
    x = evl + error_value;
    y = evl - error_value;
  }
  else
  {
    x = 255 + error_value;
    y = 255 - error_value;
  }
}

void run_motors()
{
  if(sensors_sum < 600)
  {
    motor1.setSpeed(x);
    motor2.setSpeed(y);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  else
  {
    delay(100);
    motor1.setSpeed(80);
    motor2.setSpeed(80);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(100);
  }
}
