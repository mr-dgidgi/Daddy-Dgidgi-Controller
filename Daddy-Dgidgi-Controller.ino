// If Arduino Uno / Mega
// #include <MIDI.h>
#include <USB-MIDI.h>
#include "Mux.h"
#include "Controller.h"
#include <CommonBusEncoders.h>

using namespace admux;
// If Arduino Uno / Mega
// MIDI_CREATE_DEFAULT_INSTANCE();
USBMIDI_CREATE_DEFAULT_INSTANCE();
/*********************************************************************
 DADDY DGIDGI MIDI CONTROLLER
 
 Midi controller using buttons, ptentiometers and rotary encoders
 
 It is a complete rework based on "Notes And Volts" work and using
 the last versions of Midi and Mux libraries.
 
 This project use Arduino Leonardo to be natively recognized ad midi
 device by computers.

*********************************************************************/


//*******************************************************************
//***SET THE NUMBER OF CONTROLS USED*********************************
//*******************************************************************
//---How many buttons are connected ?---------
byte NUMBER_MIDI_BUTTONS = 0;
//---How many potentiometers are connected ?--
byte NUMBER_MIDI_POTS = 0;

//---How many buttons are connected ?---------
byte NUMBER_SERVICE_BUTTONS = 0;
//---How many potentiometers are connected ?--
byte NUMBER_SERVICE_POTS = 0;
//---How many Service Encoder are connected ?--
const byte NUMBER_SERVICE_ENCODERS = 1;

//***DEFINE MIDI CHANNEL FOR TOGGLE**********************************
// not needed if we don't toggle the midichannel with buttons
//default midi channel
byte ChannelButtonDefault = 1;
// midi channel when Button2 is not activated
byte ChannelButton2 = 1;
// midi channel when Button2 is activated
byte ChannelButton2Alt = 2;
//*******************************************************************

//*******************************************************************
//***BUS ENCODER*****************************************************
//*******************************************************************
//CommonBusEncoders <name>(<pin1>, <pin2>, <pin3>, <EncoderNumber>);

//CommonBusEncoders encoders(4, 5, 6, NUMBER_SERVICE_ENCODERS);

//*******************************************************************
//***ANY MULTIPLEXERS? **********************************************
//*******************************************************************
//Mux <name>(Pin(<pin>, INPUT, PinType::<Analog/Digital>), Pinset(<adresspin1>,<adresspin2>,<adresspin3>,<adresspin4>));
//Mux mux1(Pin(7, INPUT, PinType::Digital), Pinset(8, 9, 10, 11)); //Digital multiplexer on Arduino pin 7
//Mux MUX2(Pin(A0, INPUT, PinType::Analog), Pinset(8, 9, 10, 11)); //Analog multiplexer on Arduino analog pin A0

//Mux mux1(Pin(A0, INPUT, PinType::Analog), Pinset(2,3,4,5));
//*******************************************************************

//****************************************************************************************
//************ MIDI **********************************************************************
//****************************************************************************************

//***DEFINE DIRECTLY CONNECTED MIDI POTENTIOMETERS************************
//MidiPot(byte pin, byte command, byte channel)

//MidiPot PO1(A0, 1, 1);
//MidiPot PO2(A1, 23, 2);
//MidiPot PO3(A2, 24, 3);
//MidiPot PO4(A3, 25, 4);
//MidiPot PO5(A4, 26, 5);
//MidiPot PO6(A5, 27, 6);

//***DEFINE MIDI POTENTIOMETERS CONNECTED TO MULTIPLEXER*******************
//MidiPot(byte pin, byte command, byte channel, Mux *mux);

// MidiPot MPO1(0, 16, 1, &mux1);
// MidiPot MPO2(1, 17, 1, &mux1);
// MidiPot MPO3(2, 18, 1, &mux1);
// MidiPot MPO4(3, 19, 1, &mux1);
// MidiPot MPO5(4, 20, 1, &mux1);
// MidiPot MPO6(5, 21, 1, &mux1);
// MidiPot MPO7(6, 22, 1, &mux1);
// MidiPot MPO8(7, 23, 1, &mux1);
// MidiPot MPO9(8, 24, 1, &mux1);
// MidiPot MPO10(9, 25, 1, &mux1);
// MidiPot MPO11(10, 26, 1, &mux1);
// MidiPot MPO12(11, 27, 1, &mux1);
// MidiPot MPO13(12, 28, 1, &mux1);
// MidiPot MPO14(13, 29, 1, &mux1);
// MidiPot MPO15(14, 30, 1, &mux1);
// MidiPot MPO16(15, 31, 1, &mux1);
//*******************************************************************
//Add all pots used to array below like this->	MidiPot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6.....};
MidiPot *POTS[] {};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED MIDI BUTTONS*******************************
//MidiButton(byte pin, byte command, bool toggle, byte channel, byte _debounce);

//MidiButton BU1(6, 80, true, 1, 10 ); //MidiButton on pin 6 will send CC change on commande 80 channel 1
//MidiButton BU2(7, 81, true, 1, 10 );
//MidiButton BU3(8, 82, false, 1, 10 );
//MidiButton BU1(7, 80, true, 1, 254 );

//***DEFINE MIDI BUTTONS CONNECTED TO MULTIPLEXER*************************
//MidiButton(byte pin, byte command, byte channel, byte _debounce, Mux *mux);

//MidiButton MBU1(0, 80, 1, 5, mux1);
//MidiButton MBU2(1, 81, 1, 5, mux1);
//MidiButton MBU3(2, 82, 1, 5, mux1);
//MidiButton MBU4(3, 83, 1, 5, mux1);
//*******************************************************************
//Add all buttons used to array below like this->	MidiButton *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
MidiButton *BUTTONS[] {};
//*******************************************************************


//****************************************************************************************
//************ SERVICE *******************************************************************
//****************************************************************************************

//***DEFINE DIRECTLY CONNECTED SERVICE POTENTIOMETERS************************
//ServicePot(byte pin);

//ServicePot PO1(A0);
//ServicePot PO2(A1);
//ServicePot PO3(A2);
//ServicePot PO4(A3);
//ServicePot PO5(A4);
//ServicePot PO6(A5);

//***DEFINE SERVICE POTENTIOMETERS CONNECTED TO MULTIPLEXER*******************
//ServicePot(byte pin, Mux *mux);

// ServicePot MPO1(0,MUX2);
// ServicePot MPO2(1,MUX2);
// ServicePot MPO3(2,MUX2);
// ServicePot MPO4(3,MUX2);
// ServicePot MPO5(4,MUX2);
// ServicePot MPO6(5,MUX2);
//*******************************************************************
//Add all pots used to array below like this->	ServicePot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6.....};
ServicePot *SERVICEPOTS[] {};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED SERVICE BUTTONS*******************************
//ServiceButton(byte pin, bool toggle, byte debounce);

// ServiceButton BU2(6, true, 5 );
// ServiceButton BU3(8, true, 5 );
// ServiceButton BU2(6, true, 5 );
// ServiceButton BU3(8, false, 5 );

//***DEFINE SERVICE BUTTONS CONNECTED TO MULTIPLEXER*************************
//ServiceButton(byte pin, bool toggle, byte debounce, Mux *mux);

//ServiceButton MBU1(0, false, 5, mux1);
//ServiceButton MBU2(1, false, 5, mux1);
//ServiceButton MBU3(2, false, 5, mux1);
//ServiceButton MBU4(3, false, 5, mux1);
//*******************************************************************
//Add all buttons used to array below like this->	ServiceButton *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
ServiceButton *SERVICEBUTTONS[] {};
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


void setup() {
	pinMode(LED_START, OUTPUT);
	pinMode(LED_TEMPO, OUTPUT);
	pinMode(LED_BU2, OUTPUT);
	pinMode(LED_BU3, OUTPUT);


//*******************************************************************
//Encoders creation
  // encoders.setDebounce(16);
  // encoders.resetChronoAfter(1000); 
  // encoders.addEncoder(int <encoder ID>,int <encoder step> (2/4, default 4),int <encoder ground pin>,int <button mode> (we only use 0),int <encoder index>, int <button index>);
  // encoders.addEncoder(1,4,3,0,1,101);
//*******************************************************************


//*******************************************************************
// Midi setting
	MIDI.setHandleStart(handleStart);
	MIDI.setHandleStop(handleStop);
	MIDI.setHandleContinue(handleContinue);
	MIDI.setHandleClock(handleClock);
  
	MIDI.begin(1);
// If Arduino Uno / Mega
//  Serial.begin(38400);
	//disable midi throuput
	MIDI.turnThruOff();
}

void loop() {

  // toggle channel for all the controller or just a specific pot
  // serviceButtonToggleAlterChannelAll(BU2, ChannelButtonDefault, ChannelButton2, ChannelButton2Alt);
  // serviceButtonToggleAlterChannel(BU3, ChannelButtonDefault, ChannelButton2, ChannelButton2Alt, MPO3);

  // Encoder interrupt loop
  byte index = encoders.readAll();
  if (index != 0) {
    EncoderSendNote(index);
  }

  // Update all entry  
	if (NUMBER_MIDI_BUTTONS != 0) updateMidiButtons();
	if (NUMBER_MIDI_POTS != 0) updateMidiPots();

  // Update LED status
  ServiceButtonToggleLed(BU2, LED_BU2);

  // Midi read message
	MIDI.read();
	
}


//****************************************************************************************
//************ FUNCTIONS *****************************************************************
//****************************************************************************************

//*****************************************************************
// Update the value off all midi buttons and send the new value
void updateMidiButtons() {

	// Cycle through MidiButton array
	for (int i = 0; i < NUMBER_MIDI_BUTTONS; i = i + 1) {
    BUTTONS[i]->getValue();
		// Send the new value if the button state has changed
		if (BUTTONS[i]->haschanged == true){
			MIDI.sendControlChange(BUTTONS[i]->MidiCommand, BUTTONS[i]->MidiValue, BUTTONS[i]->MidiChannel);
		}
	}
}

//***********************************************************************
// Update the value off all midi potentiometers and send the new value
void updateMidiPots() {
	for (int i = 0; i < 16; i = i + 1) {
		POTS[i]->getValue();
	  if (POTS[i]->haschanged == true) {
		  MIDI.sendControlChange(POTS[i]->MidiCommand, POTS[i]->MidiValue, POTS[i]->MidiChannel);
		}
	}
}

//***********************************************************************
//Fonction to alter pot channel
void serviceButtonToggleAlterChannel( ServiceButton &serviceButton, byte &channelDefault, byte channelDeactivated, byte channelActivated, MidiPot &midiPot) {

  serviceButton.getValue();
  // Send the new value if the button state has changed
  if (serviceButton.haschanged == true && serviceButton.serviceValue == 127){
    channelDefault = 2;
		midiPot.newValue(midiPot.MidiCommand, midiPot.MidiValue, channelDefault);
  }
  else if (serviceButton.haschanged == true && serviceButton.serviceValue == 0){
    channelDefault = 1;
		midiPot.newValue(midiPot.MidiCommand, midiPot.MidiValue, channelDefault);
  }
}

//***********************************************************************
//Fonction to alter all pots channel
void serviceButtonToggleAlterChannelAll( ServiceButton &serviceButton, byte &channelDefault, byte channelDeactivated, byte channelActivated) {

  serviceButton.getValue();
  // Send the new value if the button state has changed
  if (serviceButton.haschanged == true && serviceButton.serviceValue == 127){
    channelDefault = 2;
    for (int i = 0; i < NUMBER_MIDI_POTS; i = i + 1) {
		  POTS[i]->newValue(POTS[i]->MidiCommand, POTS[i]->MidiValue, channelDefault);
    }
  }
  else if (serviceButton.haschanged == true && serviceButton.serviceValue == 0){
    channelDefault = 1;
    for (int i = 0; i < NUMBER_MIDI_POTS; i = i + 1) {
		  POTS[i]->newValue(POTS[i]->MidiCommand, POTS[i]->MidiValue, channelDefault);
    }
  }
}


//***********************************************************************
void handleStart(){
	//turn on LED_START when Start message is received
	digitalWrite(LED_START, HIGH);
}
//***********************************************************************
void handleStop(){
	//turn off LED_START when Stop message is received
	digitalWrite(LED_START, LOW);
	//turn off LED_TEMPO and reset CLOCK_COUNT
	digitalWrite(LED_TEMPO, LOW);
	CLOCK_COUNT = 1;	
}
//***********************************************************************
void handleContinue(){
	//turn on LED_START when Continue message is received
	digitalWrite(LED_START, HIGH);
}
//***********************************************************************
void handleClock() {
	//MIDI send 24 clock message per quarter note (beat)
	//to blink the led we alternate at each beat so every 24 clock message
	if (CLOCK_COUNT == 1){
		digitalWrite(LED_TEMPO, HIGH);
		CLOCK_COUNT = CLOCK_COUNT +1;
		}
	else if (CLOCK_COUNT == 25) {
		digitalWrite(LED_TEMPO, LOW);
		CLOCK_COUNT = CLOCK_COUNT +1;
		}
	else if (CLOCK_COUNT <48){
		CLOCK_COUNT = CLOCK_COUNT +1;
		}
	else {
		CLOCK_COUNT = 1;
		}
}
//***********************************************************************
// Function to turn on light if toggle button is activated
void ServiceButtonToggleLed(ServiceButton &serviceButton, byte LED){
  if (serviceButton.serviceValue == 127){
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}
void ServiceButtonToggleLed(MidiButton &midiButton, byte LED){
  if (midiButton.MidiValue == 127){
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}


//***********************************************************************
// Send note ON when encoder is used
// usefull to control Zynthian

void EncoderSendNote(byte code){
  switch (code) {
    //********************************
    //Zynthian UI nav
    case 1: {
      // SELECT_DOWN
      MIDI.sendNoteOn(53, 127, 16);
      MIDI.sendNoteOff(53, 0, 16);
      break;
    }
    case 2: {
      // SELECT_UP
      MIDI.sendNoteOn(52, 127, 16);
      MIDI.sendNoteOff(52, 0, 16);
      break;
    }
    case 101: {
      // SWITCH_SELECT_SHORT
      MIDI.sendNoteOn(65, 127, 16);
      MIDI.sendNoteOff(60, 0, 16);
      break;
    }
    case 3: {
      // BACK_DOWN
      MIDI.sendNoteOn(55, 127, 16);
      MIDI.sendNoteOff(55, 0, 16);
      break;
    }
    case 4: {
      // BACK_UP
      MIDI.sendNoteOn(54, 127, 16);
      MIDI.sendNoteOff(54, 0, 16);
      break;
    }
    case 103: {
      // SWITCH_BACK_SHORT
      MIDI.sendNoteOn(64, 127, 16);
      MIDI.sendNoteOff(64, 0, 16);
      break;
    }
        case 5: {
      // LAYER_DOWN
      MIDI.sendNoteOn(57, 127, 16);
      MIDI.sendNoteOff(57, 0, 16);
      break;
    }
    case 6: {
      // LAYER_UP
      MIDI.sendNoteOn(56, 127, 16);
      MIDI.sendNoteOff(56, 0, 16);
      break;
    }
    case 105: {
      // SWITCH_LAYER_SHORT
      MIDI.sendNoteOn(60, 127, 16);
      MIDI.sendNoteOff(60, 0, 16);
      break;
    }
    case 7: {
      // LEARN_DOWN
      MIDI.sendNoteOn(59, 127, 16);
      MIDI.sendNoteOff(59, 0, 16);
      break;
    }
    case 8: {
      // LEARN_UP
      MIDI.sendNoteOn(58, 127, 16);
      MIDI.sendNoteOff(58, 0, 16);
      break;
    }
    case 107: {
      // SWITCH_SNAPSHOT_SHORT
      MIDI.sendNoteOn(71, 127, 16);
      MIDI.sendNoteOff(71, 0, 16);
      break;
    }
    //********************************
  }
}
