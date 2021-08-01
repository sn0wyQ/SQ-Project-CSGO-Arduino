[![CI Checks](https://github.com/sn0wyQ/SQ-Project-CSGO-Arduino/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/sn0wyQ/SQ-Project-CSGO-Arduino/actions/workflows/ci.yml)
# SQ Project CSGO Arduino Edition
External CS:GO hack for Arduino written using C++ and WinAPI.

# Special thanks to
- [hazedumper](https://github.com/frk1/hazedumper) for hazedumper.
- [Shock Byte](https://www.youtube.com/channel/UCEXBku-TaXm2UQfEhZrLL3Q) for [this](https://www.youtube.com/watch?v=qEoM8Of3A9U) video.

# Shopping list
- [Arduino Leonardo](https://store.arduino.cc/arduino-leonardo-with-headers) or it's copies (for example [Iskra Neo](https://amperka.ru/product/iskra-neo))
- [LCD 1602 with Keypad Shield](https://protosupplies.com/product/lcd1602-16x2-blue-lcd-shield-with-keypad/)

**Note that links above are NEITHER ads NOR my recommendations, they are left only with demonstration purposes**

# Getting started
After purchasing/trading/getting as a present/~~stealing~~ (last one is highly NOT recomended) needed parts follow steps below:

## Step 1
Connect your LCD Display to your Arduino.

**Note that you may be required to change pin numbers to fit [LiquidCrystal()](https://www.arduino.cc/en/Reference/LiquidCrystalConstructor()). So if needed change their definitions in *Arduino/Helpers/definitions.h (lines 5-10)*.**

## Step 2
Connect your Arduino board to your PC.

## Step 3
Build CMake projects located in folders *Arduino* and *PC*.

**Note that building project located *Arduino* also uploads it to your board, so you may be required to change COM port in *Arduino/CMakeLists.txt (line 44)* to COM port where your Arduino Bootloader will be during build process.**

## Step 4
Run Counter-Strike: Global Offensive.

## Step 5
Run *.exe* file that you got after building CMake project located in *PC* folder.

## Step 6
Setup keys following instructions in application.

## Step 7 (Optional)
Adjust settings using your Keypad Shield.

# Short video
Click on image below to watch it on YouTube

[![Video](http://img.youtube.com/vi/03OUp3qoWKg/0.jpg)](http://www.youtube.com/watch?v=03OUp3qoWKg)


# Commiting your own code
If you wish to support project by coding some new features you are more than welcome to do it, but you need to follow [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

# Future of project
I plan to add some more features, for example:
- Aim and Trigger kill delays
- Recoil-Control System
- Enemies info on LCD (position, HP, weapon)

# Denial of responsibility
- I'm not liable for any bans from any anti-cheats (including, but not limited to: VAC, SMAC, Faceit AC).
- I'm not liable for anyone using this software in competitive games.
- If using it in competitive games be ready to face anger of teammates and opponents and also **note that you should NOT use it**, but I somewhy don't care about it.
