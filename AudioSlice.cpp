#include "AudioSlice.h"

AudioSlice::AudioSlice(Button Mute,Button FilterType,Button LFORouting,Button Select,Potentiometer LFO,Potentiometer CutOff,Potentiometer Resonance,Potentiometer Volume,uint8_t Channel){
  ButMute = Mute;
  ButFilterType = FilterType;
  ButLFORouting = LFORouting;
  ButSelect = Select;
  PotLFO = LFO;
  PotCutOff = CutOff;
  PotResonance = Resonance;
  PotVolume = Volume;
  Channel = Channel;
  _volume = 255;
  _resonance = 255;
  _cutoff = 255;
  _lfo = 255;
  _select = false;
}
