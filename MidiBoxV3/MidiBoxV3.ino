#include <MIDI.h>
#include <Controlino.h>

using namespace controlino;

MIDI_CREATE_DEFAULT_INSTANCE();
/*********************************************************************
 MIDIBOX
 
 Version : 3
 Based on Daddy Dgidgi Midi Controller
 
 Midi controller using buttons and potentiometers. It is a small demo
 of Daddy Dgidgi Midi Controller capability

*********************************************************************/


//*******************************************************************
//***ANY MULTIPLEXERS? **********************************************
//*******************************************************************

  // Pin for Mux matrix
  const Pin M0 = 2;
  const Pin M1 = 3;
  const Pin M2 = 4;
  const Pin M3 = 5;
  // Pin for Mux Analog Signal
  const Pin SigAnal = A1;

  //Declare Mux Selector
  auto MuxSelector = Selector(M0,M1,M2,M3);
  // Analog Mux
  auto MuxAnalog = Multiplexer(SigAnal,MuxSelector);
//*******************************************************************

//****************************************************************************************
//************ INPUTS ********************************************************************
//****************************************************************************************

//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
//

const auto Button1 = Button(6);
const auto Button2 = Button(7);
const auto Button3 = Button(8);
Button ListButton[] {Button1,Button2,Button3};
const int NUMBUTTON = 3;

//*******************************************************************

//***DEFINE POTS CONNECTED TO MULTIPLEXER*************************
//

const auto Pot1 = Potentiometer(MuxAnalog, 0, 1);
const auto Pot2 = Potentiometer(MuxAnalog, 1, 1);
const auto Pot3 = Potentiometer(MuxAnalog, 2, 1);
const auto Pot4 = Potentiometer(MuxAnalog, 3, 1);
const auto Pot5 = Potentiometer(MuxAnalog, 4, 1);
const auto Pot6 = Potentiometer(MuxAnalog, 5, 1);
const auto Pot7 = Potentiometer(MuxAnalog, 6, 1);
const auto Pot8 = Potentiometer(MuxAnalog, 7, 1);
const auto Pot9 = Potentiometer(MuxAnalog, 8, 1);
const auto Pot10 = Potentiometer(MuxAnalog, 9, 1);
const auto Pot11 = Potentiometer(MuxAnalog, 10, 1);
const auto Pot12 = Potentiometer(MuxAnalog, 11, 1);
const auto Pot13 = Potentiometer(MuxAnalog, 12, 1);
const auto Pot14 = Potentiometer(MuxAnalog, 13, 1);
const auto Pot15 = Potentiometer(MuxAnalog, 14, 1);
const auto Pot16 = Potentiometer(MuxAnalog, 15, 1);

Potentiometer ListPotMux[] {Pot1,Pot2,Pot3,Pot4,Pot5,Pot6,Pot7,Pot8,Pot9,Pot10,Pot11,Pot12,Pot13,Pot14,Pot15,Pot16};
const int NUMPOTMUX = 16;
//*******************************************************************

//***DEFINE CHANNEL VAR*************************
//
byte CHANNEL = 1;
//*******************************************************************

//***DEFINE CC + CHANNEL*************************
//
int LISTCONTROL[NUMPOTMUX][2] = {
  {74,1},
  {71,1},
  {74,2},
  {71,2},
  {74,3},
  {71,3},
  {74,4},
  {71,4},
  {74,5},
  {71,5},
  {74,6},
  {71,6},
  {74,7},
  {71,7},
  {74,8},
  {71,8}
};

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

//*******************************************************************
// Midi setting
	MIDI.setHandleStart(handleStart);
	MIDI.setHandleStop(handleStop);
	MIDI.setHandleContinue(handleContinue);
	MIDI.setHandleClock(handleClock);
	MIDI.begin(MIDI_CHANNEL_OMNI);

// If Arduino Uno / Mega
//  Serial.begin(38400);
	//disable midi throuput
	MIDI.turnThruOff();
  Serial.begin(9600);

  // Led init
  pinMode(LED_START, OUTPUT);
  pinMode(LED_TEMPO, OUTPUT);
  pinMode(LED_BU2, OUTPUT);
  pinMode(LED_BU3, OUTPUT);
}

void loop() {

  //*************************************
  // Check Controls
  for (int i = 0; i < NUMBUTTON; i++){
    buttonprint(ListButton[i]);
  }
  for (int i = 0; i < NUMPOTMUX; i++){
    midisendcc(ListPotMux[i],LISTCONTROL[i][0],LISTCONTROL[i][1]);
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

void midisendcc(Potentiometer MyPot, int MyCC, byte MyChannel) {
  // check the button status
  if (MyPot.check() == Potentiometer::Event::Changed){
    MIDI.sendControlChange(MyCC, MyPot.read(), MyChannel);
  }
}

void handleStart(){
  //turn on LED_START when Start message is received
  digitalWrite(LED_START, HIGH);
}

void handleStop(){
  //turn off LED_START when Stop message is received
  digitalWrite(LED_START, LOW);
  //turn off LED_TEMPO and reset CLOCK_COUNT
  digitalWrite(LED_TEMPO, LOW);
  CLOCK_COUNT = 1;  
}

void handleContinue(){
  //turn on LED_START when Continue message is received
  digitalWrite(LED_START, HIGH);
}

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
