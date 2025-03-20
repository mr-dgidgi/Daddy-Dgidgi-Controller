#ifndef AudioSlice_h
#define AudioSlice_h

#include <Arduino.h>
#include <Controlino.h>

using namespace controlino;

class AudioSlice 
{
  public:
    AudioSlice(Button* Mute,Button* FilterType,Button* LFORouting,Button* Select,Potentiometer* LFO,Potentiometer* CutOff,Potentiometer* Resonance,Potentiometer* Volume,uint8_t Channel);
    AudioSlice(Button* Mute,Button* FilterType,Button* LFORouting,Button* Select,Potentiometer* LFO,Potentiometer* CutOff,Potentiometer* Resonance,Potentiometer* Volume,uint8_t Channel, byte LedMute, byte LedSelect);
    Button* ButMute;
    Button* ButFilterType;
    Button* ButLFORouting;
    Button* ButSelect;
    Potentiometer* PotLFO;
    Potentiometer* PotCutOff;
    Potentiometer* PotResonance;
    Potentiometer* PotVolume;
    uint8_t Channel;
    uint8_t VolumeVal;
    uint8_t ResonanceVal;
    uint8_t CutoffVal;
    uint8_t LfoVal;
    uint8_t FilterType;
    bool MuteVal;
    bool SelectVal;
    byte LedMute;
    byte LedSelect;
};
#endif