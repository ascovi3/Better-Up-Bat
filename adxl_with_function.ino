// Adafruit Unified Sensor - Version: 1.1.4
#include <Adafruit_Sensor.h>

// Adafruit ADXL345 - Version: 1.3.1
#include <Adafruit_ADXL345_U.h>

#include <Wire.h>


Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
float time_acceleration;
float dvX;
float vx = 0;
float dvY;
float vy = 0;
float dvZ;
float vz = 0;


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

  if (!accel.begin())
  {
    Serial.println("No ADXL345 sensor detected.");
    while (1);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
      velocityDetect();
      Serial.print("VX: "); Serial.print(vx); Serial.print("  ");
      Serial.print("VY: "); Serial.print(vy); Serial.print("  ");
      Serial.print("VZ: "); Serial.print(vz); Serial.print("  ");
      Serial.println("m/s");
      delay(500);
}

int velocityDetect(){
  for(int i = 0; i < 10; i++){
    sensors_event_t event;
    accel.getEvent(&event);
   
    dvX = (event.acceleration.x/9.81) * (.10);  // because we know the delay so the difference in time.
    dvY = (event.acceleration.y/9.81) * (.10);
    dvZ = (event.acceleration.z/9.81-1.2) * (.10);
  
    vx = vx + dvX;
    vy = vy + dvY;
    vz = vz + dvZ;

    if (event.acceleration.x/9.81 < 0.03 && event.acceleration.x/9.81 > -0.03) {
      vx = 0;  
    }

    if (event.acceleration.y/9.81 < .11 && event.acceleration.y/9.81 > -.11) {
      vy = 0;  
    }

    if ((event.acceleration.z/9.81)-1.2 < 0.03 && (event.acceleration.z/9.81)-1.2 > -0.03) {
      vz = 0;  
    }
    delay(10);
   }
  

     //need to choose whichever direction we mount it in and only print that
  return vx;
  return vy;
  return vz;

}
