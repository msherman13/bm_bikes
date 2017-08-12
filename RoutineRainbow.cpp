//#include <algorithm>
#include <math.h>

#include "RoutineRainbow.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"
#include "Logging.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineRainbow, CRoutineRainbow::c_alloc_qty> CRoutineRainbow::s_pool;

CRoutineRainbow::CRoutineRainbow(CPixelArray* pixels) :
    CRoutine(pixels)
{
    m_last_run = millis();

    for(size_t i=0;i<GetSize();i++)
    {
        if(i % c_spacing == 0)
        {
            SetPixel(i, ColorPallete::Mint);
        }
        else
        {
            SetPixel(i, CRGB::Black);
        }
    }
}

CRoutineRainbow::~CRoutineRainbow()
{
}

void CRoutineRainbow::Continue()
{
    unsigned long now = millis();

    if(now - m_last_run < 100)
    {
        return;
    }

    if(now - m_last_color >= 20000)
    {
        m_color = ColorPallete::s_colors[rand() % ColorPallete::Qty];
        m_last_color = now;
    }

    m_last_run = now;
    m_start++;

    for(size_t i=0;i<GetSize();i++)
    {
        if((i + m_start % GetSize()) % c_spacing == 0)
        {
            SetPixel(i, m_color);
        }
        else
        {
            SetPixel(i, CRGB::Black);
        }
    }
}
