WARNING: Aura is a very early WIP project, shouldn't be used in production code for now!

![Aura's logo](./Logo.png)


Aura is a modern game engine built in C++26, designed from the ground up to balance safety, performance, and ergonomics. It provides developers with a robust foundation for building real‑time interactive experiences, while enforcing compile‑time guarantees that reduce runtime errors and improve maintainability.


🎯 Core Principles

- Safety → Strong compile‑time checks, explicit context management, and zero‑overhead abstractions to prevent common C++ pitfalls.
- Performance → Deterministic, cache‑friendly systems optimized for real‑time rendering, physics, and simulation.
- Ergonomics → Clear APIs, onboarding‑friendly documentation, and expressive patterns that make complex systems approachable.


🛠 Features

- Modern C++26 core with concepts and constexpr‑driven design.
- Cross‑platform rendering backend (Vulkan/Direct3D 12/Metal).
- Compile‑time safety framework to catch errors before runtime.


🚀 Getting Started

For now, Aura only compiles with the latest Windows 11, but builds for Linux and Darwin are planned and on the road!

Prerequisites:

- A 64-bits architecture and system.
- A GPU able to run D3D12, Vulkan and Metal, in their respective systems.
- A C++26‑capable compiler (Clang ≥ 22, GCC ≥ 16).
- CMake ≥ 4.1.2
- Latest Ninja.

Build Instructions

```bash
git clone https://github.com/verdeving/Aura.git
cd Aura
cmake -G Ninja -S . -B Build -D CMAKE_BUILD_TYPE=Debug -D AURA_ENABLE_TESTING=On
ninja -C Build
```


📚 Documentation

Aura provides doxygen-style comments so that you can generate the documentation with your own design locally on your computer.


📜 License

Aura is licensed under the GPL‑3.0 license. See LICENSE for details.


🌟 Vision

Aura is not just a game engine — it’s an experiment in what C++26 can offer when safety, performance, and developer experience are treated as first‑class citizens. The goal is to empower developers to build ambitious, real‑time worlds without sacrificing clarity or reliability.