#ifndef AudioSlice_h
#define AudioSlice_h

#include <Arduino.h>
#include <Controlino.h>

using namespace controlino;

class AudioSlice 
{
  public:
    AudioSlice(Button Mute,Button FilterType,Button LFORouting,Button Select,Potentiometer LFO,Potentiometer CutOff,Potentiometer Resonance,Potentiometer Volume,uint8_t Channel);
    Button ButMute;
    Button ButFilterType;
    Button ButLFORouting;
    Button ButSelect;
    Potentiometer PotLFO;
    Potentiometer PotCutOff;
    Potentiometer PotResonance;
    Potentiometer PotVolume;
    uint8_t Channel;
  private:
    uint8_t _volume;
    uint8_t _resonance;
    uint8_t _cutoff;
    int8_t _lfo;
    bool _mute;
    bool _select;
};
#endif