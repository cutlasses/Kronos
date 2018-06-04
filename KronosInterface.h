#pragma once

#include "Interface.h"
#include "Util.h"

class KRONOS_INTERFACE
{
    static constexpr int    DELAY_TOGGLE_PIN              = 2;
    static constexpr int    BITCRUSHER_TOGGLE_PIN         = 1;
    static constexpr int    LED_1_PIN                     = 29;
    static constexpr int    LED_2_PIN                     = 11;
    static constexpr int    LED_3_PIN                     = 7;

    static constexpr int    NUM_DIALS                     = 6;
    static constexpr int    NUM_LEDS                      = 3;

    static constexpr float  FIXED_FILTER_FREQUENCY        = 1000.0f;
    static constexpr float  FIXED_FILTER_RESONANCE        = 0.707f;
    static constexpr float  FIXED_REVERB_DAMPING          = 0.2f;

    static constexpr float  MAX_DELAY_TIME_MS             = 500.0f;

    DIAL                  m_dials[NUM_DIALS];

    BUTTON                m_delay_toggle_button;    // or tap bpm?
    BUTTON                m_bitcrusher_toggle_button;

    LED                   m_leds[NUM_LEDS];

  public:

    KRONOS_INTERFACE();

    constexpr static int      required_audio_memory()     { return trunc_to_int( ceil(MAX_DELAY_TIME_MS / 2.9f) ); }

    void                      setup();

    void                      update( ADC& adc, uint32_t time_in_ms );

    float                     delay_time() const;
    float                     feedback() const;
    float                     filter_frequency() const;
    float                     filter_resonance() const;
    float                     delay_mix() const;
    float                     reverb_size() const;
    float                     reverb_damping() const;
    float                     reverb_mix() const;
    int                       sample_rate() const;
    int                       bit_depth() const;
    float                     bitcrusher_mix() const;
};
