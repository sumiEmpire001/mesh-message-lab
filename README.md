# Mesh Message Lab — bounded C++11 mesh packet filter

Fixed-memory offline packet deduplication for Arduino Uno / ESP32 teaching. Supports 16 source sequence high-water marks, rejects malformed IDs, replayed sequences, exhausted TTL and capacity overflow. Invalid input or full storage latches a fault until reset. **No radio transport is included.**

Build and test: `cmake -S . -B build && cmake --build build && ctest --test-dir build --output-on-failure`.

**Hardware and security limitations:** Uno has 2 KB SRAM. No persistence, packet authentication, CRC, sequence rollover, radio driver, retransmission, congestion or secure routing. Do not use for safety-critical actuation. Hardware not tested.