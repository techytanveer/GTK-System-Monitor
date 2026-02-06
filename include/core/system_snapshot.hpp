#pragma once
#include <vector>
#include <string>
#include <cstdint> // Correctness: Required for fixed-width types like uint64_t

namespace Shift {
    // Determinism: Represents a fixed point in time. 
    // This allows for "Time Travel" debugging or easy logging.
    struct CpuSnapshot {
        double total_usage = 0.0;
        std::vector<double> core_loads;
    };

    struct MemorySnapshot {
        uint64_t total_bytes = 0;
        uint64_t used_bytes = 0;
        double percentage = 0.0;
    };

    struct SystemSnapshot {
        CpuSnapshot cpu;
        MemorySnapshot mem;
    };
}
