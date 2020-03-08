#include <Servo.h>

Servo servo;

int mic = 2;

int pinservo = 3;
int pulsoMin = 1000;
int pulsoMax = 2000;
bool mode = true;
int sound;

void setup()
{
  pinMode(mic, INPUT);
  servo.attach(pinservo, pulsoMin, pulsoMax);
}

void loop()
{
  sound = digitalRead(mic);
  if(sound == HIGH && mode)
  {
    servo.write(150);
    mode = !mode;
    delay(1000);
    sleep();
  }
  else if(sound == HIGH && !mode)
  {
    servo.write(30);
    mode = !mode;
    delay(1000);
    sleep();
  }
  delay(1000);
}


void sleep()      //Stays in the middle of both states so it isn´t always working on pushing the light switch.
{
  servo.write(90);
  delay(500);
}
