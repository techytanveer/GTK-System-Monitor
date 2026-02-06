#pragma once
#include "system_snapshot.hpp"
#include <memory>

namespace Shift {
    class IDataProvider {
    public:
        virtual ~IDataProvider() = default;
        // Correctness: Returns a snapshot of the current system state.
        virtual SystemSnapshot get_latest_data() = 0;
    };
}
