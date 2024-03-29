# Quantum Painter display only

When I first started looking into Quantum Painter, I tried to find a simple example on how to get it up and running.

I'm not a complete hardware n00b, but while the documentation for Quantum Painter is well written and extensive, I still
found it hard to put all the pieces together. Understanding the rp2040 pin configuration, the SPI protocol, how Quantum
Painter worked, and so on and then stitching it all together was not obvious to me.

After getting some help in the QMK discord, I managed to get my first display working - A two inch 320x240 LCD using the
ST7789 driver. After getting the basics up and running, I decided to create a simple display only keyboard that can be
used to test different LCD's and get a basic idea what is needed to get Quantum Painter up and running.

Also, I wanted a configuration the would be widely compatible with almost _any_ Elite Pi/RP2040 based keyboard, making
it possible to add a color LCD using Quantum Painter to an existing keyboard.

So here it is - **The Guide** I wish I would have found when I started looking into Quantum Painter.

Let's start by going over some nomenclature.

* QMK - The keyboard firmware
* Quantum Painter - The feature in QMK that makes it possible to easily show graphics on different LCD's.
* Controller - The hardware that QMK runs on. Only RP2040 based controllers can use Quantum Painter. Pro Micro
  controllers won't work.
* SPI - The protocol used to communicate between the controller and the display.

One of the things I found it hard to wrap my head around was which pins that could/had to be used on the controller. I
wanted to use the "Extra" pins on the bottom of the controller (12,13,14,15 and 16) since these are rarely used and
would make it _a lot_ easier to add a display to more or less any keyboard. While possible to use other pin
configurations on the rp2040, the configuration we will use on this keyboard will utilize the extra pins.

Elite Pi compatible controllers (I exclusively use the Liatris from SplitKB, but any Elite Pi compatible controller
should work) have two SPI channels, SPID0 and SPID1. These two different channels have a bunch of different possible
configurations, but only SPID1 can be used on the extra pins. 
