// If Arduino Uno / Mega
// #include <MIDI.h>
#include <USB-MIDI.h>
#include <Controlino.h>
#include "AudioSlice.h"

using namespace controlino;

// If Arduino Uno / Mega
// MIDI_CREATE_DEFAULT_INSTANCE();
USBMIDI_CREATE_DEFAULT_INSTANCE();
/*********************************************************************
 DADDY DGIDGI MIDI CONTROLLER
 
 Midi controller using buttons, potentiometers and rotary encoders
 
 This project use Arduino Leonardo to be natively recognized ad midi
 device by computers.

*********************************************************************/


//*******************************************************************
//***ANY MULTIPLEXERS? **********************************************
//*******************************************************************

  // Pin for Mux matrix
  const Pin M0 = 2;
  const Pin M1 = 3;
  const Pin M2 = 4;
  const Pin M3 = 5;
  // Pin for Mux Digital Signal
  const Pin SigDigi1 = 6;
  const Pin SigDigi2 = 7;
  // Pin for Mux Analog Signal
  const Pin SigAnal1 = A1;
  const Pin SigAnal2 = A2;

  //Declare Mux Selector
  auto MuxSelector = Selector(M0,M1,M2,M3);
  // Digital Mux
  auto MuxDigi1 = Multiplexer(SigDigi1,MuxSelector);
  auto MuxDigi2 = Multiplexer(SigDigi2,MuxSelector);
  // Analog Mux
  auto MuxAnal1 = Multiplexer(SigAnal1,MuxSelector);
  auto MuxAnal2 = Multiplexer(SigAnal2,MuxSelector);
//*******************************************************************

//****************************************************************************************
//************ INPUTS ********************************************************************
//****************************************************************************************

//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
//

// const auto Button1 = Button(0);
// const auto Button2 = Button(1);
// const auto Button3 = Button(2);
Button ListButton[] {};
const int NUMBUTTON = 0;

//***DEFINE  BUTTONS CONNECTED TO MULTIPLEXER*************************
//

const auto Button1 = Button(MuxDigi1, 0);
const auto Button2 = Button(MuxDigi1, 1);
const auto Button3 = Button(MuxDigi1, 2);
const auto Button4 = Button(MuxDigi1, 3);
const auto Button5 = Button(MuxDigi1, 4);
const auto Button6 = Button(MuxDigi1, 5);
const auto Button7 = Button(MuxDigi1, 6);
const auto Button8 = Button(MuxDigi1, 7);

Button ListButtonMux[] {Button1,Button2,Button3,Button4,Button5,Button6,Button7,Button8};
const int NUMBUTTONMUX = 8;
//*******************************************************************

//***DEFINE DIRECTLY CONNECTED KEYS*******************************
//

// const auto Key1 = Key(0);
// const auto Key2 = Key(1);
// const auto Key3 = Key(2);
Key ListKey[] {};
const int NUMKEY = 0;

//***DEFINE  KEYS CONNECTED TO MULTIPLEXER*************************
//

// const auto Key1 = Key(MuxDigi, 3);
// const auto Key2 = Key(MuxDigi, 4);
// const auto Key3 = Key(MuxDigi, 5);

Key ListKeyMux[] {};
const int NUMKEYMUX = 0;
//*******************************************************************

//***DEFINE DIRECTLY CONNECTED POTS*******************************
//

// const auto Pot1 = Potentiometer(0);
// const auto Pot2 = Potentiometer(1);
// const auto Pot3 = Potentiometer(2);
Potentiometer ListPot[] {};
const int NUMPOT = 0;

//***DEFINE POTS CONNECTED TO MULTIPLEXER*************************
//

const auto Pot1 = Potentiometer(MuxAnal1, 0, 1);
const auto Pot2 = Potentiometer(MuxAnal1, 1, 1);
const auto Pot3 = Potentiometer(MuxAnal1, 2, 1);
const auto Pot4 = Potentiometer(MuxAnal1, 3, 1);
const auto Pot5 = Potentiometer(MuxAnal1, 4, 1);
const auto Pot6 = Potentiometer(MuxAnal1, 5, 1);
const auto Pot7 = Potentiometer(MuxAnal1, 6, 1);
const auto Pot8 = Potentiometer(MuxAnal1, 7, 1);

Potentiometer ListPotMux[] {Pot1,Pot2,Pot3,Pot4,Pot5,Pot6,Pot7,Pot8};
const int NUMPOTMUX = 8;
//*******************************************************************

//***DEFINE REFERENCE OCTAVE*************************
//
byte OCTAVE = 5;
//*******************************************************************

//***DEFINE CHANNEL VAR*************************
//
byte CHANNEL = 1;
//*******************************************************************

//***DEFINE TEMPO RELATED VARIABLES*************************
//
byte BPM;
int BPMINTERVAL = 60000 / (BPM * 24);
unsigned long MILLISPREV = 0;
//*******************************************************************

//***DEFINE EACH AUDIO SLICE ****************************************
//
AudioSlice Slice1 = AudioSlice(&Button1,&Button2,&Button3,&Button4,&Pot1,&Pot2,&Pot3,&Pot4,1);
AudioSlice Slice2 = AudioSlice(&Button5,&Button6,&Button7,&Button8,&Pot5,&Pot6,&Pot7,&Pot8,2);
AudioSlice LISTAUDIOSLICE[] {Slice1,Slice2};
uint8_t NUMAUDIOSLICE = 2;

//*******************************************************************

//***DEFINE LED FOR MIDI INPUT***************************************
// useful if you want visual return
byte LED_START = 10;
byte LED_TEMPO = 11;
byte LED_BU2 = 12;
byte LED_BU3 = 9;

//*******************************************************************

//***DEFINE CLOCK MESSAGE COUNT**************************************
//needed for TEMPO LED
byte CLOCK_COUNT = 1;

//*******************************************************************

//***DEFINE THE MENU ID *********************************************
//
uint8_t MENU = 1;

//*******************************************************************


void setup() {

//*******************************************************************
// Midi setting
	// MIDI.setHandleStart(handleStart);
	// MIDI.setHandleStop(handleStop);
	// MIDI.setHandleContinue(handleContinue);
	// MIDI.setHandleClock(handleClock);
  
	 MIDI.begin(MIDI_CHANNEL_OMNI);
// If Arduino Uno / Mega
//  Serial.begin(38400);
	//disable midi throuput
	MIDI.turnThruOff();
  Serial.begin(9600);
}

void loop() {

  //*************************************
  // Clock
  unsigned long MillisCurrent = millis();
  if (MillisCurrent - MILLISPREV >= BPMINTERVAL) {
      MILLISPREV = MillisCurrent; // Update the last value
      MIDI.sendClock();
  }  
  //*************************************

  //*************************************
  // Check each slice
  for ( uint8_t i = 0; i < NUMAUDIOSLICE; i++){
    // Cutoff potentiometer
    midisendcc(LISTAUDIOSLICE[i].PotCutOff,74,&LISTAUDIOSLICE[i].CutoffVal,LISTAUDIOSLICE[i].Channel);
    // Resonance potentiometer
    midisendcc(LISTAUDIOSLICE[i].PotResonance,71,&LISTAUDIOSLICE[i].ResonanceVal,LISTAUDIOSLICE[i].Channel);
    // LFO potentiometer
    midisendcc(LISTAUDIOSLICE[i].PotLFO,16,&LISTAUDIOSLICE[i].LfoVal,LISTAUDIOSLICE[i].Channel);
    // Volume potentiometer
    midisendcc(LISTAUDIOSLICE[i].PotVolume,7,&LISTAUDIOSLICE[i].VolumeVal,LISTAUDIOSLICE[i].Channel);
    // Mute button
    buttonmute(LISTAUDIOSLICE[i].ButMute,&LISTAUDIOSLICE[i].MuteVal,LISTAUDIOSLICE[i].Channel);
    // Select button
    buttonselect(LISTAUDIOSLICE[i].ButSelect,&LISTAUDIOSLICE[i].SelectVal,LISTAUDIOSLICE[i].Channel);
    // Filter button
    buttonfilter(LISTAUDIOSLICE[i].ButFilterType,&LISTAUDIOSLICE[i].FilterType,LISTAUDIOSLICE[i].Channel);
    // LFO button
    buttonlfo(LISTAUDIOSLICE[i].ButLFORouting,LISTAUDIOSLICE[i].Channel);
  }

  //*************************************

	MIDI.read();
}


//****************************************************************************************
//************ FUNCTIONS *****************************************************************
//****************************************************************************************

void buttonprint(Button MyButton) {
  // check the button status
  const auto event = MyButton.check();
  switch(event) {
    case Button::Event::Down: {
      Serial.println("Down");
    }
    case Button::Event::Up: {
      Serial.println("Up");
    }
    case Button::Event::Click: {
      Serial.println("Click");
    }
    case Button::Event::Press: {
      Serial.println("Press");
    }
    case Button::Event::ClickClick: {
      Serial.println("ClickClick");
    }
    case Button::Event::ClickPress: {
      Serial.println("ClickPress");
    }
  }
}

void buttonalt(Button MyButton, bool MyAlt){
  const auto event = MyButton.check();
  if (event == Button::Event::Click){
    if (MyAlt){
      MyAlt = false;
    }
    else {
      MyAlt = true;
    }
  }
}

void buttonmute(Button* MyButton, bool* MuteStatus, uint8_t MyChannel){
  const auto event = MyButton->check();
  if (event == Button::Event::Click){
    if (*MuteStatus == true){
      byte SysexMute[] {0xf0,0x41,0x10,0x00,0x00,0x1b,0x12,0x38,0x01,0x00,0x00,0x4a,0xf7};
      SysexMute[8] = MyChannel;
      *MuteStatus = false;
      MIDI.sendSysEx(13,*SysexMute, false);
    }
    else {
      byte SysexUnmute[] {0xf0,0x41,0x10,0x00,0x00,0x1b,0x12,0x38,0x01,0x00,0x01,0x49,0xf7};
      SysexUnmute[8] = MyChannel;
      *MuteStatus = true;
      MIDI.sendSysEx(13,*SysexUnmute, false);
    }
  }
}

void buttonselect(Button* MyButton, bool* SelectStatus, uint8_t MyChannel){
  const auto event = MyButton->check();
  if (event == Button::Event::Click){
    if (*SelectStatus == true){
      *SelectStatus = false;
    }
    else {
      *SelectStatus = true;
    }
  }
}

void buttonfilter(Button* MyButton, uint8_t* MyFilterType, uint8_t MyChannel){
  const auto event = MyButton->check();
  if (event == Button::Event::Click){
    if (MyFilterType == 4){
      *MyFilterType = 0;
      //affiche temporairement le filtre dans le menu lcd
    }
    else {
      (*MyFilterType)++;
    }
  }
  else if (event == Button::Event::Press){
    //display menu on LCD
  }
}

void buttonlfo(Button* MyButton, uint8_t MyChannel){
  const auto event = MyButton->check();
  if (event == Button::Event::Click){
    //affiche le menu lfo dans sur le LCD
  }
}

void keyprint(Key MyKey) {
  // check the button status
  const auto event = MyKey.check();
  switch(event) {
    case Key::Event::Down: {
      Serial.println("Down");
    }
    case Key::Event::Up: {
      Serial.println("Up");
    }
    case Key::Event::Hold: {
      Serial.println("Hold");
    }
  }
}

void midisendkey(Key MyKey, int MyNote, byte MyOctave, int MyVelocity, uint8_t MyChannel) {
  // check the button status
  const auto event = MyKey.check();
  switch(event) {
    case Key::Event::Down: {
      // C1 Midi number is 24, there is 12 notes per octave so we multiply 12 with MyOctave to move the value
      // we also add 11 because the first key is 1 so 1+11=12 and 12*MyOctave=12*1=12 12+12=24 so C1
      MIDI.sendNoteOn(12 * MyOctave + 11 + MyNote, MyVelocity, MyChannel);
    }
    case Key::Event::Up: {
      MIDI.sendNoteOff(12 * MyOctave + 11 + MyNote, MyVelocity, MyChannel);
    }
  }
}

void potprint(Potentiometer MyPot) {
  // check the button status
  if (MyPot.check() == Potentiometer::Event::Changed){
    Serial.println(MyPot.read());
  }
}

void midisendcc(Potentiometer* MyPot, uint8_t MyCC, uint8_t* MyValue, uint8_t MyChannel) {
  // check the button status
  if (MyPot->check() == Potentiometer::Event::Changed){
    *MyValue = MyPot->read();
    MIDI.sendControlChange(MyCC, *MyValue, MyChannel);
  }
}

void setoctave(bool MyModifier){
  if (MyModifier == true){
    if (OCTAVE <8){
      OCTAVE = OCTAVE++;
    } 
    return OCTAVE;
  }
  else if (MyModifier == false) {
    if (OCTAVE >1){
      OCTAVE = OCTAVE--;
    }
    return OCTAVE;
  }
}

void setchannel(bool MyModifier){
  if (MyModifier == true){
    if (CHANNEL <16){
      CHANNEL = CHANNEL++;
    } 
    return CHANNEL;
  }
  else if (MyModifier == false) {
    if (CHANNEL >1){
      CHANNEL = CHANNEL--;
    }
    return CHANNEL;
  }
}

void setbpm(int MyValue){
  if (BPM > 50 && BPM < 300){
    BPM = BPM + MyValue;
    BPMINTERVAL = 60000 / (BPM * 24);
  }
}

void menumove(bool Increment,byte MyValue){
  if (Increment == true){
    MENU = MENU + MyValue;
  }
  else {
    MENU = MyValue;
  }
}
