/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include <string.h>

#define SERVO1 9 //digital pin for camera setpoint signal
#define SERVO2 3

Servo servo_cam;  // servo object for camera yaw
Servo servo_gun; // // servo object for gun pitch

double cam_set = 0;
double gun_set = 0;

void setup() {
  servo_cam.attach(9);
  servo_gun.attach(3);
  Serial.begin(9600); // serial comm to raspi
  Serial.print("Setup success");
}

char s[]="180,360";
void loop() {
  //read setpoint
  char *s1;
  char *s2;
  
  delay(1000);
  if(Serial.available())
  {
    get_setpoint();  //get setpoint from serial communication
    cam_set = map(cam_set, 0, 360, 0, 360);     // scale it to use it with the servo (value between 0 and 180)
    gun_set = map(gun_set, 0, 180, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  }
  
  Serial.print("cam_set = ");
  Serial.println(cam_set);
  Serial.print("gun_set = ");
  Serial.println(gun_set);
  
  //Move the servo
  servo_cam.write(cam_set);                  // sets the servo position according to the scaled value
  servo_gun.write(gun_set);
  delay(1000);
  //servo_cam.write(0);                  // sets the servo position according to the scaled value
  
}

void get_setpoint()
{
  String serialResponse;
  serialResponse = Serial.readStringUntil('\0');
  char buf[sizeof(s)];
  serialResponse.toCharArray(buf, sizeof(buf));
  char *p = buf;
  char *camc, *gunc;  //string variable for cam and gun
  
  char *str;
  str = strtok_r(p, ",", &p); 
  while (str  != NULL) // delimiter is the semicolon
  {
      //camc = &str[0];
      //String s=camc;
      //cam_set = s.toFloat();
           
      if(str[0]=='c')
      {
        camc = &str[1];
        String s=camc;
        cam_set = s.toFloat();
        
      }else if(str[0]=='g'){
        gunc = &str[1];
        String s=gunc;
        gun_set = s.toFloat();
      }
    str = strtok_r(p, ",", &p);
  }
}


