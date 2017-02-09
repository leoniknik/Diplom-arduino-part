#include <MQ.h>

//имя для пина, к которому подключен датчик
#define PIN_MQ  A0
// создаём объект для работы с датчиком и передаём ему номер пина
MQ mq(PIN_MQ);

void setup()
{
  // открываем последовательный порт
  Serial.begin(9600);
  // выполняем калибровку датчика на чистом воздухе
  mq.calibrate();
}

void loop()
{
  Serial.print(" Smoke: ");
  Serial.print(mq.readSmoke());
  Serial.println(" ppm ");
  delay(1000);
}


