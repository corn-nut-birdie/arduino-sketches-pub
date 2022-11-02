# Yet another RC car's sketches.

The controller utilizes a Wii Nunchuk for user input.
Tried pwm driven but dropped, because of the caused interference.

__modules:__
- 2 radio modules of NRF24L01 for RC communication;
- a Wii Nunchuk as input of controlling on the RC controller side, which connected to a simple _wiichuk_ adapter shield that converts the plug of the Wii Nunchuk to 2.54mm gpio pins.
- a small motor driver module, _Mini L298N_.
- 4 small 3-6V TT 130 motors.
- two 18650 batteries, with a parallel battery holder, on the small car side; 
- two DC voltage regulators to output 3.3V and optional 3~6V to the Raspberry Pi Pico board and the driver module.
- two AA batteries, with a parallel battery holder, for the controller side, that directly connect to the Vin pin and a Gnd pin of the ESP32.
- 4 wheel 2 layer small car chassis kits, that has 4 gear motors.
- an __ESP32__ board for the controller side; an __Raspberry Pi PICO__ board for the car side. They could be replaced with 2 __Arduino UNO__ boards.
- etc.

__software environment:__
- Arduino IDE

__arduino libraries:__
- NRFLite
- NintendoExtensionCtrl

Some other components may be mounted, such as WS2812 RGB LED, a tri color led module, an 1.3" OLED display, an active buzzer. More complicated control involved the gyro of the Wii Nunchuk could be applied.
