//#include <algorithm>
#include <math.h>

#include "RoutineRainbow.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"
#include "Logging.h"

CMemoryPool<CRoutineRainbow, CRoutineRainbow::c_alloc_qty> CRoutineRainbow::s_pool;

CRoutineRainbow::CRoutineRainbow(CPixelArray* pixels) :
    CRoutine(pixels)
{
    m_last_run = millis();

    for(size_t i=0;i<GetSize();i++)
    {
        CHSV color(((float)i / (GetSize()-1)) * 255, 255, 255);
        SetPixel(i, color);
    }
}

CRoutineRainbow::~CRoutineRainbow()
{
}

void CRoutineRainbow::Continue()
{
    unsigned long now = millis();

    if(now - m_last_run < 30)
    {
        return;
    }

    m_last_run = now;
    m_start++;

    for(size_t i=0;i<GetSize();i++)
    {
        CHSV color(((float)((i+m_start) % GetSize()) / (GetSize()-1)) * 255, 255, 255);
        SetPixel(i, color);
    }
}
