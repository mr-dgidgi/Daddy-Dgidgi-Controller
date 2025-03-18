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
  const Pin SigDigi = 6;
  // Pin for Mux Analog Signal
  const Pin SigAnal = A1;

  //Declare Mux Selector
  auto MuxSelector = Selector(M0,M1,M2,M3);
  // Digital Mux
  auto MuxDigi = Multiplexer(SigDigi,MuxSelector);
  // Analog Mux
  auto MuxAnal = Multiplexer(SigAnal,MuxSelector);
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

const auto Button1 = Button(MuxDigi, 0);
const auto Button2 = Button(MuxDigi, 1);
const auto Button3 = Button(MuxDigi, 2);

Button ListButtonMux[] {Button1,Button2,Button3};
const int NUMBUTTONMUX = 3;
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

const auto Key1 = Key(MuxDigi, 3);
const auto Key2 = Key(MuxDigi, 4);
const auto Key3 = Key(MuxDigi, 5);

Key ListKeyMux[] {Key1,Key2,Key3};
const int NUMKEYMUX = 3;
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

const auto Pot1 = Potentiometer(MuxAnal, 0, 1);
const auto Pot2 = Potentiometer(MuxAnal, 1, 1);
const auto Pot3 = Potentiometer(MuxAnal, 2, 1);

Potentiometer ListPotMux[] {Pot1,Pot2,Pot3};
const int NUMPOTMUX = 3;
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

//***DEFINE EACH CHANNEL VOLUME*************************
//
byte VOLCHANNEL1 = 0;
byte VOLCHANNEL2 = 0;
byte VOLCHANNEL3 = 0;
byte VOLCHANNEL4 = 0;
byte VOLCHANNEL5 = 0;
byte VOLCHANNEL6 = 0;
byte VOLCHANNEL7 = 0;
byte VOLCHANNEL8 = 0;
byte VOLCHANNEL9 = 0;
byte VOLCHANNEL10 = 0;
byte VOLCHANNEL11 = 0;
byte VOLCHANNEL12 = 0;
byte VOLCHANNEL13 = 0;
byte VOLCHANNEL14 = 0;
byte VOLCHANNEL15 = 0;
byte VOLCHANNEL16 = 0;
byte LISTVOLCHANNEL[] {VOLCHANNEL1,VOLCHANNEL2,VOLCHANNEL3,VOLCHANNEL4,VOLCHANNEL5,VOLCHANNEL6,VOLCHANNEL7,VOLCHANNEL8,VOLCHANNEL9,VOLCHANNEL10,VOLCHANNEL11,VOLCHANNEL12,VOLCHANNEL13,VOLCHANNEL14,VOLCHANNEL15,VOLCHANNEL16};
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
  // Check Controls
  for (int i = 0; i < NUMBUTTONMUX; i++){
    buttonprint(ListButtonMux[i]);
  }
  for (int i = 0; i < NUMBUTTON; i++){
    buttonprint(ListButton[i]);
  }
  for (int i = 0; i < NUMKEYMUX; i++){
    keyprint(ListKeyMux[i]);
    midisendkey(ListKeyMux[i],i,OCTAVE,127,1);
  }
  for (int i = 0; i < NUMKEY; i++){
    midisendkey(ListKeyMux[i],i,OCTAVE,127,1);
  }
  for (int i = 0; i < NUMPOTMUX; i++){
    potprint(ListPotMux[i]);
  }
  for (int i = 0; i < NUMPOT; i++){
    potprint(ListPot[i]);
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

void midisendkey(Key MyKey, int MyNote, byte MyOctave, int MyVelocity, byte MyChannel) {
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

void midisendcc(Potentiometer MyPot, int MyCC, byte MyChannel) {
  // check the button status
  if (MyPot.check() == Potentiometer::Event::Changed){
    MIDI.sendControlChange(MyCC, MyPot.read(), MyChannel);
  }
}

void setvolume(Potentiometer MyPot, byte MyChannel){
  // check the button status
  if (MyPot.check() == Potentiometer::Event::Changed){
    LISTVOLCHANNEL[MyChannel+1] = MyPot.read();
  }
}

void updatevolume(Potentiometer MyPot, byte MyChannel){
  // check the button status
  if (MyPot.check() == Potentiometer::Event::Changed){
    if (MyPot.read() > LISTVOLCHANNEL[MyChannel+1] - 10 || MyPot.read() < LISTVOLCHANNEL[MyChannel+1] + 10) {
      LISTVOLCHANNEL[MyChannel+1] = MyPot.read();
      MIDI.sendControlChange(7, MyPot.read(), MyChannel);
    }
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
