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

    m_show = new CPixelArray(*m_geometry);

    // Parallel Output
    LEDS.addLeds<WS2813_PORTD>(m_show->GetRaw(), m_show->GetRawSize());

    char logstr[256];
    sprintf(logstr, "CBixi::CBixi: Initial allocations complete, %u byte remaining", FreeRam());
    CLogging::log(logstr);
}

CBixi::~CBixi()
{
    CLogging::log("CBixi::~CBixi: Destructing");

    ShutDown();

    delete m_geometry;
}

void CBixi::Show(CPixelArray* pixels)
{
    for(size_t i=0;i<pixels->GetSize();i++)
    {
        m_show->SetPixel(i, pixels->GetPixel(i));
    }

    LEDS.show();
}

void CBixi::Continue()
{
    s_iteration++;

    size_t now = millis();

    m_geometry->Continue();

    Show(m_geometry);

    FastLED.countFPS();

    static size_t last_log = 0;
    if(now - last_log >= 10000)
    {
        last_log = now;
        char logString[128];
        sprintf(logString, "CBixi::Continue: Frame rate for last 10 seconds is %u", FastLED.getFPS());
        CLogging::log(logString);
    }

    if(now - m_lastIndicator >= c_indicatorDelayMs)
    {
        m_indicatorOn   = !m_indicatorOn;
        m_lastIndicator = now;
        digitalWrite(c_indicatorPin, m_indicatorOn ? HIGH : LOW);
    }
}
