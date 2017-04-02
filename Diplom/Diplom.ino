#include <MQ.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TroykaDHT11.h>
#include <TimeLib.h>

using namespace std;

#define PIN_MQ  A0
#define PIN_DHT 4
#define PIN_LIGHT A1
#define RELAY_1 13
#define RELAY_2 12
#define RELAY_3 11
#define RELAY_LIGHT 10

MQ mq(PIN_MQ);
DHT11 DHT(PIN_DHT);

int ARDUINO_ID = 0;
int LIGHT_TRESHHOLD = 600;
int SMOKE_TRESHHOLD = 0;
int TEMPRETURE_MIN = 20;
int TEMPRETURE_MAX = 26;
int HUMIDITY_MIN = 30;
int HUMIDITY_MAX = 60;

struct Rule {
  int relay;
  int ruleHour;
  int ruleMinute;
  int mode;
};


vector<Rule> rules;

void setup()
{
  Serial.begin(9600);
  mq.calibrate();
  initRelay();
  delay(1000);
  printSettings();
}

void loop()
{
  checkSmoke();
  checkTemAndHum();
  checkLight();
  checkSchedule();
  delay(1000);
}

void initRelay() {
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_LIGHT, OUTPUT);
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_LIGHT, HIGH);
}

void checkSmoke()
{
  int smoke = mq.readSmoke();
  Serial.print(" Smoke: ");
  Serial.print(smoke);
  Serial.println(" ppm ");
  if (smoke > SMOKE_TRESHHOLD) {

  }
}

void checkTemAndHum()
{
  int tempreture = 0;
  int humidity = 0;
  switch (DHT.read()) {
    case DHT_OK:
      tempreture = DHT.getTemperatureC();
      humidity = DHT.getHumidity();
      Serial.print("Temperature = ");
      Serial.print(tempreture);
      Serial.print("C \t");
      Serial.print("Humidity = ");
      Serial.print(humidity);
      Serial.println("%");
      if (tempreture < TEMPRETURE_MIN || tempreture > TEMPRETURE_MAX) {

      }
      if (humidity < HUMIDITY_MIN || humidity > HUMIDITY_MAX) {

      }
      break;
    default:
      Serial.println("Unknown error");
      break;
  }
}

void checkSchedule()
{
  for (int i = 0; i < rules.size(); i++)
  {
    if (rules[i].ruleHour == hour() && rules[i].ruleMinute == minute())
    {
        digitalWrite(rules[i].relay, rules[i].mode);
    }
  }
}

void checkLight() {
  int light = analogRead(PIN_LIGHT);
  Serial.println(light);
  if (light > LIGHT_TRESHHOLD) {

  }
}

void initTime(int hour, int minute, int second) {
  setTime(hour, minute, second, 1, 1, 2017);
}

void printSettings() {
  Serial.print("PIN_MQ: ");
  Serial.println(PIN_MQ);
  Serial.print("PIN_DHT: ");
  Serial.println(PIN_DHT);
  Serial.print("PIN_LIGHT: ");
  Serial.println(PIN_LIGHT);
  Serial.print("RELAY_1: ");
  Serial.println(RELAY_1);
  Serial.print("RELAY_2: ");
  Serial.println(RELAY_2);
  Serial.print("RELAY_3: ");
  Serial.println(RELAY_3);
  Serial.print("ARDUINO_ID: ");
  Serial.println(ARDUINO_ID);
  Serial.print("LIGHT_TRESHHOLD: ");
  Serial.println(LIGHT_TRESHHOLD);
  Serial.print("SMOKE_TRESHHOLD: ");
  Serial.println(SMOKE_TRESHHOLD);
  Serial.print("TEMPRETURE_MIN: ");
  Serial.println(TEMPRETURE_MIN);
  Serial.print("TEMPRETURE_MAX: ");
  Serial.println(TEMPRETURE_MAX);
  Serial.print("HUMIDITY_MIN: ");
  Serial.println(HUMIDITY_MIN);
  Serial.print("HUMIDITY_MAX: ");
  Serial.println(HUMIDITY_MAX);
}

