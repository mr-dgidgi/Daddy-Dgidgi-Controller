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
byte NUMBER_BUTTONS = 3;
//---How many potentiometers are connected ?--
byte NUMBER_POTS = 16;
//---How many Encoder are connected ?--
byte NUMBER_ENCODERS = 0;


//*******************************************************************
//***ANY MULTIPLEXERS? **********************************************
//*******************************************************************
//Mux <name>(Pin(<pin>, INPUT, PinType::<Analog/Digital>), Pinset(<adresspin1>,<adresspin2>,<adresspin3>,<adresspin4>));


//Mux mux1(Pin(7, INPUT, PinType::Digital), Pinset(8, 9, 10, 11)); //Digital multiplexer on Arduino pin 7
//Mux MUX2(Pin(A0, INPUT, PinType::Analog), Pinset(8, 9, 10, 11)); //Analog multiplexer on Arduino analog pin A0
Mux mux1(Pin(A0, INPUT, PinType::Analog), Pinset(2,3,4,5));
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED POTENTIOMETERS************************
//Pot(byte pin, byte command, byte channel)

//Pot PO1(A0, 1, 1);
//Pot PO2(A1, 23, 2);
//Pot PO3(A2, 24, 3);
//Pot PO4(A3, 25, 4);
//Pot PO5(A4, 26, 5);
//Pot PO6(A5, 27, 6);

//***DEFINE POTENTIOMETERS CONNECTED TO MULTIPLEXER*******************
//Pot(byte pin, byte command, byte channel, Mux *mux);

// Pot MPO1(0, 16, 1, MUX2);
// Pot MPO2(1, 17, 1, MUX2);
// Pot MPO3(2, 18, 1, MUX2);
// Pot MPO4(3, 19, 1, MUX2);
// Pot MPO5(4, 20, 1, MUX2);
// Pot MPO6(5, 21, 1, MUX2);
Pot MPO1(0, 16, 1, &mux1);
Pot MPO2(1, 17, 1, &mux1);
Pot MPO3(2, 18, 1, &mux1);
Pot MPO4(3, 19, 1, &mux1);
Pot MPO5(4, 20, 1, &mux1);
Pot MPO6(5, 21, 1, &mux1);
Pot MPO7(6, 22, 1, &mux1);
Pot MPO8(7, 23, 1, &mux1);
Pot MPO9(8, 24, 1, &mux1);
Pot MPO10(9, 25, 1, &mux1);
Pot MPO11(10, 26, 1, &mux1);
Pot MPO12(11, 27, 1, &mux1);
Pot MPO13(12, 28, 1, &mux1);
Pot MPO14(13, 29, 1, &mux1);
Pot MPO15(14, 30, 1, &mux1);
Pot MPO16(15, 31, 1, &mux1);
//*******************************************************************
//Add all pots used to array below like this->	Pot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6.....};
Pot *POTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6, &MPO7, &MPO8, &MPO9, &MPO10, &MPO11, &MPO12, &MPO13, &MPO14, &MPO15, &MPO16};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
//Button(byte pin, byte command, byte channel, byte _debounce);

//Button BU1(6, 80, 1, 10 ); //Button on pin 6 will send CC change on commande 80 channel 1
//Button BU2(7, 81, 1, 10 );
//Button BU3(8, 82, 1, 10 );
Button BU1(7, 80, 1, 254 );
Button BU2(6, 81, 1, 254 );
Button BU3(8, 82, 1, 254 );

//***DEFINE BUTTONS CONNECTED TO MULTIPLEXER*************************
//Button(byte pin, byte command, byte channel, byte _debounce, Mux *mux);

//Button MBU1(0, 80, 1, 5, mux1);
//Button MBU2(1, 81, 1, 5, mux1);
//Button MBU3(2, 82, 1, 5, mux1);
//Button MBU4(3, 83, 1, 5, mux1);
//*******************************************************************
//Add all buttons used to array below like this->	Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
Button *BUTTONS[] {&BU1, &BU2, &BU3};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED ENCODERS************************
//Encoder(byte pinA, byte pinB, byte command, byte channel);

//Encoder EN1(A0, 1, 1, 1);
//Encoder EN2(A1, 1, 23, 2);
//Encoder EN3(A2, 1, 24, 3);
//Encoder EN4(A3, 1, 25, 4);
//Encoder EN5(A4, 1, 26, 5);
//Encoder EN6(A5, 1, 27, 6);

//***DEFINE ENCODERS CONNECTED TO MULTIPLEXER*************************
//Encoder(byte pinA, byte pinB, byte command, byte channel, Mux *mux);

//Encoder MEN1(5, 6, 70, 1, 5, mux1);
//Encoder MEN2(7, 8, 71, 1, 5, mux1);
//Encoder MEN3(9, 10, 72, 1, 5, mux1);
//Encoder MEN4(11, 12, 73, 1, 5, mux1);
//*******************************************************************
//Add all Encoders used to array below like this->	Encoder *Encoders[] {&EN1, &EN2, &EN3, &EN4, &EN5, &EN6};
Encoder *ENCODERS[] {};
//*******************************************************************


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
	if (NUMBER_BUTTONS != 0) updateButtons();
	if (NUMBER_POTS != 0) updatePots();
	MIDI.read();
	
}


//*****************************************************************
void updateButtons() {

	// Cycle through Button array
	for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    BUTTONS[i]->getValue();
		// Send the new value if the button state has changed
		if (BUTTONS[i]->haschanged == true){
			MIDI.sendControlChange(BUTTONS[i]->MidiCommand, BUTTONS[i]->MidiValue, BUTTONS[i]->MidiChannel);
		}
	}
}

//***********************************************************************
void updatePots() {
	for (int i = 0; i < NUMBER_POTS; i = i + 1) {
		POTS[i]->getValue();
	  if (POTS[i]->haschanged == true) {
		  MIDI.sendControlChange(POTS[i]->MidiCommand, POTS[i]->MidiValue, POTS[i]->MidiChannel);
		}
	}
}

//***********************************************************************
void updateEncoders() {
	for (int i = 0; i < NUMBER_POTS; i = i + 1) {
		bool HasChanged = ENCODERS[i]->getValue();
		if (HasChanged == true) {
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
