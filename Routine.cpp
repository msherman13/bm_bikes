#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"
#include "Arduino.h"
#include "Bixi.h"

//#include <algorithm>

CRoutine::CRoutine(CPixelArray* pixels) :
    m_pixels(pixels)
{
}

CRoutine::~CRoutine()
{
}

void CRoutine::SetPixel(size_t index, CRGB rgb)
{
    m_pixels->SetPixel(index, rgb);
}

void CRoutine::SetAllPixels(CRGB rgb)
{
    for(size_t i=0;i<GetSize();i++)
    {
        SetPixel(i, rgb);
    }
}

CRGB CRoutine::GetPixel(size_t index)
{
    return m_pixels->GetPixel(index);
}

size_t CRoutine::GetSize()
{
    return m_pixels->GetSize();
}
