#include "MQ.h"

MQ::MQ(uint8_t pin) :
  _pin (pin) {
}

// калибровка
void MQ::calibrate() {
  float ro = 0;
  for (int i = 0; i < MQ_SAMPLE_TIMES; i++) {
    ro += calculateResistance(analogRead(_pin));
    delay(MQ_SAMPLE_INTERVAL);
  }
  ro = ro/MQ_SAMPLE_TIMES;
  ro = ro/getRoInCleanAir();
  _ro = ro;
  _stateCalibrate = true;
}

// сопротивление датчика
float MQ::calculateResistance(int rawAdc) const {
  float vrl = rawAdc*(5.0 / 1023);
  float rsAir = (5.0 - vrl)/vrl*getRL();
  return rsAir;
}

// показания дыма
unsigned long MQ::readSmoke() {
  return readScaled(-0.42, 3.54);
}

// чтение показаний с поправочными коэффицентами
unsigned long MQ::readScaled(float a, float b) const {
  float ratio = readRatio();
  return exp((log(ratio)-b)/a);
}

// чтение соотношения
float MQ::readRatio() const {
  return readRs()/getRo();
}

// считывание датчика
float MQ::readRs() const {
  float rs = 0;
  for (int i = 0; i < MQ_SAMPLE_TIMES; i++) {
    rs += calculateResistance(analogRead(_pin));
    delay(MQ_SAMPLE_INTERVAL);
  }
  rs = rs/MQ_SAMPLE_TIMES;
  return rs;
}
