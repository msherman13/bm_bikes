#include "Bixi.h"
#include "Logging.h"
#include "Arduino.h"
#include "Bike.h"
#include "FreeRam.h"

size_t CBixi::s_iteration = 0;

CBixi& CBixi::Instance()
{
    static CBixi bixi;
    return bixi;
}

CBixi::CBixi()
{
    CLogging::log("CBixi::CBixi: Initializing Bixi");

    // indicator
    pinMode(c_indicatorPin, OUTPUT);

    // geometry
    CLogging::log("CBixi::CBixi: Geometry = GEOM_BIKE");
    m_geometry = new CBike();

    // Parallel Output
    LEDS.addLeds<WS2812B, c_data_pin, GRB>(m_geometry->GetRaw(), m_geometry->GetSize());

    char logstr[128];
    sprintf(logstr, "CBixi::CBixi: Initial allocations complete, %u byte remaining", FreeRam());
    CLogging::log(logstr);
}

CBixi::~CBixi()
{
    CLogging::log("CBixi::~CBixi: Destructing");

    delete m_geometry;
}

void CBixi::Show(CPixelArray* pixels)
{
    LEDS.show();
}

void CBixi::Continue()
{
    unsigned long now = millis();

    s_iteration++;

    m_geometry->Continue();

    Show(m_geometry);

    if(now - m_lastIndicator >= c_indicatorDelayMs)
    {
        m_indicatorOn   = !m_indicatorOn;
        m_lastIndicator = now;
        digitalWrite(c_indicatorPin, m_indicatorOn ? HIGH : LOW);
    }
}
