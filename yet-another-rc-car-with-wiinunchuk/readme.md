Yet another RC car's sketches. 

Both the sketches of the remote controller, and the RC car, that utilizes the joystick on the Wii Nunchuk for driving and ..pivot steering.
Tried pwm driven but dropped, when it produced interference.

modules: 
- two NRF24L01 of radio module for remote control;
- a Wii Nunchuk as the ..__controller__ on the RC controller, connected to a simple _wiichuk_ adapter shield that converts the plug of the Wii Nunchuk to 2.54mm gpio pins.
- a motor drive module.
- 4 small motors
- two 18650 batteries.
- etc.

libraries:
- NRFLite
- NintendoExtensionCtrl

The RC controller is on a ESP32 board; and the RC car is on a Raspberry PI Pico board, powered by 2 of 18650 Li batteries, through a regulator module, the Li batteries power the 4 motors at the same time.
