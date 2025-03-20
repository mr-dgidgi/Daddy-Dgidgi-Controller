#include "AudioSlice.h"

AudioSlice::AudioSlice(Button* Mute,Button* FilterType,Button* LFORouting,Button* Select,Potentiometer* LFO,Potentiometer* CutOff,Potentiometer* Resonance,Potentiometer* Volume,uint8_t Channel){
  *ButMute = *Mute;
  *ButFilterType = *FilterType;
  *ButLFORouting = *LFORouting;
  *ButSelect = *Select;
  *PotLFO = *LFO;
  *PotCutOff = *CutOff;
  *PotResonance = *Resonance;
  *PotVolume = *Volume;
  Channel = Channel;
  VolumeVal = 255;
  ResonanceVal = 255;
  CutoffVal = 255;
  LfoVal = 255;
  FilterType = 0;
  MuteVal = false;
  SelectVal = false;
  LedMute = 0;
  LedSelect = 0;
}

AudioSlice::AudioSlice(Button* Mute,Button* FilterType,Button* LFORouting,Button* Select,Potentiometer* LFO,Potentiometer* CutOff,Potentiometer* Resonance,Potentiometer* Volume,uint8_t Channel, byte LedMute, byte LedSelect){
  *ButMute = *Mute;
  *ButFilterType = *FilterType;
  *ButLFORouting = *LFORouting;
  *ButSelect = *Select;
  *PotLFO = *LFO;
  *PotCutOff = *CutOff;
  *PotResonance = *Resonance;
  *PotVolume = *Volume;
  Channel = Channel;
  VolumeVal = 255;
  ResonanceVal = 255;
  CutoffVal = 255;
  LfoVal = 255;
  FilterType = 0;
  MuteVal = false;
  SelectVal = false;
  LedMute = LedMute;
  LedSelect = LedSelect;
}
