# Steering wheel control adapter using a microcontroller

An example project to learn how to translate the car's factory steering wheel control signal to an aftermarket head unit using a small microcontroller

This example uses a small Adafruit Trinket (5V), so I needed to add a shift register to have enough digital out pin.

The code and the circuit is currently prepared to be used in a Suzuki SX4 and to control a Pioneer head unit, but by changing the resistance values in the code to match your car and changing the resistors in the circuit to match your head unit, it's easy to use this with other cars and head units.
