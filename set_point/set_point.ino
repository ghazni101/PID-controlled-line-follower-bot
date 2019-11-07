void setup() {
  Serial.begin(9600);
}

void loop()
{
 long sensors_average;
 long sensors_sum;
 int sensors[] = {0, 0, 0, 0, 0};
 for (int i = 0; i < 5; i++)
 {
  sensors[i] = analogRead(i);
  sensors_average += sensors[i] * (i - 2) * 100L;
  sensors_sum += int(sensors[i]);
 }
  int set_point = int(sensors_average / sensors_sum);
  Serial.print(sensors[0]);
  Serial.print(",");
  Serial.print(sensors[1]);
  Serial.print(",");
  Serial.print(sensors[2]);
  Serial.print(",");
  Serial.print(sensors[3]);
  Serial.print(",");
  Serial.print(sensors[4]);
  Serial.print(",");
  Serial.print(sensors_average);
  Serial.print(",");
  Serial.print(sensors_sum);
  Serial.print(",");
  Serial.println(set_point);
  delay(100);
 
  sensors_average = 0;
  sensors_sum = 0;
  set_point = 0;
}
