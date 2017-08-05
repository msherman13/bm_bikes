#pragma once

#include <stdlib.h>
#include "PixelArray.h"
#include "MemoryPool.h"

class CRoutine;

class CBike : public CPixelArray
{
    public:
        static constexpr size_t c_transition_time_ms  = 20 * 1000;
        static constexpr size_t c_min_routine_time_ms = 2 * 60 * 1000;
        static constexpr size_t c_max_routine_time_ms = 4 * 60 * 1000;

    public:
        class BikeConfig : public CPixelArray::Config
        {
            public:
                BikeConfig() :
                    CPixelArray::Config()
                {
                    m_physical_size = 60;
                    m_logical_size = 60;
                    m_num_legs = 1;
                }

                virtual CPixelArray::Coordinate GetCoordinate(size_t index) override;
        };

    public:
        CBike();
        ~CBike();

    private:
        static CMemoryPool<CBike, 1> s_pool;

    public:
        void* operator new(size_t size)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CBike*>(ptr));
        }

    public:
        static BikeConfig s_config;
};
