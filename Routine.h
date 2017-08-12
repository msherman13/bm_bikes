#pragma once

#include <stdlib.h>

#include "PixelArray.h"
#include "MemoryPool.h"

struct CRGB;

class CRoutine
{
    public:
        static constexpr float c_transition_q = 2.0;

    public:
        CRoutine(CPixelArray* pixels);
        virtual ~CRoutine();

    public:
        virtual void            Continue() = 0;
        virtual const char*     GetName()  = 0;
        void                    SetAllPixels();
        void                    SetPixel(size_t index, CRGB rgb);
        void                    SetAllPixels(CRGB rgb);
        CRGB                    GetPixel(size_t index);
        CPixelArray*            GetPixels() { return m_pixels; }
        void                    SetPixels(CPixelArray* pixels) { m_pixels = pixels; }
        size_t                  GetSize();

    private:
        CPixelArray* m_pixels = nullptr;
};
