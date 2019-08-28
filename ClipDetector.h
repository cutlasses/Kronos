#pragma once

#include <Audio.h>
#include <limits>

class CLIP_DETECTOR : public AudioStream
{
  
public:

  CLIP_DETECTOR( int clip_time_out ) :
    AudioStream(1, m_input_queue_array),
    m_clip_time_out( clip_time_out ),
    m_clip_timer( 0 )
  {
  }

  virtual void update() override
  {
    if( m_clip_timer > 0 )
    {
      --m_clip_timer;
    }

    audio_block_t* in_block = receiveReadOnly();

    if( in_block != nullptr )
    {
      // is this sample clipping
      for( int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i )
      {
        const int threshold = 10;
        if( abs(in_block->data[i]) >= (std::numeric_limits<int16_t>::max() - threshold) )
        {
          m_clip_timer = m_clip_time_out;
          break;
        }
      }
      
      transmit(in_block);

      release(in_block);
    }
  }
  
  bool clipping() const
  {
    return m_clip_timer > 0;
  }

private:

  audio_block_t*      m_input_queue_array[1];
  const int           m_clip_time_out;
  int                 m_clip_timer;
};
