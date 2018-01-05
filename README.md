This is the source code for my IR adapter

The project is written for an Arduino Uno.

It takes infrared signals from my Bang & Olfusen remote control (Beoremote One) through a B&O IR eye.
The B&O ir remotes uses a carrier frequency at 455 KHz and manchester encoding.
I used this library for that: https://github.com/christianlykke9/Beomote.

It is then translated into infrared signals for my Samsung tv.
This remote used a carrier frequency on 38 KHz.

Also, rf, 455MHz is sent through 

