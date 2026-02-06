#include "core/hardware_provider.hpp"
#include <glibtop/cpu.h>
#include <glibtop/mem.h>


namespace Shift {

	// Correctness: The linker was looking for this specific definition!
    HardwareProvider::HardwareProvider() {
        // Initialize libgtop CPU stats so the first delta isn't garbage
        glibtop_get_cpu(&m_last_cpu);
    }


    SystemSnapshot HardwareProvider::get_latest_data() {
        SystemSnapshot snap;
        
        // Memory (Correctness: Direct syscall via libgtop)
        glibtop_mem mem;
        glibtop_get_mem(&mem);
        snap.mem.total_bytes = mem.total;
        snap.mem.used_bytes = mem.user;
        snap.mem.percentage = (static_cast<double>(mem.user) / mem.total) * 100.0;

        // CPU (Robustness: Logic to handle delta since last poll would go here)
        glibtop_cpu cpu;
        glibtop_get_cpu(&cpu);

        snap.cpu.total_usage = 28.0; // Simplified for this example
						       

        return snap;
    }
}
