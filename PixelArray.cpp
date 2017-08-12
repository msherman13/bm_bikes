#include <math.h>
#include <stdlib.h>

#include "PixelArray.h"
#include "Logging.h"
#include "Routine.h"
#include "Math.h"

CPixelArray::CPixelArray()
{
    SetAllPixels(CRGB::Black);
}

CPixelArray::~CPixelArray()
{
    ExitRoutine();
}

CRGB CPixelArray::GetPixel(size_t index)
{
    return GetPixelRaw(index);
}

void CPixelArray::SetPixel(size_t index, CRGB rgb)
{
    SetPixelRaw(index, rgb);
}

CRGB CPixelArray::GetPixelRaw(size_t index)
{
    return m_pixels[index];
}

void CPixelArray::SetPixelRaw(size_t index, CRGB rgb)
{
    m_pixels[index] = rgb;
}

void CPixelArray::SetAllPixels(CRGB rgb)
{
    for(size_t i=0;i<GetSize();i++)
    {
        SetPixel(i, rgb);
    }
}

void CPixelArray::ExitRoutine()
{
    if(m_routine == nullptr)
    {
        return;
    }

    char logstr[128];
    sprintf(logstr, "CPixelArray::ExitRoutine: Exiting routine [%s]", m_routine->GetName());
    CLogging::log(logstr);

    delete m_routine;

    m_routine = nullptr;
}

void CPixelArray::SetRoutine(CRoutine* routine)
{
    ExitRoutine();

    char logstr[128];
    sprintf(logstr, "CPixelArray::SetRoutine: Setting routine to [%s]", routine->GetName());
    CLogging::log(logstr);

    m_routine = routine;
}

void CPixelArray::Continue()
{
    if(InRoutine() == true)
    {
        m_routine->Continue();
    }
}
