#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  Serial.begin(9600);
  
  starttime = millis();
  endtime = starttime;
  while((endtime - starttime) < 500)
  {
    sensors_average = 0;
    sensors_sum = 0;
    for (int i = 0; i < 5; i++)
    {
      sensors[i] = analogRead(i);
      sensors_average += sensors[i] * (i - 2) * 100L;
      sensors_sum += int(sensors[i]);
     }
     set_point = int(sensors_average / sensors_sum);
     if ( )
     pset_point
   }
}

void loop() 
{
}
