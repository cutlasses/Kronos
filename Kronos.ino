#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc;                     //xy=69,224
AudioMixer4              feedback_mixer;          //xy=238,228
AudioEffectDelay         delay_line;                   //xy=411,319
AudioFilterStateVariable filter;                  //xy=419,96
AudioMixer4              delay_mixer;             //xy=561,230
AudioEffectFreeverb      freeverb;                //xy=714,273
AudioMixer4              reverb_mixer;            //xy=881,222
AudioEffectBitcrusher    bitcrusher;              //xy=1048,281
AudioMixer4              bitcrusher_mixer;          //xy=1214,232
AudioOutputAnalog        dac;                     //xy=1364,231
AudioConnection          patch_cord_1( adc, 0, feedback_mixer, 0 );
AudioConnection          patch_cord_2( feedback_mixer, delay_line );
AudioConnection          patch_cord_3( feedback_mixer, 0, delay_mixer, 0);
AudioConnection          patch_cord_4( delay_line, 0, filter, 0);
AudioConnection          patch_cord_5( delay_line, 0, delay_mixer, 1);
AudioConnection          patch_cord_6( filter, 0, feedback_mixer, 1);
AudioConnection          patch_cord_d7( delay_mixer, freeverb );
AudioConnection          patch_cord_8( delay_mixer, 0, reverb_mixer, 0 );
AudioConnection          patch_cord_9( freeverb, 0, reverb_mixer, 1);
AudioConnection          patch_cord_10( reverb_mixer, bitcrusher_mixer );
AudioConnection          patch_cord_d11( reverb_mixer, 0, bitcrusher_mixer, 0 );
AudioConnection          patch_cord_12( bitcrusher, 0, bitcrusher_mixer, 1 );
AudioConnection          patch_cord_13( bitcrusher_mixer, dac );
// GUItool: end automatically generated code


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
