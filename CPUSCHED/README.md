# CPU Scheduling Simulation Project

This project simulates a CPU scheduler handling 500 simulated processes. It implements and evaluates three scheduling algorithms:
    FIFO
    SJF (withou preemption)
    Priority (with preemption)

Each simulated process has the following parameters:

<Process ID, Arrival Time, CPU Burst Length, Priority>

Requirements
    C++17 or higher
	A C++ compiler (e.g., g++, clang++)
	datafile1.txt — input file containing process data

File Structure

.
├── cpu_scheduler_simulation.cpp   # Main simulation source code
├── datafile1.txt                  # Input file with 500+ processes
└── README.md                      # This documentation

Input File Format

The file datafile1.txt must have tab-separated columns in the following format:

Arrival time    CPU Burst length    Priority
10              22                  1
68              12                  6
...

How to Compile and Run

1. Compile
g++ -std=c++17 -o scheduler ./CPUSCHED/cpuScheduler.cpp

2. Run
./CPUSCHED/scheduler

3. Expected Output

The program prints scheduling statistics for each algorithm to the console:

--- FIFO Scheduling ---
Number of processes: 500
Total elapsed time: 14744
Throughput: 0.03 processes/unit time
CPU Utilization: 71.61%
Average Waiting Time: 17.88
Average Turnaround Time: 39.00
Average Response Time: 17.88

--- SJF (Non-preemptive) Scheduling ---
Number of processes: 500
Total elapsed time: 14744
Throughput: 0.03 processes/unit time
CPU Utilization: 71.61%
Average Waiting Time: 14.24
Average Turnaround Time: 35.36
Average Response Time: 14.24

--- Priority (Preemptive) Scheduling ---
Number of processes: 500
Total elapsed time: 14744
Throughput: 0.03 processes/unit time
CPU Utilization: 71.61%
Average Waiting Time: 23.48
Average Turnaround Time: 44.60
Average Response Time: 9.49

Statistics Explained
	Total Elapsed Time — Time until the 500th process completes.
	Throughput — Number of processes completed per unit time.
	CPU Utilization — Percentage of time the CPU was busy.
	Average Waiting Time — Average time processes spent waiting.
	Average Turnaround Time — Average total time from arrival to finish.
	Average Response Time — Average time from arrival to first CPU access.

Notes
	Only the first 500 processes from the file are considered.
	Preemptive priority scheduling uses a min-heap (priority queue) to dynamically switch between processes based on priority.

Developed using C++ by Taran Moses!