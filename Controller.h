#ifndef Controller_h
#define Controller_h

#include <Arduino.h>
#include "Mux.h"
using namespace admux;

//************************************************************************
//MidiButton (Pin Number, byte Command, Note Number, byte Channel, Debounce Time)
class MidiButton
{
	public:
		MidiButton(byte pin, byte command, bool toggle, byte channel, byte debounce);
		MidiButton(byte pin, byte command, bool toggle, byte channel, byte debounce, Mux *mux);
		void updatePin();
		void newValue(byte command, byte value, byte channel);
		void getValue();
		byte MidiChannel;
		byte MidiCommand;
		byte MidiValue;
		bool haschanged;

	private:
		byte _pin;
		Mux *_mux;
		byte _value;
		byte _oldValue;
		bool _hasMux;
		byte _debounce;
		int _time;
    bool _toggle;
};
//*************************************************************************
class MidiPot
{
	public:
		MidiPot(byte pin, byte command, byte channel);
		MidiPot(byte pin, byte command, byte channel, Mux *mux);
		void updatePin();
		void newValue(byte command, byte value, byte channel);
		void getValue();
		byte MidiValue;
		byte MidiCommand;
		byte MidiChannel;
		bool haschanged;

	private:
		byte _pin;
		Mux *_mux;
		int _value;
		int _oldMidiValue;
		bool _hasMux;
};
//*************************************************************************
class MidiEncoder
{
	public:
		MidiEncoder(byte pinA, byte pinB, byte command, byte channel);
		MidiEncoder(byte pinA, byte pinB, byte command, byte channel, Mux *mux);
		void updatePin();
		void newValue(byte command, byte value, byte channel);
		void getValue();
		byte MidiValue;
		byte MidiCommand;
		byte MidiChannel;
		bool haschanged;

	private:
		byte _pinA;
		byte _pinB;
		Mux *_mux;
		byte _statePinA;
		byte _statePinB;
		byte _oldStatePinA;
		byte _oldStatePinB;
		bool _hasMux;
};
//*************************************************************************
//ServiceButton 
class ServiceButton
{
	public:
		ServiceButton(byte pin, bool toggle, byte debounce);
		ServiceButton(byte pin, bool toggle, byte debounce, Mux *mux);
		void updatePin();
		void newValue(byte pin, byte value);
		void getValue();
		byte serviceValue;
		bool haschanged;

	private:
		byte _pin;
		Mux *_mux;
		bool _hasMux;
		byte _debounce;
		int _time;
    byte _value;
    byte _oldValue;
    bool _toggle;
};
//*************************************************************************
class ServicePot
{
	public:
		ServicePot(byte pin);
		ServicePot(byte pin, Mux *mux);
		void updatePin();
		void newValue(byte value);
		void getValue();
		byte serviceValue;
		bool haschanged;

	private:
		byte _pin;
		Mux *_mux;
		int _value;
		int _oldServiceValue;
		bool _hasMux;
};
//*************************************************************************
class ServiceEncoder
{
	public:
		ServiceEncoder(byte pinA, byte pinB);
		ServiceEncoder(byte pinA, byte pinB, Mux *mux);
		void updatePin();
		void newValue(byte value);
		void getValue();
		byte serviceValue;
		bool haschanged;

	private:
		byte _pinA;
		byte _pinB;
		Mux *_mux;
		byte _statePinA;
		byte _statePinB;
		byte _oldStatePinA;
		byte _oldStatePinB;
		bool _hasMux;
};
#endif
