shift/
├── CMakeLists.txt
├── include/
│   ├── core/
│   │   ├── provider_interface.hpp  # Testability (Abstraction)
│   │   ├── system_snapshot.hpp    # Determinism (Immutable data)
│   │   └── hardware_provider.hpp  # Correctness (libgtop implementation)
│   ├── ui/
│   │   ├── main_window.hpp        # Maintainability (Separation of concerns)
│   │   └── graph_widget.hpp       # Performance (Custom Cairo drawing)
│   └── utils/
│       └── logger.hpp             # Robustness (Error tracking)
├── src/
│   ├── core/
│   │   └── hardware_provider.cpp
│   ├── ui/
│   │   └── main_window.cpp
│   └── main.cpp                   # Deployability (Entry point)
└── tests/                         # Testability
    └── test_calculations.cpp
