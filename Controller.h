#ifndef Controller_h
#define Controller_h

#include <Arduino.h>
#include "Mux.h"
using namespace admux;

//************************************************************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
class Button
{
  public:
    Button(byte pin, byte command, byte channel, byte _debounce);
    Button(byte pin, byte command, byte channel, byte _debounce, Mux *mux);
    void updatePin();
    void newValue(byte command, byte value, byte channel);
    bool getValue();
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
};
//*************************************************************************
class Pot
{
  public:
    Pot(byte pin, byte command, byte channel);
    Pot(byte pin, byte command, byte channel, Mux *mux);
    void updatePin();
    void newValue(byte command, byte value, byte channel);
    bool getValue();
    byte MidiValue;
    byte MidiCommand;
    byte MidiChannel;
    bool haschanged;

  private:
    byte _pin;
    Mux *_mux;
    int _value;
    int _oldValue;
    bool _hasMux;
};
//*************************************************************************
class Encoder
{
  public:
    Encoder(byte pinA, byte pinB, byte command, byte channel);
    Encoder(byte pinA, byte pinB, byte command, byte channel, Mux *mux);
    void updatePin();
    void newValue(byte command, byte value, byte channel);
    bool getValue();
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
#endif
