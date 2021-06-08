//Author:GlucoseGuy
//Main function: Playing more than one note simultaneously from ANY Midi file
//Add velocity function if U like
#include <Wire.h>
#include <MIDI.h>
#define slaveAddress 0x08
int device;
int devicechannel;
int deviceoff;
//no note means 0
int devicenote[7][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}; //sepcific note for each devices (I have six for example), keep the values here
//6 channels and 6 devices, 36 in total

//
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
{ //sometimes when the note in different channel appears, this guy will send them into the same channel. Which is not good

  //only ONE note at a time
  for (int a = 1; a < 7; a++) {
    //if(devicechannel[a] ==
    //chan = channel;
    //comparing the cannel value to the previous or the other ones before
    for (int i = 0; i < 6; i++) { //scan through 6 devices, output:0,1,2,3,4,5 SHOULD ON THE SAME CHANNEL
      if (devicenote[a][i] == 0) { //make sure only add new devices when the current note is zero
        device = i; //get the specific device value that appears to be 0
        devicechannel = a;
        devicenote[devicechannel][device] = pitch;//get the current value and write to the device
        break;//exit this loop
      }
    }
  }
  //same channel, executing the one above
  //DIFFERENT, go checking the same stuff on other channels and adding values
  //so we should have two values: Channel name and devicenote

  Wire.beginTransmission(slaveAddress);//send ONLY when the board find the correct device
  byte dataArray[3] = {channel,  devicenote[device], device};//sent it rignt away, channel is always the same stuff
  for (int i = 0; i < 3; i++) //write to the slave, change it to 3 for devices
  {
    Wire.write(dataArray[i]);
  }
  Wire.endTransmission();
}

void handleNoteOff(byte channel, byte pitch, byte velocity) //MIDI Note OFF Command
{
  for (int a = 1; a < 7; a++) {
    for (int i = 0; i < 6; i++) {
      if (devicenote[a][i] != 0) {//turn the note off if it's not zero
        deviceoff = i; //get the specific device value that appears to be 0
        devicechannel = a;
        devicenote[devicechannel][deviceoff] = 0;//set to zero
        break;//exit this loop  
      }
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
