#include "Bike.h"
#include "Logging.h"
#include "FastLED.h"
#include "RoutineFire.h"

CMemoryPool<CBike, 1>  CBike::s_pool;
CBike::BikeConfig CBike::s_config;

CPixelArray::Coordinate CBike::BikeConfig::GetCoordinate(size_t index)
{
    return CPixelArray::Coordinate(0.0, (float)index / m_logical_size);
}

CBike::CBike() :
    CPixelArray("Bike", &s_config)
{
    SetRoutine(new CRoutineFire(this));
}

CBike::~CBike()
{
}
