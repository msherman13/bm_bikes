#pragma once

#include "stdint.h"

#include "Routine.h"

class CPixelArray;

class CRoutineRainbow : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty           = 1;
        static constexpr size_t c_spacing             = 4;

    public:
        CRoutineRainbow(CPixelArray* pixels);
        ~CRoutineRainbow();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Rainbow"; }

    private:
        size_t            m_start    = 0;
        unsigned long int m_last_run = 0;
        unsigned long int m_last_color = 0;
        CRGB              m_color    = 0;

    private:
        static CMemoryPool<CRoutineRainbow, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineRainbow*>(ptr));
        }
};
