# Producer-Consumer Problem Using Pthreads in C++

This project implements the Producer-Consumer problem using the Pthreads API in C++. The producer and consumer threads interact via a shared bounded buffer.

Measures total turnaround time of execution

Compilation

Use g++ to compile the program:
g++ -pthread -std=c++17 -o prodCon prodConPthreads.cpp

How to run:
Run the program and follow the interactive prompts:

./prodCon

Input Parameters:
You'll be asked to input the following:

Number of items to be produced and consumed
Producer sleep time (in tenths of a second)
Consumer sleep time (in tenths of a second)
Number of producer threads
Number of consumer threads

Example Run:

Enter number of items to produce/consume: 100
Enter producer sleep time (in tenths of a second): 1
Enter consumer sleep time (in tenths of a second): 2
Enter number of producers: 4
Enter number of consumers: 2

Sample Output
Producer 0 produced item 0
Producer 1 produced item 1000
Consumer 0 consumed item 0
Consumer 1 consumed item 1000
...
Total Turnaround Time: 5.32478 seconds

Developed using C++ by Taran Moses!