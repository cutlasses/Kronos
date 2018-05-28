#include <ADC.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// wrap in a struct to ensure initialisation order
struct IO
{
  ADC                         adc;
  AudioInputAnalog            audio_input;
  AudioOutputAnalog           audio_output;

  IO() :
    adc(),
    audio_input(A0),
    audio_output()
  {
  }
};

IO io;

AudioMixer4              feedback_mixer;
AudioEffectDelay         delay_line;
AudioFilterStateVariable filter;
AudioMixer4              delay_mixer;
AudioEffectFreeverb      freeverb;
AudioMixer4              reverb_mixer;
AudioEffectBitcrusher    bitcrusher;
AudioMixer4              bitcrusher_mixer;

AudioConnection          patch_cord_1( io.audio_input, 0, feedback_mixer, 0 );
AudioConnection          patch_cord_2( feedback_mixer, delay_line );
AudioConnection          patch_cord_3( feedback_mixer, 0, delay_mixer, 0);
AudioConnection          patch_cord_4( delay_line, 0, filter, 0);
AudioConnection          patch_cord_5( delay_line, 0, delay_mixer, 1);
AudioConnection          patch_cord_6( filter, 0, feedback_mixer, 1);
AudioConnection          patch_cord_d7( delay_mixer, freeverb );
AudioConnection          patch_cord_8( delay_mixer, 0, reverb_mixer, 0 );
AudioConnection          patch_cord_9( freeverb, 0, reverb_mixer, 1);
AudioConnection          patch_cord_10( reverb_mixer, bitcrusher_mixer );
AudioConnection          patch_cord_11( reverb_mixer, 0, bitcrusher_mixer, 0 );
AudioConnection          patch_cord_12( bitcrusher, 0, bitcrusher_mixer, 1 );
AudioConnection          patch_cord_13( bitcrusher_mixer, io.audio_output );

void setup()
{
  // put your setup code here, to run once:

}

void loop()
{
  // put your main code here, to run repeatedly:

}
