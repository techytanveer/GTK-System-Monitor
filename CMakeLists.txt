cmake_minimum_required(VERSION 3.22)

# Deployability: Define project metadata used by CPack later
project(ShiftMonitor 
    VERSION 1.0.0 
    DESCRIPTION "A high-performance GTK4 System Monitor"
    LANGUAGES CXX
)

# Robustness: Enforce modern C++ standards and strict compiler warnings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

# Portability: Locate dependencies using PkgConfig
find_package(PkgConfig REQUIRED)
pkg_check_modules(DEPS REQUIRED 
    gtkmm-4.0 
    libadwaita-1 
    libgtop-2.0
)

# Maintainability: Keep headers and source organized
include_directories(include)

# Correctness: Explicitly list source files (avoids issues with globbing)
set(SOURCES
    src/main.cpp
    src/ui/main_window.cpp
    src/core/hardware_provider.cpp
)

# Performance: Enable optimizations for release builds
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(shift ${SOURCES})

# Linking: Apply the flags discovered by PkgConfig
target_link_libraries(shift 
    ${DEPS_LIBRARIES}
)
target_compile_options(shift PRIVATE ${DEPS_CFLAGS})

# --- INSTALLATION & DEPLOYABILITY (CPack) ---

include(GNUInstallDirs)

# Define where the binary goes after installation
install(TARGETS shift RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# CPack Configuration
set(CPACK_PACKAGE_NAME "shift-monitor")
set(CPACK_PACKAGE_VENDOR "ShiftProject")
set(CPACK_PACKAGE_CONTACT "yourname@example.com")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE") # Ensure you have a LICENSE file

# DEB specific (Ubuntu/Debian)
set(CPACK_GENERATOR "DEB;RPM")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtkmm-4.0-dev, libadwaita-1-dev, libgtop2-dev")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

# RPM specific (Fedora/CentOS)
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Applications/System")
set(CPACK_RPM_PACKAGE_REQUIRES "gtkmm4.0, libadwaita, libgtop2")

include(CPack)
