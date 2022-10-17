/*

  Radio    ESP32
  CE    -> 17
  CSN   -> 5 (Hardware SPI SS)
  MOSI  -> 23 (Hardware SPI MOSI)
  MISO  -> 19 (Hardware SPI MISO)
  SCK   -> 18 (Hardware SPI SCK)
  IRQ   -> No connection
  VCC   -> No more than 3.6 volts
  GND   -> GND

*/

/*
  22 -> SCL
  21 -> SDA
*/

#include <NRFLite.h>
#include <NintendoExtensionCtrl.h>

const static uint8_t RADIO_ID = 137;
const static uint8_t DESTINATION_RADIO_ID = 139;
const static uint8_t PIN_RADIO_CE = 17;
const static uint8_t PIN_RADIO_CSN = 5;

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

Nunchuk nchuk;

void setup()
{
  _data.counter = 0;
  _data.FromRadioId = RADIO_ID;

  pinMode(LED_BUILTIN, OUTPUT);

  nchuk.begin();
  if (!nchuk.connect()) {
    digitalWrite(LED_BUILTIN, HIGH);
    while (1) {
      delay(1000);
    }
  }

  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, 113))
  {
    digitalWrite(LED_BUILTIN, HIGH);
    while (1) {
      delay(1000);
    }
  }
}

void loop()
{
  if (!nchuk.update()) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    _data.c = nchuk.buttonC();
    _data.z = nchuk.buttonZ();
    _data.x = nchuk.joyX();
    _data.y = nchuk.joyY();
    _data.r = nchuk.rollAngle() * 100;
    _data.p = nchuk.pitchAngle() * 100;

    bool result = false;
    for (int i = 0; i < 3; i++) {
      if (_radio.send(DESTINATION_RADIO_ID, &_data, sizeof(_data))) {
        result = true;
        break;
      }
    }

    if (result)
    {
      _data.counter++;
    }
  }
}
