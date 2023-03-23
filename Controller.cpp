#include "Controller.h"
//****************************************************************************************
//************ MIDI **********************************************************************
//****************************************************************************************


//****************************************************************************************
//MidiButton (Pin Number, Command, Note Number, Channel)
MidiButton::MidiButton(byte pin, byte command, bool toggle, byte channel, byte debounce)
{
	_debounce = debounce;
	_pin = pin;
  _toggle = toggle;
  _hasMux = false;
	pinMode(_pin, INPUT_PULLUP);
	MidiCommand = command;
	MidiChannel = channel;
	updatePin();
	_oldValue = _value;
	_time = 0;
	haschanged = false;
  MidiValue = 0;
}

MidiButton::MidiButton(byte pin, byte command, bool toggle, byte channel, byte debounce, Mux *mux)
{
	_debounce = debounce;
	_pin = pin;
  _toggle = toggle;
	*_mux = *mux;
	_hasMux = true;
	MidiCommand = command;
	MidiChannel = channel;
	updatePin();
	_oldValue = _value;
	_time = 0;
	haschanged = false;
  MidiValue = 0;
}

void MidiButton::updatePin()
{
	if ( _hasMux == true ){
		_value = _mux->read(_pin);
	}
	else {
		_value = digitalRead(_pin);
	}
}

void MidiButton::getValue()
{
	if (millis() > _debounce + _time){
		updatePin();
		_time = millis();
    if (_toggle == false){
      if (_value == LOW && _value != _oldValue){
        MidiValue = 127;
        haschanged = true;
        _oldValue = _value;
      }
      else if (_value == HIGH && _value != _oldValue){
        MidiValue = 0;
        haschanged = true;
        _oldValue = _value;			
      }
      else if (_value == _oldValue){
        haschanged = false;
        _oldValue = _value; 
      }
    }
    else if (_toggle == true){
      if (_value == LOW){
        if (_value != _oldValue && pressed == false){
          haschanged = true;
          if (MidiValue == 0){
            MidiValue = 127;
          }
          else {
            MidiValue = 0;
          }
        }
        else {
          haschanged = false;
        } 
        pressed = true;       
      }
      if (_value == HIGH){
        pressed = false;
        haschanged = false;
      }
    }
	}
	else {
		haschanged = false;
	}
}


void MidiButton::newValue(byte command, byte value, byte channel)
{
	MidiValue = value;
	MidiCommand = command;
	MidiChannel = channel;
}

//********************************************************************
MidiPot::MidiPot(byte pin, byte command, byte channel)
{
	_pin = pin;
	_hasMux = false;
	updatePin();
	_oldMidiValue = MidiValue;
	MidiCommand = command;
	MidiChannel = channel;
}

MidiPot::MidiPot(byte pin, byte command, byte channel, Mux *mux)
{
	_pin = pin;
	_mux = mux;
	_hasMux = true;
	updatePin();
	_oldMidiValue = MidiValue;
	MidiCommand = command;
	MidiChannel = channel;
}

void MidiPot::updatePin(){
	if ( _hasMux == true ){
		_value = _mux->read(_pin);

	}
	else {
		_value = analogRead(_pin); 
	}
	// division to convert 10bits to 8bits (bytes)
	MidiValue = _value / 8;
}

void MidiPot::getValue()
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

void MidiPot::newValue(byte command, byte value, byte channel) {
	MidiCommand = command;
	MidiValue = value;
	MidiChannel = channel;
}

//********************************************************************
MidiEncoder::MidiEncoder(byte pinA, byte pinB, byte command, byte channel)
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

MidiEncoder::MidiEncoder(byte muxpinA, byte muxpinB, byte command, byte channel, Mux *mux)
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

void MidiEncoder::updatePin()
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

void MidiEncoder::getValue()
{
	updatePin();
	if ( _statePinA != _oldStatePinA ){
		if ( _statePinB != _oldStatePinB ){
			if ( MidiValue < 127 ){
				MidiValue++;
			 }
		}
		else{
			if ( MidiValue > 0 ){
				MidiValue--;
			 }
		 }
	}
	_oldStatePinA = _statePinA;
	_oldStatePinB = _statePinB;
}

void MidiEncoder::newValue(byte command, byte value, byte channel) {
	MidiCommand = command;
	MidiValue = value;
	MidiChannel = channel;
}

//****************************************************************************************
//************ SERVICE *******************************************************************
//****************************************************************************************

//ServiceButton (Pin Number, Command, Note Number, Channel)
ServiceButton::ServiceButton(byte pin, bool toggle, byte debounce)
{
	_debounce = debounce;
	_pin = pin;
  _hasMux = false;
  _toggle = toggle;
	pinMode(_pin, INPUT_PULLUP);
	updatePin();
  _oldValue = _value;
	_time = 0;
	haschanged = false;
  pressed = false;
	pressedDouble = false;
	pressedLong = false;
  serviceValue = 0;
}

ServiceButton::ServiceButton(byte pin, bool toggle, byte debounce, Mux *mux)
{
	_debounce = debounce;
	_pin = pin;
  *_mux = *mux;
  _hasMux = true;
  _toggle = toggle;
	updatePin();
  _oldValue = _value;
	_time = 0;
	haschanged = false;
  pressed = false;
	pressedDouble = false;
	pressedLong = false;
  serviceValue = 0; 
}

void ServiceButton::updatePin()
{
	if ( _hasMux == true ){
		_value = _mux->read(_pin);
	}
	else {
		_value = digitalRead(_pin);
	}
}

void ServiceButton::getValue()
{
	if (millis() > _debounce + _time){
		updatePin();
		_time = millis();
    if (_toggle == false){
      if (_value == LOW && _value != _oldValue){
        serviceValue = 127;
        haschanged = true;
      }
      else if (_value == HIGH && _value != _oldValue){
        serviceValue = 0;
        haschanged = true;		
      }
      else if (_value == _oldValue){
        haschanged = false;
      }
    }
    else if (_toggle == true){
      if (_value == LOW){
        if (_value != _oldValue && pressed == false){
          haschanged = true;
          if (serviceValue == 0){
            serviceValue = 127;
          }
          else {
            serviceValue = 0;
          }
        }
        else {
          haschanged = false;
        } 
        pressed = true;       
      }
      if (_value == HIGH){
        pressed = false;
        haschanged = false;
      }
    }
    _oldValue = _value;
	}
}


void ServiceButton::newValue(byte pin, byte value)
{
  _pin = pin;
 serviceValue = value;
}
//********************************************************************
ServicePot::ServicePot(byte pin)
{
	_pin = pin;
	_hasMux = false;
	updatePin();
	_oldServiceValue = serviceValue;
}

ServicePot::ServicePot(byte pin, Mux *mux)
{
	_pin = pin;
	_mux = mux;
	_hasMux = true;
	updatePin();
	_oldServiceValue = serviceValue;
}

void ServicePot::updatePin(){
	if ( _hasMux == true ){
		_value = _mux->read(_pin);
	}
	else {
		_value = analogRead(_pin); 
	}
	// division to convert 10bits to 8bits (bytes)
	serviceValue = _value / 8;
}

void ServicePot::getValue()
{
	updatePin();
	if (serviceValue  > _oldServiceValue + 2 || serviceValue  < _oldServiceValue - 2) {
		_oldServiceValue = serviceValue;
		haschanged = true;
	}
	else {
		haschanged = false;
	}
}

void ServicePot::newValue(byte value) {
	serviceValue = value;
}

//********************************************************************
ServiceEncoder::ServiceEncoder(byte pinA, byte pinB, bool eincremental)
{
	_pinA = pinA;
	_pinB = pinB;
	updatePin();
	_oldStatePinA = _statePinA;
	_oldStatePinB = _statePinB;
  incremental = eincremental;
	serviceValue = 0;
}

ServiceEncoder::ServiceEncoder(byte muxpinA, byte muxpinB, bool eincremental, Mux *mux)
{
	_pinA = muxpinA;
	_pinB = muxpinB;
	*_mux = *mux;
	_hasMux = true;
	updatePin();
	_oldStatePinA = _statePinA;
	_oldStatePinB = _statePinB;
  incremental = eincremental;
	serviceValue = 0;
}

void ServiceEncoder::updatePin()
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

void ServiceEncoder::getValue()
{
	updatePin();
  if ( incremental == true){
    if ( _statePinA != _oldStatePinA ){
      if ( _statePinB != _oldStatePinB ){
        serviceValue = 1;
      }
      else{
        serviceValue = 2;
      }
    }
    else{
      serviceValue = 0;
    }
  }
  else {
    if ( _statePinA != _oldStatePinA ){
      if ( _statePinB != _oldStatePinB ){
        if ( serviceValue < 2147483647 ){
          serviceValue++;
        }
      }
      else{
        if ( serviceValue > 0 ){
          serviceValue--;
        }
      }
    }
  }
	_oldStatePinA = _statePinA;
	_oldStatePinB = _statePinB;
}

void ServiceEncoder::newValue(byte value) {
	serviceValue = value;
}