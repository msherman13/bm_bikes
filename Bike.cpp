#include "Bike.h"
#include "Logging.h"
#include "FastLED.h"
#include "RoutineRainbow.h"

#include <string.h>

CMemoryPool<CBike, CBike::c_alloc_qty>                CBike::s_pool;

CBike::CBike() :
    CPixelArray()
{
    SetRoutine(new CRoutineRainbow(this));
}

CBike::~CBike()
{
}
