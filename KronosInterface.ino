#include "KronosInterface.h"
#include "Util.h"

KRONOS_INTERFACE::KRONOS_INTERFACE() :
  m_dials( { DIAL( A20 ), DIAL( A19 ), DIAL( A18 ), DIAL( A17 ), DIAL( A16 ), DIAL( A13 ) } ),
  m_delay_toggle_button( DELAY_TOGGLE_PIN, true ),
  m_bitcrusher_toggle_button( BITCRUSHER_TOGGLE_PIN, true ),
  m_leds( { LED( LED_1_PIN, false ), LED( LED_2_PIN, false ), LED( LED_3_PIN, false ) } ),
  m_delay_time_and_mix( m_dials[0], m_delay_toggle_button, INITIAL_DELAY_MIX ),
  m_feedback_and_filter_freq( m_dials[1], m_delay_toggle_button, INITIAL_FILTER_FREQUENCY / MAX_FILTER_FREQUENCY ),
  m_reverb_size_and_mix_push_and_turn( m_dials[2], m_delay_toggle_button, INITIAL_REVERB_MIX )
{

}

void KRONOS_INTERFACE::setup()
{
  m_delay_toggle_button.setup();
  m_bitcrusher_toggle_button.setup();

  for( int l = 0; l < NUM_LEDS; ++l )
  {
    m_leds[l].setup();
    m_leds[l].set_brightness( 0.25f );
  }
}

void KRONOS_INTERFACE::update( ADC& adc, uint32_t time_in_ms )
{
  // read each pot
  for( int d = 0; d < NUM_DIALS; ++d )
  {
    m_dials[d].update( adc );
  }
  
  m_delay_toggle_button.update( time_in_ms );
  m_bitcrusher_toggle_button.update( time_in_ms );

  // push and turn must be updated after dials and buttons
  m_delay_time_and_mix.update();
  m_feedback_and_filter_freq.update();
  m_reverb_size_and_mix_push_and_turn.update();

  if( m_delay_toggle_button.active() )
  {
    m_leds[0].set_active( true );
  }
  else
  {
    m_leds[0].set_active( false );
  }

  if( m_bitcrusher_toggle_button.active() )
  {
    m_leds[1].set_active( true );
  }
  else
  {
    m_leds[1].set_active( false );
  }

  for( int l = 0; l < NUM_LEDS; ++l )
  {
    m_leds[l].update( time_in_ms );
  }
}

float KRONOS_INTERFACE::delay_time() const
{
  return m_delay_time_and_mix.primary_value() * MAX_DELAY_TIME_MS;
}

float KRONOS_INTERFACE::feedback() const
{
  return m_feedback_and_filter_freq.primary_value() * MAX_FEEDBACK;
}

float KRONOS_INTERFACE::filter_frequency() const
{
  return m_feedback_and_filter_freq.secondary_value() * MAX_FILTER_FREQUENCY;
}

float KRONOS_INTERFACE::filter_resonance() const
{
  return FIXED_FILTER_RESONANCE;
}

float KRONOS_INTERFACE::delay_mix() const
{
  if( m_delay_toggle_button.active() )
  {
    return m_delay_time_and_mix.secondary_value();
  }
  else
  {
    return 0.0f;
  }
}

float KRONOS_INTERFACE::reverb_size() const
{
  return m_reverb_size_and_mix_push_and_turn.primary_value();
}

float KRONOS_INTERFACE::reverb_damping() const
{
  return m_dials[3].value();
}

float KRONOS_INTERFACE::reverb_mix() const
{
  return m_reverb_size_and_mix_push_and_turn.secondary_value();
}

int KRONOS_INTERFACE::sample_rate() const
{
  const float freq = m_dials[4].value() * 44100.0f;
  return clamp<int>( freq, 1, 44100 );
}

int KRONOS_INTERFACE::bit_depth() const
{
  return trunc_to_int( m_dials[5].value() * 15.0f ) + 1;
}

float KRONOS_INTERFACE::bitcrusher_mix() const
{
  if( m_bitcrusher_toggle_button.active() )
  {
    return 1.0f;
  }
  else
  {
    return 0.0f;
  }
}

void KRONOS_INTERFACE::set_clipping( bool clipping )
{
  m_leds[2].set_active(clipping);
}
