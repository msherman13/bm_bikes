#pragma once

#include <stdlib.h>
#include "PixelArray.h"
#include "MemoryPool.h"

class CRoutine;

class CBike : public CPixelArray
{
    public:
        static constexpr size_t c_alloc_qty = 1;

    public:
        CBike();
        ~CBike();

    private:
        static CMemoryPool<CBike, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CBike*>(ptr));
        }
};
