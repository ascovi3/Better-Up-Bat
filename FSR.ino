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

void setup() {
  Serial.begin(9600);
}

void loop() {
  pinDetect(fsrPin1, fsrPin2, fsrPin3, fsrPin4);
  Serial.print("The ball hit zone ");
  Serial.println(zone);
}

int pinDetect(int fPin1, int fPin2, int fPin3, int fPin4) {
  fsrReading = 0;
  fsrReading1 = analogRead(fPin1);
  Serial.print("FSR1: "); Serial.println(fsrReading1);
  fsrReading2 = analogRead(fPin2);
  Serial.print("FSR2: "); Serial.println(fsrReading2);
  fsrReading3 = analogRead(fPin3);
  Serial.print("FSR3: "); Serial.println(fsrReading3);
  fsrReading4 = analogRead(fPin4);
  Serial.print("FSR4: "); Serial.println(fsrReading4);
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
  delay(1000);
  return zone;
}
