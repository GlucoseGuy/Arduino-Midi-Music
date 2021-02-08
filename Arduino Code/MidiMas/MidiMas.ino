//Author:GlucoseGuy
//Main function: Playing more than one note simultaneously from ANY Midi file
//Add velocity function if U like
#include <Wire.h>
#include <MIDI.h>
#define slaveAddress 0x08
int device = 0;
int deviceoff = 0;
//no note means 0
byte devicenote[] = {0, 0, 0, 0, 0, 0, 0}; //sepcific note for each devices (I have six for example)
MIDI_CREATE_DEFAULT_INSTANCE(); //use default MIDI settings
void setup()
{
  Wire.begin();
  MIDI.begin(MIDI_CHANNEL_OMNI); //listen to all MIDI channels
  MIDI.setHandleNoteOn(handleNoteOn); //execute function when note on message is recieved
  MIDI.setHandleNoteOff(handleNoteOff); //execute function when note off message is recieved
}
void loop()
{
  MIDI.read(); //read MIDI messages
}
void handleNoteOn(byte channel, byte pitch, byte velocity) //MIDI Note ON Command
{
    for (int i = 0; i < 6; i++) { //scan through 6 devices
      if (devicenote[i] == 0) { //make sure only add new devices when the note is not zero
        device = i; //get the device value for future use.
        devicenote[device] = pitch;//get the value and write device
        break;//exit this loop
      }
    }
    // so it make sense, currently we have the device specific note, device for the device number, inside the array for the device note.
    Wire.beginTransmission(slaveAddress);
    byte dataArray[3] = {channel,  devicenote[device], device};//sent it rignt away
    for (int i = 0; i < 3; i++) //write to the slave, change it to 3 for devices
    {
      Wire.write(dataArray[i]);
    }
    Wire.endTransmission();
}

void handleNoteOff(byte channel, byte pitch, byte velocity) //MIDI Note OFF Command
{
    for (int i = 0; i < 6; i++) {
      if (devicenote[i] != 0) {//turn the note off if it's not zero
        deviceoff=i;
        devicenote[deviceoff] = 0;//write 0 to devices
        break;//exit the loop
      }
    }
    Wire.beginTransmission(slaveAddress);
    byte dataArray[3] = {channel, devicenote[deviceoff], deviceoff};
    for (int i = 0; i < 3; i++)//the function fot data transmission
    {
      Wire.write(dataArray[i]);
    }
    Wire.endTransmission();
}
