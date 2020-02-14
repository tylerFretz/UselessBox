/*  Purpose: Useless box -- A machine that turns itself off after being turned on
 *  Author: Tyler Fretz
 *  Date: 12/12/2019
 *  Citation: Inspiration for arm/lid movement style from reddit user u/ahhTheSnorch. URL --> https://www.youtube.com/watch?time_continue=53&v=kproPsch7i0&feature=emb_logo
 *  link to u/ahhTheSnorch's code --> https://codebender.cc/sketch:273092#Useless_Machine_Final.ino
 */

#include <Servo.h>
Servo lidservo;
Servo armservo; 

const int buzzer = 5;
const int knockSensor = A0;
const int switchpin = 4;

//max arm & lid servo positions
const int armClosed = 15;     
const int armOpen = 147;
const int lidClosed = 128;
const int lidOpen = 90;

//changing variables
int action = 1;
int pos = 0;
int knockVal = 0;

void setup() {
pinMode(buzzer, OUTPUT);
pinMode(switchpin,INPUT);
armservo.attach(3);

//starting position for arm
armservo.write(armClosed);
}

void loop() {

  knockVal = analogRead(knockSensor);   //get integer value from the lid knock sensor

  if (digitalRead(switchpin) == LOW)    //if the switch has been pushed, preform an action
  {
    if (action > 8) {                     //reset back to action #1 after whole cycle has been preformed
      action = 1;
    } 
    switch(action){
      case 1:
        action1();
        break;
      case 2:
        action2();
        break;
      case 3:
        action3();
        break;
      case 4:
        action4();
        break;
      case 5:
        action5();
        break;
      case 6:
        action6();
        break;
      case 7:
        action7();
        break;
      case 8:
        action8();
        break;  
    }
    action += 1;                //increment the actions
  }

  if (digitalRead(switchpin) == HIGH)   //check for knock and respond only while switch has not been pushed
  {
    if (knockVal >= 225){
      delay(1500);
      knockBuzz();
      delay(200);
    }
  }
}

//methods

void buzz(){                      //buzzer tone that plays during action #8
  tone(buzzer, 1700, 150);
  delay(300);
  tone(buzzer, 1700, 150);
  delay(300);
  tone(buzzer, 1700, 150);
  delay(300);
  tone(buzzer, 1700, 150);
  delay(300);
  tone(buzzer, 1700, 150);
  delay(300);
  tone(buzzer, 1700, 300);
  delay(100);
  tone(buzzer, 1700, 2000);
  delay(200);
  tone(buzzer, 1500, 1000);
  delay(200);
  tone(buzzer, 1900, 2000);
  delay(200);
}

void knockBuzz(){                   //buzzer tone that plays after a knock on lid
  tone(buzzer, 1900, 200);
  delay(300);
  tone(buzzer, 1500, 200);
  delay(300);
  tone(buzzer, 1300, 200);
  delay(100);
}

// methods for arm/lid movement based on number of switch flips

void action1() {  //standard open close
  lidservo.attach(2);                  //attaching lid during action 1 to avoid servo hum on start up
  delay(100);
  lidservo.write(lidOpen);
  delay(100);
  lidservo.detach();                  //need to detach lid servo from pwm while it is under load to avoid servo hum
  delay(1000);
  armservo.write(armOpen);
  delay(500); 
  armservo.write(armClosed);
  delay(900);
  lidservo.attach(2);
  delay(100);                         //delay after reattach to ensure proper connection
  lidservo.write(lidClosed);
  delay(1000);
  lidservo.detach();
}

void action2() {   //quick open close
  lidservo.attach(2);
  delay(100);
  lidservo.write(lidOpen);
  delay(100);
  armservo.write(armOpen);
  delay(250);
  armservo.write(armClosed);
  delay(100);
  lidservo.write(lidClosed);
  delay(100);
  lidservo.detach();
}

void action3() {    //slow open
  lidservo.attach(2);
  delay(100); 
  for(pos = 128; pos > 90; pos -=1)
  {
    lidservo.write(pos);
    delay(50);
  }
  lidservo.detach();
  delay(100);
  armservo.write(armOpen);
  delay(500);
  armservo.write(armClosed);
  lidservo.attach(2);
  delay(100);
  lidservo.write(lidClosed);
  delay(200);
  lidservo.detach();
}

void action4() {      //hold arm on switch
  lidservo.attach(2);
  delay(250);
  lidservo.write(lidOpen);
  delay(100);
  lidservo.detach();
  armservo.write(armOpen);
  delay(2500);
  for(pos = 147; pos > 15; pos -=2)
  {
    armservo.write(pos);
    delay(50);
  }
  lidservo.attach(2);
  delay(100);
  lidservo.write(lidClosed);
  delay(100);
  lidservo.detach();
}

void action5() {     //fast repeat open/close lid
  lidservo.attach(2);
  delay(100);
  lidservo.write(lidOpen); 
  delay(500);
  lidservo.write(lidClosed); 
  delay(500);
  lidservo.write(lidOpen);  
  delay(500);
  lidservo.write(lidClosed);  
  delay(500);
  lidservo.write(lidOpen);  
  delay(500);
  lidservo.write(lidClosed);
  delay(2500);
  lidservo.write(lidOpen);
  delay(100);
  armservo.write(armOpen);
  delay(250);
  armservo.write(armClosed);
  delay(100);
  lidservo.write(lidClosed);
  delay(100);
  lidservo.detach();
}

void action6() {     //fast arm psyche out touch
  lidservo.attach(2);
  delay(100);
  lidservo.write(lidOpen);
  delay(100);
  armservo.write(128);
  delay(250);
  armservo.write(armClosed);
  delay(100);
  lidservo.write(lidClosed);
  delay(250);
  lidservo.write(lidOpen);
  delay(100);
  armservo.write(128);
  delay(250);
  armservo.write(armClosed);
  delay(100);
  lidservo.write(lidClosed);
  delay(250);
  lidservo.write(lidOpen);
  delay(100);
  armservo.write(128);
  delay(250);
  armservo.write(armClosed);
  delay(100);
  lidservo.write(lidClosed);
  delay(250);  
  lidservo.write(lidOpen);
  delay(100);
  armservo.write(armOpen);
  delay(250);
  armservo.write(armClosed);
  delay(100);
  lidservo.write(lidClosed);
  delay(100);
  lidservo.detach();
}

void action7() {       //slow open, slow arm
  lidservo.attach(2);
  delay(100);
  for(pos = 128; pos > 80; pos -=2)
  {
    lidservo.write(pos);
    delay(50);
  }
  lidservo.detach();
  for(pos = 15; pos < 81; pos +=2)
  {
    armservo.write(pos);
    delay(50);
  }
  delay(500);
  armservo.write(armOpen);
  delay(250);
  for(pos = 147; pos > 15; pos -=2)
  {
    armservo.write(pos);
    delay(50);
  }
  lidservo.attach(2);
  delay(100);
  for(pos = 80; pos < 128; pos +=2)
  {
    lidservo.write(pos);
    delay(50);
  }
  lidservo.detach();
}

void action8() {     //vocal annoyed arm
  lidservo.attach(2);
  delay(100);
  lidservo.write(lidOpen);
  delay(200);
  lidservo.detach();
  armservo.write(105);
  delay(300);
  buzz();
  delay(1000);
  armservo.write(armClosed);
  delay(1000);
  armservo.write(armOpen);
  delay(300);
  armservo.write(armClosed);
  lidservo.attach(2);
  delay(100);
  lidservo.write(lidClosed);
  delay(200);
  lidservo.detach();
}
