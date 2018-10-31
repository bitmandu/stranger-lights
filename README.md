stranger-lights
===============

This is my attempt to recreate the
[Christmas light, message wall from Stranger Things][stranger-things-tweet].
This is a popular project on the Interwebs, but is usually done using
an Arduino.

This project features:

- A bare bones ATmega328 AVR (no Arduino ecosystem)
- Command-line scripts to send tweets to the AVR over serial UART
- Random flashes — to warn you when the Demogorgon is nearby

This [video shows stranger-lights in action][youtube].

Getting Started
---------------

An avr-gcc Makefile is provided to compile the flash the source code.

    $ make
    $ make flash

Serial messages are read over the serial port and displayed.

### Displaying Messages with upsidedown.py

The script `bin/upsidedown.py` sends serial messages to display.

Without any command-line arguments, upsidedown.py sends a random
message like "run."

    $ ./upsidedown.py

To display your own message, just add it to the command-line.

    $ ./upsidedown.py stranger lights

The special message `~` is used to flash the LEDs — warning that the
Demogorgon is nearby.

    $ ./upsidedown.py ~

### Displaying Tweets

The script `bin/poll` uses [Twurl][twurl] to periodically retrieve and
display tweets containing a hashtag.

    $ ./poll

Documentation
-------------

Step-by-step instructions on setting up the hardware and software are
available in the [documentation][docs].

Help / Issues
-------------

Please report all bugs and feature requests using the
[Issue Tracker][issues].

License
-------

[MIT](LICENSE) ***except*** for
[Danny Havenith's ws2811 library][ws2811] which is licensed under the
[Boost Software License 1.0][boost].


[boost]: https://github.com/DannyHavenith/ws2811/blob/master/LICENSE_1_0.txt
[docs]: https://bitmandu.com/stranger-lights/latest/index.html
[issues]: https://github.com/bitmandu/stranger-lights/issues
[stranger-things-tweet]: https://twitter.com/stranger_things/status/898307224979742720
[twurl]: https://github.com/twitter/twurl
[ws2811]: https://github.com/DannyHavenith/ws2811
[youtube]: https://www.youtube.com/watch?v=xbL81dse8vs
