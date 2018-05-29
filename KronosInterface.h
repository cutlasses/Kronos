#include "Interface.h"

class KRONOS_INTERFACE
{
  static const int      DELAY_TOGGLE_PIN                = 2;
  static const int      BITCRUSHER_TOGGLE_PIN           = 1;
  static const int      LED_1_PIN                       = 29;
  static const int      LED_2_PIN                       = 11;
  static const int      LED_3_PIN                       = 7;

  static const int      NUM_DIALS                       = 6;
  static const int      NUM_LEDS                        = 3;
 
  DIAL                  m_dials[NUM_DIALS];

  BUTTON                m_delay_toggle_button;    // or tap bpm?
  BUTTON                m_bitcrusher_toggle_button;

  LED                   m_leds[NUM_LEDS];

public:

  KRONOS_INTERFACE();

  void            setup();

  void            update( ADC& adc, uint32_t time_in_ms );

  float           delay_time() const;
  float           feedback() const;
  float           reverb_size() const;
  float           reverb_mix() const;
  int             sample_rate() const;
  int             bit_depth() const;
};
