/*
Programme réalisé par Valentin BONNET dans le cadre des PPE - Terminale SSI,
Groupe panneau solaire orientable Année 2017-2018
*/

//Setup Motors
#include <DRV8835MotorShield.h>
#define LED_PIN 13
DRV8835MotorShield motors;

//Setup photocells
int photocellPinA2 = 2; // the cell connected to a2
int photocellPinA3 = 3; // the cell connected to a3
int photocellPinA4 = 4; // the cell connected to a4
int photocellPinA5 = 5; // the cell connected to a5
int photocellReadingA2; // the analog reading from the analog resistor divider a2
int photocellReadingA3; // the analog reading from the analog resistor divider a3
int photocellReadingA4; // the analog reading from the analog resistor divider a4
int photocellReadingA5; // the analog reading from the analog resistor divider a5

int averageLeft; //average of photocellReading A2 and A3
int averageRight; //average of photocellReading A4 and A5
boolean Night; //Boolean value of night
boolean ResetMotor; //Boolean value of reset motor

void setup()
{
  Serial.begin(9600); //Information via the Serial monitor
  
  //Setup Channel A
  pinMode(LED_PIN, OUTPUT);
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
}

void loop()
{
  photocellReadingA2 = analogRead(photocellPinA2);
  photocellReadingA3 = analogRead(photocellPinA3);
  photocellReadingA4 = analogRead(photocellPinA4);
  photocellReadingA5 = analogRead(photocellPinA5);

  /*Serial.print("A2 : ");
  Serial.print(photocellReadingA2); // the raw analog reading
  Serial.println("\n");
  Serial.print("A3 : ");
  Serial.print(photocellReadingA3); // the raw analog reading
  Serial.println("\n");
  Serial.print("A4 : ");
  Serial.print(photocellReadingA4); // the raw analog reading
  Serial.println("\n");
  Serial.print("A5 : ");
  Serial.print(photocellReadingA5); // the raw analog reading
  Serial.println("\n");*/

  averageRight = (photocellReadingA2+photocellReadingA3)/2;
  averageLeft = (photocellReadingA4+photocellReadingA5)/2;
  Serial.print("\nAverage Right : ");
  Serial.print(averageRight);
  Serial.print("\nAverage Left : ");
  Serial.print(averageLeft);

  if ((averageLeft + averageRight) > (300*2)){
    Night = false;
    ResetMotor = false;
    Serial.print("\nDay !");
  } else {
    Night = true;
    Serial.print("\nNight !");
  }

  if ((averageLeft >= averageRight) && (Night == false)){
    digitalWrite(LED_PIN, LOW);
    motors.setM1Speed(-400);
    Serial.print("\nChasing sun !");
  }
  else {
    digitalWrite(LED_PIN, LOW);
    motors.setM1Speed(0);
    Serial.print("\nStop Rotate");
  }

  if ((Night == true) && (ResetMotor == false)){
    Serial.print("\nGood night ! (Reset)");
    digitalWrite(LED_PIN, HIGH);
    motors.setM1Speed(400);
    Serial.print("\nReset start !");
    Serial.print("\nReset stake 0%");
    delay(10000);
    Serial.print("\nReset stake 10%");
    delay(10000);
    Serial.print("\nReset stake 20%");
    delay(10000);
    Serial.print("\nReset stake 30%");
    delay(10000);
    Serial.print("\nReset stake 40%");
    delay(10000);
    Serial.print("\nReset stake 50%");
    delay(10000);
    Serial.print("\nReset stake 60%");
    delay(10000);
    Serial.print("\nReset stake 70%");
    delay(10000);
    Serial.print("\nReset stake 80%");
    delay(10000);
    Serial.print("\nReset stake 90%");
    delay(10000);
    Serial.print("\nReset stake 100%");
    delay(5000);
    Serial.print("\nReset Done !");
    digitalWrite(LED_PIN, LOW);
    motors.setM1Speed(0);
    ResetMotor = true;
  }
}
