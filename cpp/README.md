# MeshQueue C++11 reference

Bounded store-and-forward frame queue with TTL, duplicate detection, fixed-size payloads and deterministic capacity limits. No actual radio transport, cryptographic authentication or persistent replay protection.

Build on a host: `cmake -S cpp -B build && cmake --build build && ctest --test-dir build --output-on-failure`.

The header is standard C++11 and suitable for Arduino Uno / ESP32 algorithm integration, but no device firmware or GPIO sketch is included. For board use, supply validated sensor/input data, watchdogs and fail-safe outputs. Hardware and board toolchain builds are unverified.
