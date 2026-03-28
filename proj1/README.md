# Process Management

---
## Overview

This poject implement a proccess managment system that simulates how an operating system performs process sheduling,
resource allocation and deadloack dectection. The system supports both single-core and multi-core simulations with three different scheduling algorithms.

---

## Project Structure

```
proj1
   ├── data
   │   ├── process1.list
   │   └── process2.list
   ├── Makefile
   ├── README.md
   ├── run.sh
   └── src
       ├── logger.c - Logging functions
       ├── logger.h - Logging definations
       ├── manager.c - Core scheduling logic
       ├── manager.h
       ├── proc_gen.c
       ├── proc_gen.h
       ├── proc_loader.c
       ├── proc_parser.c
       ├── proc_parser.h
       ├── proc_structs.h - Data structures (PCB, queues, resources)
       └── proc_syntax.h
```
