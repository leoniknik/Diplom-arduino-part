#include <MQ.h>
#include <iarduino_DHT.h>
#include <StandardCplusplus.h>
#include <vector>

using namespace std;

#define PIN_MQ  A0
#define PIN_DHT 4
#define PIN_LIGHT A1

MQ mq(PIN_MQ);
iarduino_DHT DHT(PIN_DHT);

struct Rule {
  int id;
  int hour;
  int minute;
  int mode;
};

vector<Rule> rules;

void setup()
{
  Serial.begin(9600);
  mq.calibrate();
  delay(1000);
}

void loop()
{
  checkSmoke();
  checkTemAndHum();
  checkLight();
  checkSchedule();
  delay(1000);
}

void checkSmoke() 
{
  Serial.print(" Smoke: ");
  Serial.print(mq.readSmoke());
  Serial.println(" ppm ");
}

void checkTemAndHum() 
{
  DHT.read();
  Serial.println(DHT.hum);
  Serial.println(DHT.tem);
}

void checkSchedule() 
{
  
}

void checkLight() {
  int light = analogRead(PIN_LIGHT);
  Serial.println(light);
}


