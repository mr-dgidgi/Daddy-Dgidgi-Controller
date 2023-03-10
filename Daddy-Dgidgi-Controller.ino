// If Arduino Uno / Mega
// #include <MIDI.h>
#include <USB-MIDI.h>
#include "Mux.h"
#include "Controller.h"

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
byte NUMBER_MIDI_BUTTONS = 3;
//---How many potentiometers are connected ?--
byte NUMBER_MIDI_POTS = 16;
//---How many MidiEncoder are connected ?--
byte NUMBER_MIDI_ENCODERS = 0;


//*******************************************************************
//***ANY MULTIPLEXERS? **********************************************
//*******************************************************************
//Mux <name>(Pin(<pin>, INPUT, PinType::<Analog/Digital>), Pinset(<adresspin1>,<adresspin2>,<adresspin3>,<adresspin4>));


//Mux mux1(Pin(7, INPUT, PinType::Digital), Pinset(8, 9, 10, 11)); //Digital multiplexer on Arduino pin 7
//Mux MUX2(Pin(A0, INPUT, PinType::Analog), Pinset(8, 9, 10, 11)); //Analog multiplexer on Arduino analog pin A0
Mux mux1(Pin(A0, INPUT, PinType::Analog), Pinset(2,3,4,5));
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

// MidiPot MPO1(0, 16, 1, MUX2);
// MidiPot MPO2(1, 17, 1, MUX2);
// MidiPot MPO3(2, 18, 1, MUX2);
// MidiPot MPO4(3, 19, 1, MUX2);
// MidiPot MPO5(4, 20, 1, MUX2);
// MidiPot MPO6(5, 21, 1, MUX2);
MidiPot MPO1(0, 16, 1, &mux1);
MidiPot MPO2(1, 17, 1, &mux1);
MidiPot MPO3(2, 18, 1, &mux1);
MidiPot MPO4(3, 19, 1, &mux1);
MidiPot MPO5(4, 20, 1, &mux1);
MidiPot MPO6(5, 21, 1, &mux1);
MidiPot MPO7(6, 22, 1, &mux1);
MidiPot MPO8(7, 23, 1, &mux1);
MidiPot MPO9(8, 24, 1, &mux1);
MidiPot MPO10(9, 25, 1, &mux1);
MidiPot MPO11(10, 26, 1, &mux1);
MidiPot MPO12(11, 27, 1, &mux1);
MidiPot MPO13(12, 28, 1, &mux1);
MidiPot MPO14(13, 29, 1, &mux1);
MidiPot MPO15(14, 30, 1, &mux1);
MidiPot MPO16(15, 31, 1, &mux1);
//*******************************************************************
//Add all pots used to array below like this->	MidiPot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6.....};
MidiPot *POTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6, &MPO7, &MPO8, &MPO9, &MPO10, &MPO11, &MPO12, &MPO13, &MPO14, &MPO15, &MPO16};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED MIDI BUTTONS*******************************
//MidiButton(byte pin, byte command, bool toggle, byte channel, byte _debounce);

//MidiButton BU1(6, 80, true, 1, 10 ); //MidiButton on pin 6 will send CC change on commande 80 channel 1
//MidiButton BU2(7, 81, true, 1, 10 );
//MidiButton BU3(8, 82, false, 1, 10 );
MidiButton BU1(7, 80, true, 1, 254 );
MidiButton BU2(6, 81, true, 1, 254 );
MidiButton BU3(8, 82, true, 1, 254 );

//***DEFINE MIDI BUTTONS CONNECTED TO MULTIPLEXER*************************
//MidiButton(byte pin, byte command, byte channel, byte _debounce, Mux *mux);

//MidiButton MBU1(0, 80, 1, 5, mux1);
//MidiButton MBU2(1, 81, 1, 5, mux1);
//MidiButton MBU3(2, 82, 1, 5, mux1);
//MidiButton MBU4(3, 83, 1, 5, mux1);
//*******************************************************************
//Add all buttons used to array below like this->	MidiButton *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
MidiButton *BUTTONS[] {&BU1, &BU2, &BU3};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED MIDI ENCODERS************************
//MidiEncoder(byte pinA, byte pinB, byte command, byte channel);

//MidiEncoder EN1(A0, 1, 1, 1);
//MidiEncoder EN2(A1, 1, 23, 2);
//MidiEncoder EN3(A2, 1, 24, 3);
//MidiEncoder EN4(A3, 1, 25, 4);
//MidiEncoder EN5(A4, 1, 26, 5);
//MidiEncoder EN6(A5, 1, 27, 6);

//***DEFINE MIDI ENCODERS CONNECTED TO MULTIPLEXER*************************
//MidiEncoder(byte pinA, byte pinB, byte command, byte channel, Mux *mux);

//MidiEncoder MEN1(5, 6, 70, 1, 5, mux1);
//MidiEncoder MEN2(7, 8, 71, 1, 5, mux1);
//MidiEncoder MEN3(9, 10, 72, 1, 5, mux1);
//MidiEncoder MEN4(11, 12, 73, 1, 5, mux1);
//*******************************************************************
//Add all MidiEncoders used to array below like this->	MidiEncoder *MidiEncoders[] {&EN1, &EN2, &EN3, &EN4, &EN5, &EN6};
MidiEncoder *ENCODERS[] {};
//*******************************************************************

//****************************************************************************************
//************ SERVICE *******************************************************************
//****************************************************************************************


//***DEFINE LED FOR MIDI INPUT***************************************
byte LED_START = 10;
byte LED_TEMPO = 11;
byte LED_BU2 = 12;
byte LED_BU3 = 9;

//*******************************************************************

//***DEFINE CLOCK MESSAGE COUNT***************************************
byte CLOCK_COUNT = 1;

//*******************************************************************


void setup() {
	pinMode(LED_START, OUTPUT);
	pinMode(LED_TEMPO, OUTPUT);
	pinMode(LED_BU2, OUTPUT);
	pinMode(LED_BU3, OUTPUT);
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
	if (NUMBER_MIDI_BUTTONS != 0) updateMidiButtons();
	if (NUMBER_MIDI_POTS != 0) updateMidiPots();
	if (NUMBER_MIDI_ENCODERS != 0) updateMidiEncoders();
	MIDI.read();
	
}


//*****************************************************************
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
void updateMidiPots() {
	for (int i = 0; i < NUMBER_MIDI_POTS; i = i + 1) {
		POTS[i]->getValue();
	  if (POTS[i]->haschanged == true) {
		  MIDI.sendControlChange(POTS[i]->MidiCommand, POTS[i]->MidiValue, POTS[i]->MidiChannel);
		}
	}
}

//***********************************************************************
void updateMidiEncoders() {
	for (int i = 0; i < NUMBER_MIDI_ENCODERS; i = i + 1) {
		ENCODERS[i]->getValue();
		if (ENCODERS[i]->haschanged == true) {
			MIDI.sendControlChange(ENCODERS[i]->MidiCommand, ENCODERS[i]->MidiValue, ENCODERS[i]->MidiChannel);
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
