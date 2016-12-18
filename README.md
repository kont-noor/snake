# Snake
A snake demo using [maple](http://www.leaflabs.com/maple) and [pcd8544](https://cdn-learn.adafruit.com/downloads/pdf/nokia-5110-3310-monochrome-lcd.pdf)

## Setup
* Setup your maple board or any similar stm32 board.
* (Optional) flash bootloader if needed
* Install libmaple: `git clone https://github.com/leaflabs/libmaple.git` (is no longer supported. need to remake it to use stm32duino)
* Clone this repo: `git clone https://github.com/kont-noor/snake.git`
* `cd snake`
* Install it to your board: `make install`
* Reset your board
* Connect to your board by serial port and handle snake using Vim navigation keys (`h`,`j`,`k`,`l`)
