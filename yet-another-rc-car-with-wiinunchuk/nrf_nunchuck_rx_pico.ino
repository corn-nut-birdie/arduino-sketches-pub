/*

  Radio    Pico
  CE    -> 20
  CSN   -> 17 (Hardware SPI SS)
  MOSI  -> 19 (Hardware SPI MOSI)
  MISO  -> 16 (Hardware SPI MISO)
  SCK   -> 18 (Hardware SPI SCK)
  IRQ   -> No connection
  VCC   -> No more than 3.6 volts
  GND   -> GND
*/


#include <NRFLite.h>

const static uint8_t RADIO_ID = 139;
const static uint8_t PIN_RADIO_CE = 20;
const static uint8_t PIN_RADIO_CSN = 17;

struct
{
  uint8_t FromRadioId;
  unsigned short counter;
  unsigned char c: 1;
  unsigned char z: 1;
  unsigned char x;
  unsigned char y;
  short r;
  short p;
} _data;

NRFLite _radio;

long cnt = 0;
int length;

const int lf = 12, lb = 13;
const int rf = 14, rb = 15;
bool driving = false;

long lastRecv;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, 113))
  {
    digitalWrite(LED_BUILTIN, HIGH);
    while (1);
  }

  lastRecv = millis();
}

void loop()
{
  while (length = _radio.hasData())
  {
    if (length != sizeof(_data)) {
      _radio.discardData(length);
      continue;
    }

    _radio.readData(&_data);

    cnt++;

    lastRecv = millis();

    if (_data.c) {
      driving = true;
    }
    if (_data.z) {
      driving = false;
    }

    float x = _data.x - 127;
    float y = _data.y - 127;
    float r = sqrt(x * x + y * y);
    float xAngle = r != 0 ? asin(x / r) / PI * 180 : 0;
    float yAngle = r != 0 ? asin(y / r) / PI * 180 : 0;

    String cmdStr = "";
    if (!driving || r < 40) {
      digitalWrite(lf, LOW);
      digitalWrite(lb, LOW);
      digitalWrite(rf, LOW);
      digitalWrite(rb, LOW);
    } else if (yAngle > 67.5) {
      digitalWrite(lf, HIGH);
      digitalWrite(lb, LOW);
      digitalWrite(rf, HIGH);
      digitalWrite(rb, LOW);
    } else if (yAngle < -67.5) {
      digitalWrite(lf, LOW);
      digitalWrite(lb, HIGH);
      digitalWrite(rf, LOW);
      digitalWrite(rb, HIGH);
    } else if (xAngle > 67.5) {
      digitalWrite(lf, HIGH);
      digitalWrite(lb, LOW);
      digitalWrite(rf, LOW);
      digitalWrite(rb, HIGH);
    } else if (xAngle < -67.5) {
      digitalWrite(lf, LOW);
      digitalWrite(lb, HIGH);
      digitalWrite(rf, HIGH);
      digitalWrite(rb, LOW);
    } else {
      digitalWrite(lf, LOW);
      digitalWrite(lb, LOW);
      digitalWrite(rf, LOW);
      digitalWrite(rb, LOW);
    }
  }

  if (millis() - lastRecv > 100) {
    digitalWrite(lf, LOW);
    digitalWrite(lb, LOW);
    digitalWrite(rf, LOW);
    digitalWrite(rb, LOW);
  }
}

