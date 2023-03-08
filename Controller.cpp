
#include "Controller.h"

//****************************************************************************************
//Button (Pin Number, Command, Note Number, Channel)
Button::Button(byte pin, byte command, byte channel, byte _debounce)
{
	_debounce = 5;
	_pin = pin;
  _hasMux = false;
	pinMode(_pin, INPUT_PULLUP);
	MidiCommand = command;
	MidiChannel = channel;
	updatePin();
	_oldValue = _value;
	_time = 0;
	haschanged = false;
}

Button::Button(byte pin, byte command, byte channel, byte _debounce, Mux *mux)
{
	_debounce = 5;
	_pin = pin;
	*_mux = *mux;
	_hasMux = true;
	MidiCommand = command;
	MidiChannel = channel;
	updatePin();
	_oldValue = _value;
	_time = 0;
	haschanged = false;
}

void Button::updatePin()
{
	if ( _hasMux == true ){
		_value = _mux->read(_pin);
	}
	else {
		_value = digitalRead(_pin);
	}
}

void Button::getValue()
{
	if (millis() > _debounce + _time){
		updatePin();
		_time = millis();
		if (_value == 1 && _value != _oldValue){
			MidiValue = 0;
			haschanged = true;
			_oldValue = _value;
		}
		else if (_value == 0 && _value != _oldValue){
			MidiValue = 127;
			haschanged = true;
			_oldValue = _value;			
		}
		else if (_value == _oldValue){
			haschanged = false;
			_oldValue = _value; 
		}
	}
	else {
		haschanged = false;
	}
}


void Button::newValue(byte command, byte value, byte channel)
{
	MidiValue = value;
	MidiCommand = command;
	MidiChannel = channel;
}

//********************************************************************
Pot::Pot(byte pin, byte command, byte channel)
{
	_pin = pin;
	_hasMux = false;
	updatePin();
	_oldMidiValue = MidiValue;
	MidiCommand = command;
	MidiChannel = channel;
}

Pot::Pot(byte pin, byte command, byte channel, Mux *mux)
{
	_pin = pin;
	_mux = mux;
	_hasMux = true;
	updatePin();
	_oldMidiValue = MidiValue;
	MidiCommand = command;
	MidiChannel = channel;
}

void Pot::updatePin(){
	if ( _hasMux == true ){
		_value = _mux->read(_pin);

	}
	else {
		_value = analogRead(_pin); 
	}
	// division to convert 10bits to 8bits (bytes)
	MidiValue = _value / 8;
}

void Pot::getValue()
{
	updatePin();
	if (MidiValue  > _oldMidiValue + 2 || MidiValue  < _oldMidiValue - 2) {
		_oldMidiValue = MidiValue;
		haschanged = true;
	}
	else {
		haschanged = false;
	}
}

void Pot::newValue(byte command, byte value, byte channel) {
	MidiCommand = command;
	_value = value;
	MidiChannel = channel;
}

//********************************************************************
Encoder::Encoder(byte pinA, byte pinB, byte command, byte channel)
{
	_pinA = pinA;
	_pinB = pinB;
	updatePin();
	_oldStatePinA = _statePinA;
	_oldStatePinB = _statePinB;
	MidiValue = 0;
	MidiCommand = command;
	MidiChannel = channel;
}

Encoder::Encoder(byte muxpinA, byte muxpinB, byte command, byte channel, Mux *mux)
{
	_pinA = muxpinA;
	_pinB = muxpinB;
	*_mux = *mux;
	_hasMux = true;
	updatePin();
	_oldStatePinA = _statePinA;
	_oldStatePinB = _statePinB;
	MidiValue = 0;
	MidiCommand = command;
	MidiChannel = channel;
}

void Encoder::updatePin()
{
	if ( _hasMux == true ){
		_statePinA = _mux->read(_pinA);
		_statePinB = _mux->read(_pinB);
	}
	else {
		_statePinA = digitalRead(_pinA);
		_statePinB = digitalRead(_pinB);
	}
}

// bool Encoder::getValue()
// {
//	 updatePin()
// 	if ( _statePinA != _oldStatePinA ){
// 		if ( _statePinB != _oldStatePinB ){
//			 if ( MidiValue < 127 ){
// 				MidiValue++;
//			 }
// 		}
// 		else{
//			 if ( MidiValue > 0 ){
// 				MidiValue--;
//			 }
//		 }
// 	}
// 	_oldStatePinA = _statePinA;
// 	_oldStatePinB = _statePinB;

// 	return MidiValue;
// }

void Encoder::newValue(byte command, byte value, byte channel) {
	MidiCommand = command;
	MidiValue = value;
	MidiChannel = channel;
}
