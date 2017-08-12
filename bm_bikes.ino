#include "Bixi.h"
#include "Logging.h"

void setup()
{
    CLogging::Init();
    CBixi::Instance();
    CLogging::log("Bixi is initialized");
}

void loop()
{
    CBixi::Instance().Continue();
}  
