#include "Logging.h"
#include "Arduino.h"
#include "Bixi.h"

void CLogging::Init()
{
    Serial.begin(9600);
    unsigned long startMillis = millis();
    while(!Serial && millis() - startMillis < c_initTimeoutMs)
    {
        ;
    }

    log("*** Begin Session***");
}

void CLogging::log(const char* buff)
{
    if(!Serial)
        return;

    char logstr[128];
    sprintf(logstr, "[%lu (%u)]: %s", millis(), CBixi::Iteration(), buff);

    Serial.println(logstr);
}
