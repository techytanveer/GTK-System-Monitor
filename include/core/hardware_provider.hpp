#pragma once

#include "core/provider_interface.hpp"
#include "core/system_snapshot.hpp"
#include <glibtop/cpu.h>
#include <glibtop/mem.h>

namespace Shift {
    // Performance: This class handles the low-level hardware communication
    class HardwareProvider : public IDataProvider {
    public:
        HardwareProvider();
        virtual ~HardwareProvider() = default;

        // Correctness: Implementation of the interface to fetch real data
        SystemSnapshot get_latest_data() override;

    private:
        // Robustness: We store the previous CPU state to calculate deltas
        // (CPU usage is calculated as: delta_busy / delta_total)
        glibtop_cpu m_last_cpu;
        
        void initialize_cpu();
    };
}
