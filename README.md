# Arduino_Midi
This is an Arduino Project that could read and playing more than one note simultaneously on buzzers (You can hook up whatever you want, like Tesla Coils, stepper motors, floppy drives or whatever can play frequencies).

# Hardware requirements: 
- Any arduino board (Uno and mega are recommended)
- Another arduino mega (If you are using the ToneLib)
- 6 Buzzers
- Resistors (Reduce the volume)

# About how to use:
- [Arduino midi library](https://github.com/FortySevenEffects/arduino_midi_library) Make sure you have it installed on arduino IDE
- [Tone.lib](https://github.com/bhagman/Tone) Install the Tone Library for multiple buzzers.
 
 Notice that this program is using the I2C communication (For some reasons the tone library conflict with the Midi libaray). 
 
 # Wiring 
 - Wiring up your buzzers on pin 2,3,4,5,6,7 on Mega board.
 - Connecting an I2C bridge between your Uno and Mega.

# For MIDI Communication
- Flash [HIDUINO](https://github.com/ddiakopoulos/hiduino) or [mocuLUFA](https://github.com/kuwatay/mocolufa) on to the board. 
- Or useing DIN socket.
- Or even using [loopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html) and [hairlessMIDI](http://projectgus.github.io/hairless-midiserial/) to make a Serial to MIDI communication.
There are fully descriptions on some other websites.
