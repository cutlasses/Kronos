#include <ADC.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "KronosInterface.h"


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
AudioConnection          patch_cord_2( feedback_mixer, 0, delay_line, 0 );
AudioConnection          patch_cord_3( io.audio_input, 0, delay_mixer, 0);
AudioConnection          patch_cord_4( delay_line, 0, filter, 0);
AudioConnection          patch_cord_5( delay_line, 0, delay_mixer, 1);
AudioConnection          patch_cord_6( filter, 0, feedback_mixer, 1);
AudioConnection          patch_cord_d7( delay_mixer, 0, freeverb, 0 );
AudioConnection          patch_cord_8( delay_mixer, 0, reverb_mixer, 0 );
AudioConnection          patch_cord_9( freeverb, 0, reverb_mixer, 1);
AudioConnection          patch_cord_10( reverb_mixer, 0, bitcrusher, 0 );
AudioConnection          patch_cord_11( reverb_mixer, 0, bitcrusher_mixer, 0 );
AudioConnection          patch_cord_12( bitcrusher, 0, bitcrusher_mixer, 1 );
AudioConnection          patch_cord_13( bitcrusher_mixer, io.audio_output );

KRONOS_INTERFACE         g_kronos_interface;


//////////////////////////////////////

void set_adc1_to_3v3()
{
  ADC1_SC3 = 0; // cancel calibration
  ADC1_SC2 = ADC_SC2_REFSEL(0); // vcc/ext ref 3.3v

  ADC1_SC3 = ADC_SC3_CAL;  // begin calibration

  uint16_t sum;

  //serial_print("wait_for_cal\n");

  while( (ADC1_SC3 & ADC_SC3_CAL))
  {
    // wait
  }

  __disable_irq();

    sum = ADC1_CLPS + ADC1_CLP4 + ADC1_CLP3 + ADC1_CLP2 + ADC1_CLP1 + ADC1_CLP0;
    sum = (sum / 2) | 0x8000;
    ADC1_PG = sum;
    sum = ADC1_CLMS + ADC1_CLM4 + ADC1_CLM3 + ADC1_CLM2 + ADC1_CLM1 + ADC1_CLM0;
    sum = (sum / 2) | 0x8000;
    ADC1_MG = sum;

  __enable_irq();
  
}

void setup()
{
 Serial.begin(9600);

  AudioMemory(256);

  analogReference(INTERNAL);

  set_adc1_to_3v3();

  Serial.print("Setup finished!\n");
}

void loop()
{
  const uint32_t time_in_ms = millis();
  g_kronos_interface.update( io.adc, time_in_ms );

  if( g_kronos_interface.delay_active() )
  {
    delay_mixer.gain( 0, 0.0f );
    delay_mixer.gain( 1, 1.0f );
  }
  else
  {
    delay_mixer.gain( 0, 1.0f );
    delay_mixer.gain( 1, 0.0f );
  }

  if( g_kronos_interface.bitcrusher_active() )
  {
    bitcrusher_mixer.gain( 0, 0.0f );
    bitcrusher_mixer.gain( 1, 1.0f );
  }
  else
  {
    bitcrusher_mixer.gain( 0, 1.0f );
    bitcrusher_mixer.gain( 1, 0.0f );
  }
}
