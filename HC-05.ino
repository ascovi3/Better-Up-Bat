#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Wire.h>

//variables for fsr
int fsrPin1 = 0;
int fsrPin2 = 1;
int fsrPin3 = 2;
int fsrPin4 = 3;    
int fsrReading;  
int fsrReading1;
int fsrReading2;
int fsrReading3;
int fsrReading4;
int zone = 0;
//variables for adxl
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
float time_acceleration;
float dvX;
float vx = 0;
float dvY;
float vy = 0;
float dvZ;
float vz = 0;

void setup() {
  
  Serial.begin(9600);   //baud rate
  //setup for bluetooth
    while(!Serial)
    {
      //waiting for bluetooth to connect
    }
    
  //set up for adxl
  Wire.begin();
  if (!accel.begin())
  {
    Serial.println("No ADXL345 sensor detected.");
    while (1);
  }
}

void loop() {

      velocityDetect();
      Serial.print("VX: "); Serial.print(vx); Serial.print("  ");
      Serial.print("VY: "); Serial.print(vy); Serial.print("  ");
      Serial.print("VZ: "); Serial.print(vz); Serial.print("  ");
      Serial.println("m/s");

      //Print and determining zone
      pinDetect(fsrPin1, fsrPin2, fsrPin3, fsrPin4);
      Serial.print("The ball hit zone ");
      Serial.println(zone); 

      delay(200);

}

//determines zone
int pinDetect(int fPin1, int fPin2, int fPin3, int fPin4) {
  fsrReading = 0;
  fsrReading1 = analogRead(fPin1);
  fsrReading2 = analogRead(fPin2);
  fsrReading3 = analogRead(fPin3);
  fsrReading4 = analogRead(fPin4);
  if (fsrReading1 > fsrReading){
    fsrReading = fsrReading1;
    zone = 1;
  }
  if (fsrReading2 > fsrReading){
    fsrReading = fsrReading2;
    zone = 2;
  }
  if (fsrReading3 > fsrReading){
    fsrReading = fsrReading3;
    zone = 3;
  }
  if (fsrReading4 > fsrReading){
    fsrReading = fsrReading4;
    zone = 4;
  }
    return zone;
}

int velocityDetect(){
  for(int i = 0; i < 50; i++){
    sensors_event_t event;
    accel.getEvent(&event);

    //Serial.print("AX: "); Serial.println(event.acceleration.x);
    //Serial.print("AY: "); Serial.println(event.acceleration.y);
    //Serial.print("AZ: "); Serial.println(event.acceleration.z);
   
    dvX = (event.acceleration.x/9.81) * (.010);  // because we know the delay so the difference in time.
    dvY = (event.acceleration.y/9.81) * (.010);
    dvZ = (event.acceleration.z/9.81-1.2) * (.010);
  
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
