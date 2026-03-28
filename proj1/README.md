# Process Management

## Overview

This poject implement a proccess managment system that simulates how an operating system performs process sheduling,
resource allocation and deadloack dectection. The system supports both single-core and multi-core simulations with three different scheduling algorithms.

## Features

- **Process Management**: Full Process Control Block (PCB) management
- **Resource Management**: Request and release resources with proper allocation and waiting queues
- **Three Scheduling Algorithms**:
  - First-Come, First-Served (FCFS)
  - Round Robin (RR) with configurable time quantum
  - Priority-based Preemptive Scheduling
- **Multi-core Simulation**: Parallel execution using OpenMP threads
- **Deadlock Detection**: Identifies deadlocked processes and blocked processes
- **Comprehensive Logging**: Detailed output for debugging and analysis

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

## Prerequisites

- GCC compiler with OpenMP support
- Make utility
- Linux/Unix environment (or WSL on Windows)

## Build

```bash
# Standard build
gcc -fopenmp -o schedule_processes manager.c proc_loader.c proc_parser.c proc_gen.c logger.c -lm

# With debug output
gcc -fopenmp -DDEBUG -o schedule_processes manager.c proc_loader.c proc_parser.c proc_gen.c logger.c -lm

# With Makefile
make
make DEBUG=-DDEBUG_MNGR
```

## Usage

```
./schedule_processes <num_threads> <data> <scheduler> <time_quantum>
```

| Argument | Description |
|---|---|
| `num_threads` | Number of simulated CPU cores (OpenMP threads) |
| `data` | Path to a `.list` process file, or `generate` for random generation |
| `scheduler` | `0` = Priority, `1` = Round Robin, `2` = FCFS |
| `time_quantum` | Number of instructions per timeslice (used by Round Robin only) |

## Output Files

For each thread or process, two files are written during execution:

| File | Contents |
|---|---|
| `thr<id>.log` | Internal scheduling events (acquire, release, wakeup) |
| `thr<id>.out` | Full execution trace including queue states |

When the `DEBUG` flag is set, all output is mirrored to stdout.
