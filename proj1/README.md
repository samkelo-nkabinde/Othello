# Process Management

---
## Overview

This poject implement a proccess managment system that simulates how an operating system performs process sheduling,
resource allocation and deadloack dectection. The system supports both single-core and multi-core simulations with three different scheduling algorithms.

---
## Features


## Project Structure

```.
   ├── data
   │   ├── process1.list
   │   └── process2.list
   ├── Makefile
   ├── README.md
   ├── run.sh
   └── src
       ├── logger.c         // Logs system events to files
       ├── logger.h         // Definition of logger.c functions
       ├── manager.c        // Core scheduling logic
       ├── manager.h        // Defination of manager.c fucntions and data struture
       ├── proc_gen.c       // Generates random test processes
       ├── proc_gen.h       // Definition of proc_gen.c functions
       ├── proc_loader.c    // Manages OS process and resource loading
       ├── proc_parser.c    // Parses process configuration files
       ├── proc_parser.h    // Defination of proc_parser.c
       ├── proc_structs.h   // Defines OS data structures
       └── proc_syntax.h    // Defines parser's language keywords
```
