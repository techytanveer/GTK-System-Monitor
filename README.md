# GTK-System-Monitor

Shift is a GTK based Linux System Monitor, the idea is learn how Engineer Pillars (**Correctness → Robustness → Security → Performance → Determinism → Maintainability → Portability → Testability → Deployability**) in systems design can be utilized in a project.

A high-performance Linux system monitor built with **C++20, gtkmm-4.0, and libadwaita**. <ins>Shift</ins> is designed with a strict adherence to core engineering principles to ensure reliability and clarity.

# 🛠 Engineering Pillars
## 1. Correctness
<ins>Shift</ins> ensures data accuracy by utilizing *libgtop2* to interface directly with the Linux kernel's */proc* filesystem. CPU usage is calculated via precise delta-tracking between polling intervals, avoiding the common mistake of displaying "boot-time averages."

## 2. Robustness
The application employs a multi-threaded architecture. The hardware-polling engine runs on a dedicated worker thread, ensuring that even if the system is under extreme load, the UI remains responsive. We use *Glib::Dispatcher* for thread-safe communication between the backend and the GTK main loop.

## 3. Security
*Memory Safety:* 
Built using Modern C++ (Smart Pointers) to eliminate manual memory management and prevent leaks or dangling pointers.

*Minimal Privileges:* 
Shift operates entirely in user-space, requiring no *sudo* or elevated permissions to read system stats.

## 4. Performance
By using *std::this_thread::sleep_for*, we maintain a constant 1Hz update frequency. This keeps <ins>Shift</ins>'s own CPU footprint at <1% on modern systems, ensuring the monitor doesn't become the problem it's trying to track.

## 5. Determinism
State transitions are predictable. The UI only updates when the dispatcher receives a signal, and data snapshots are protected by *std::mutex* to prevent race conditions or "jittery" data displays.

## 6. Maintainability
The codebase follows a strict Interface-based Design.

*IDataProvider:* 
An abstract interface allowing for easy swapping of data sources (e.g., switching from *libgtop* to a custom */proc* parser).

*Clear Hierarchy:* 
Logical separation between *Core* (logic) and *UI* (presentation).

## 7. Portability
While optimized for Ubuntu 24.04 (GNOME), <ins>Shift</ins> uses *PkgConfig* in its build system to dynamically locate dependencies, making it portable across various Linux distributions with GTK4 support.

## 8. Testability
The logic for byte-conversion and CPU percentage calculation is decoupled from the GTK widgets, allowing for headless unit testing of the core provider logic.

## 9. Deployability
<ins>Shift</ins> is ready for distribution. It includes a *CMake* configuration compatible with CPack, enabling the generation of *.deb* & *.rpm* packages for easy installation on Debian-based systems.

# 🚀 Getting Started

Prerequisites

**Compiler:** GCC 13+ or Clang 16+
**Libraries:** libgtkmm-4.1-dev, libadwaita-1-dev, libgtop2-dev

## Installation

mkdir build && cd build
cmake ..
make -j$(nproc)
./shift

# 📸 Preview
**CPU Usage:** Live delta-based percentage tracking. 
**Memory Usage:** Real-time GiB consumption vs. System Total.

# Project Structure

* Shift
 - CMakeLists.txt
 - include
  * core
   - proivder_interface.hpp
   - system_snapshot.hpp
   - hardware_provider.hpp
  * ui
   - main_window.hpp
   - graph_widget.hpp
  * utils
   - logger.hpp
 - src
 - main.cpp
  * core
   - hardware_provider.cpp
  * ui
   _ main_window.cpp
 * tests
* GO

* Item 1
* Item 2
  * Nested Item A
  * Nested Item B
- Item 3
- Item 4


1. First item
2. Second item
1. Third item (the '1.' here will render as '3.')
   1. Nested ordered item (indent with at least four spaces)
   2. Another nested ordered item
4. Fourth item
