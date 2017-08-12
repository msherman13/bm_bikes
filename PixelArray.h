#pragma once

#include "FastLED.h"
#include "MemoryPool.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

class  CRoutine;

class CPixelArray
{
    public:
        static constexpr size_t c_num_pixels = 90;

    public:
        CPixelArray();
        virtual ~CPixelArray();

    public:
        void         SetRoutine(CRoutine* routine);
        virtual void ExitRoutine();
        virtual void Continue();
        bool         InRoutine()      { return m_routine != nullptr; }

    public:
        size_t         GetSize() const                               { return c_num_pixels; }
        CRGB*          GetRaw(size_t index=0)                        { return &m_pixels[index]; }

    public:
        CRGB    GetPixel(size_t index);
        void    SetPixel(size_t index, CRGB rgb);
        CRGB    GetPixelRaw(size_t index);
        void    SetPixelRaw(size_t index, CRGB rgb);
        void    SetAllPixels(CRGB rgb);

    protected:
        CRGB   m_pixels[c_num_pixels];

    protected:
        CRoutine* m_routine           = nullptr;
};
