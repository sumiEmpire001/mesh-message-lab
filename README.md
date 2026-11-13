# Mesh Message Lab — C++11 bounded frame codec

A fixed-size mesh-message framing exercise for Arduino/ESP32. Implements versioned binary frames, CRC-16-CCITT integrity, bounded payloads (48 bytes), TTL-limited forwarding and a 16-entry duplicate cache. Malformed frames are rejected before copying into application state.

## Test
```sh
cmake -S . -B build && cmake --build build
ctest --test-dir build --output-on-failure
```

The ArduinoSerial sketch performs a serial-only codec demonstration; it does **not** connect a radio. CRC detects accidental corruption but provides **no authentication, confidentiality or replay protection**. The cache evicts older entries and sequence-number rollover may admit repeats. Real ESP-NOW, LoRa or Wi-Fi mesh needs authenticated encryption, persistent anti-replay counters, airtime budgeting, collision handling, link monitoring, routing policy, regulatory compliance and hardware tests. The example include path is sketch-layout dependent; host CI does not compile board firmware. No prior Python code existed to preserve.
