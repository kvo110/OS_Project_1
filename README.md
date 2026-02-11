# Process Scheduling Simulation

**Operating Systems – Project 1**

This project simulates how an operating system schedules CPU processes using different scheduling algorithms. The program reads process data from a file, simulates CPU scheduling behavior, and displays execution order and performance metrics such as waiting time and turnaround time.

The project is written in **C++** and runs entirely in the terminal.

---

## Features

- Reads process information from a text file
- Implements two CPU scheduling algorithms:
  - First-Come, First-Served (FCFS)
  - Round Robin (RR)
- Displays a text-based Gantt chart
- Calculates:
  - Waiting Time (WT)
  - Turnaround Time (TAT)
  - Average WT and TAT
  - CPU Utilization
- Menu-driven interface for easy testing

---

## Files Included

- `main.cpp`
  Contains the implementation of the scheduling algorithms and program logic.

- `processes.txt`
  Input file containing process data (PID, arrival time, burst time, priority).

- `README.md`
  Project overview and instructions.

- `Project_Report.pdf`
  Written report explaining the implementation, results, and challenges
  (generated separately).

---

## Input File Format

Each process in the input file should be listed on its own line using the following format:

Header lines are ignored automatically by the program.

---

## How to Compile and Run

Compile the program using:
g++ -std=c++17 -Wall main.cpp -o sched

Run the program with:
./sched

By default, the program reads input from `processes.txt`.

---

## How to Use the Program

After running the program, a menu will appear:

- Select **1** to run First-Come, First-Served scheduling
- Select **2** to run Round Robin scheduling
  - You will be prompted to enter a time quantum
- Select **3** to exit the program

After execution, the program displays:

- A Gantt chart showing execution order
- A table of process statistics
- Average waiting and turnaround times
- CPU utilization

---

## Scheduling Algorithms

### First-Come, First-Served (FCFS)

Processes are executed in the order they arrive in the system. Once a process begins execution, it runs until completion. This algorithm is simple but can result in long waiting times for shorter processes.

### Round Robin (RR)

Each process is given a fixed time quantum. If a process does not finish within its time slice, it is placed back into the ready queue. This approach improves fairness and is commonly used in time-sharing systems.

---

## Notes

- Priority values are read and stored but are not directly used in FCFS or Round Robin.
- CPU idle time is explicitly shown in the Gantt chart when applicable.
- The program can be extended to support additional scheduling algorithms such as SJF or Priority Scheduling.

---

## Author

Kenny Vo
Operating Systems – Spring 2026
