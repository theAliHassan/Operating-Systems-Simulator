# Operating-system shell simulator

A Linux console program, written in C++ for an Operating Systems course (March 2022). It imitates a small operating system: after you start it with a RAM size, disk size and core count, it shows a menu of "programs" and runs them. It is a teaching simulation, not a real or real-time operating system.

## What is in it

| Menu item | What it does |
|---|---|
| New file, copy, move, delete (1–4) | Small file operations (the copy, move and delete steps run through shell commands) |
| Time and calendar (5, 6) | Shows the current time and a calendar |
| Chat (7) | Message passing between two parts of the program through a Unix pipe |
| Scheduling algorithm (8) | First-come-first-served (FCFS) scheduling for four processes, with completion, turnaround and waiting times |
| Multitasking, average calculator (9, 11) | Worker threads with `pthread`, a mutex and a condition variable |
| Resource allocation | A process control block (PCB) per process, with fixed RAM and stack sizes checked against the RAM you started with |
| Calculator, Pacman, Minesweeper, Chess (10, 12–14) | Console programs launched from the menu |

Files: `link.cpp` is the main program; `Pacman.cpp`, `Minesweeper.cpp`, `Chess.cpp`, `Calendar.cpp` and `Time.cpp` are the programs it includes; the `.sh` scripts and `newchess.txt` are helpers.

## Build and run

Needs Linux with `gnome-terminal`, because some menu items open a second terminal.

```bash
g++ -pthread -o myOS link.cpp
./myOS 1024 500 4        # RAM, HDD, cores: the three numbers are shown at the top of the menu
```

## Status and limits

- **Compile-checked only.** I confirmed that it compiles with `g++ -pthread` (Apple clang on macOS, C++11 and C++17 modes). I have not run it on Linux again, so the menu items that open new terminals are untested.
- **Only FCFS scheduling is implemented.** There is no round-robin, priority scheduling, deadlock handling, swapping or paging, and no real-time scheduling. The earlier repository description claimed more than this.
- Resource figures (RAM and stack per process) are fixed numbers, not measured.
- The original upload did not build: `Minesweeper.cpp` included a file that was never committed (`MinesweeperNewTerminal.cpp`). I removed that include, renamed a variable called `function` that clashed with `std::function` in modern C++, and removed the two compiled binaries (`myOS`, `mylinknew`), which cannot be verified from source.
- No automated tests, and course-project code quality.
