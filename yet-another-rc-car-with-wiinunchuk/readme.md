Yet another RC car's sketches.

With both the sketches of the remote controller and the RC car, that utilize a Wii Nunchuk for input of controlling.
Tried pwm driven but dropped, because of the caused interference.

modules:
- 2 radio modules of NRF24L01 for RC communication;
- a Wii Nunchuk as input of controlling on the RC controller side, which connected to a simple _wiichuk_ adapter shield that converts the plug of the Wii Nunchuk to 2.54mm gpio pins.
- a small motor driver module.
- 4 small 3-6V TT 130 motors.
- two 18650 batteries, with a battery capsule, for the small car side; two step down DC voltage regulators to output 3.3V and optional 3~6V for the Raspberry Pi Pico board and the driver module.
- two AA batteries, with a battery capsule, for the controller side, that directly connect to the Vin pin of the ESP32.
- the basic car suite.
- an ESP32 board on the controller side; an Raspberry PICO board on the car side. But they can be replaced with 2 arduino uno boards.
- etc.

software environment:
- Arduino IDE

arduino libraries:
- NRFLite
- NintendoExtensionCtrl

The RC controller is on a ESP32 board; and the RC car is on a Raspberry PI Pico board, powered by 2 of 18650 Li batteries, through a regulator module, the Li batteries power the 4 motors at the same time.

Some other components may be mounted, such as WS2812 RGB LED, tri color led module, 1.3" OLED display, active buzzer. More complicated control involved the gyro of the Wii Nunchuk could be applied.
