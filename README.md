# SonarScannerV2

This code is for the video https://youtu.be/iTtid9Hw2sM
The board is not publically available but you can use any Esp32 S2
the pins for the ADC data inputs are 1 to 8. 9 and 10 are used later to read back CS and clk since RMT bypasses the gpio matrix...
CS and clk output pins are defined in the code.

This is just a few of the tests I performed durign the development but might be useful to see how to read many GPIOs at once and how to use RMT.
The timings of the RMT in high clock speeds are behaving strange. It's more of a trial and error. If you miss the ight timing it might just add a few clock cycles.
A lot to experiment there.

# Support

Github sponsorship: https://github.com/sponsors/bitluni

Paypal: https://paypal.me/bitluni
