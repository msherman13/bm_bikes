#pragma once

#include "FastLED.h"
#include "PixelArray.h"
#include "Addressing.h"

class CBixi
{
    public:
        static constexpr size_t c_indicatorPin     = 13;
        static constexpr size_t c_indicatorDelayMs = 1000;
        static constexpr size_t c_data_pin         = 9;

    public: // singleton
        static CBixi& Instance();
        CBixi();
        ~CBixi();

    public:
        void Continue();
        static size_t Iteration() { return s_iteration; }

    protected:
        virtual void Show(CPixelArray* pixels);

    private:
        unsigned long m_lastIndicator = 0;
        bool          m_indicatorOn   = false;
        CPixelArray*  m_geometry      = nullptr;

    private:
        static size_t s_iteration;
};
