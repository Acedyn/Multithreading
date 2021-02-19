# Multithreading Exercices

Exercices from ARTFX's workshop on multithreading

## How to build

```powershell
cd path/to/build_directory
cmake path/to/repository -G "generator_name" -D MULTITHREADING_OUTPUT_DIR="path/to/binary_directory"
```

## Content

- 01_threadManagement : Basics on how to use std::thread
- 02_shareData : How to use std::mutex to prevent race conditions
- °3_synchronizeOperations : Simulation of a restaurant with one thread per worker talking to each other
