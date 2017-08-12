#include <math.h>

#include "RoutineSparkle.h"
#include "PixelArray.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineSparkle, CRoutineSparkle::c_alloc_qty> CRoutineSparkle::s_pool;

CRoutineSparkle::CRoutineSparkle(CPixelArray* pixels) :
    CRoutine(pixels)
{
    m_last_run = millis();
    m_num_lit = c_max_num_lit;
    m_num_lit = min(GetSize() / 2, m_num_lit);

    for(size_t i=0;i<m_num_lit;i++)
    {
        m_release_ms[i] = rand() % c_release_ms;
        m_lit[i] = rand() % GetSize();
        m_color[i]      = rgb2hsv_approximate(CRGB(ColorPallete::s_colors[rand() % ColorPallete::Qty]));
    }
}

CRoutineSparkle::~CRoutineSparkle()
{
}

void CRoutineSparkle::Continue()
{
    size_t now = millis();

    SetAllPixels(CRGB::Black);

    for(size_t i=0;i<m_num_lit;i++)
    {
        if(m_release_ms[i] <= now - m_last_run)
        {
            m_release_ms[i] = c_release_ms;
            m_lit[i]        = rand() % GetSize();
            m_color[i]      = rgb2hsv_approximate(CRGB(ColorPallete::s_colors[rand() % ColorPallete::Qty]));
        }
        else
        {
            m_release_ms[i] -= now - m_last_run;
        }

        float brightness_mod = (float)(m_release_ms[i]) / c_release_ms;
        CHSV color = m_color[i];
        color.v = brightness_mod * 255;

        SetPixel(m_lit[i], color);
    }

    m_last_run = now;
}
