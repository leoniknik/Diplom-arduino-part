#ifndef MQ_H
#define MQ_H
#include <Arduino.h>
// кол-во считываний значений в цикле
#define MQ_SAMPLE_TIMES 5
// задержка после каждого считывания датчика
#define MQ_SAMPLE_INTERVAL 20

class MQ {
public:
  unsigned long readSmoke();
	MQ(uint8_t pin);

	inline bool isCalibrated() const {
		return _stateCalibrate;
	};
	inline float getRo() const {
		return _ro;
        };

private:
  unsigned long readScaled(float a, float b) const;
  float readRatio() const;
	bool _stateCalibrate = false;
	float _ro = 1.0f;
	uint8_t _pin;
	float readRs() const;
	float calculateResistance(int rawAdc) const;
  // Резистор установленный на плату (кОм)
  int getRL() const { return 5; }
  // коефициент чистого воздуха
  float getRoInCleanAir() const { return 9.83; }
};

#endif
