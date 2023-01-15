#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial bt(2, 3); /* (Rx,Tx) */
Servo myservo;

int led = 13;
int servoMin = 0;
int servoMax = 30;

void setup()
{
    bt.begin(9600);     /* Define baud rate for software serial communication */
    Serial.begin(9600); /* Define baud rate for serial communication */
    pinMode(led, OUTPUT);

    myservo.attach(9);

    Serial.println("> Start");
}

void loop()
{
    String command;
    if (bt.available()) /* If data is available on serial port */
    {
        command = bt.readString();
        Serial.println(command);

        servoMove(command);
        switchOn(command);
    }
}

void switchOn(String command)
{
    if (command == "on")
    {
        digitalWrite(led, HIGH);
    }

    if (command == "off")
    {
        digitalWrite(led, LOW);
    }
}

void servoMove(String command)
{
    if (command == "on")
    {
        Serial.println("SERVO ON");
        for (int pos = servoMin; pos <= servoMax; pos--)
        {
            myservo.write(pos);
            delay(5);
        }
    }

    if (command == "off")
    {
        Serial.println("SERVO OFF");
        for (int pos = servoMax; pos >= servoMin; pos--)
        {
            myservo.write(pos);
            delay(5);
        }
    }
}
