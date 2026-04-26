# Player

Develop and test your Othello player. Two workflows:
- Build your player as a Docker image for use in matches run by `te-local-match-runner`
- Run locally in process mode against a random opponent via the test harness (no Docker required)

## Prerequisites

- MPI (`mpicc`, `mpirun`) -- see the Software Requirements section on STEMLearn
- Docker (for building the player image) -- E.g., [Rancher Desktop](https://docs.rancherdesktop.io/getting-started/installation/), [Docker Desktop](https://docs.docker.com/desktop/), or [Docker Engine](https://docs.docker.com/engine/install/)

## Project structure

```

├── te-local-match-runner
│   ...
├── te-local-test-harness
│   ...
└── 12345678-rw314-projects/proj2 # This project
    ├── .env
    ├── Makefile
    ├── my_player
    │   ├── Dockerfile
    │   └── src
    │       ├── comms.h           # Communication interface (do not modify)
    │       └── player.c          # Your player implementation
    └── README.md
```

## Building the Docker image

Build your player as a Docker image:

```sh
make image
```

This produces `${REGISTRY}/my-player:${VERSION}` (default: `localhost/my-player:1.0.0`).

To play a Docker match, go to `te-local-match-runner` and execute `make run` in (see its README).

## Process mode

Runs your player locally against a random opponent using the test harness -- no Docker required.

### Setup

Requires `te-local-test-harness` (default: `../../te-local-test-harness`). To use a different location, update `HARNESS_DIR` in `.env`.

### Run a match

```sh
make run
```

This compiles the test harness and your player, links them together, and runs with `mpirun`.
Logs are written to `./logs/my_player.log`.

### Clean up

```sh
make clean-build
```

## Configuration

All configuration is in `.env`:

| Variable         | Default                     | Description                        |
|------------------|-----------------------------|------------------------------------|
| `VERSION`        | 1.0.0                       | Your player image version          |
| `REGISTRY`       | localhost                   | Container image registry           |
| `HARNESS_DIR`    | ../../te-local-test-harness | Path to the test harness           |

## Make targets

| Target                 | Description                           |
|------------------------|---------------------------------------|
| `make`                 | Build the player Docker image         |
| `make image`           | Build the player Docker image         |
| `make run`             | Process mode: compile and run locally |
| `make build`           | Process mode: compile only (no run)   |
| `make clean`           | Remove the player Docker image        |
| `make clean-build`     | Remove process mode build artifacts   |
| `make clean-logs`      | Remove log files                      |
