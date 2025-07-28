#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority;
    int start_time = -1;
    int finish_time = 0;
    int remaining;
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

bool compareBurst(const Process &a, const Process &b) {
    return a.burst < b.burst;
}

bool comparePriority(const Process &a, const Process &b) {
    return a.priority < b.priority;
}

void calculateAndPrintStats(const std::vector<Process> &completed, int total_time, int cpu_busy_time) {
    double total_turnaround = 0, total_wait = 0, total_response = 0;

    for (const auto &p : completed) {
        int turnaround = p.finish_time - p.arrival;
        int wait = turnaround - p.burst;
        int response = p.start_time - p.arrival;

        total_turnaround += turnaround;
        total_wait += wait;
        total_response += response;
    }

    int n = completed.size();
    std::cout << "Number of processes: " << n << "\n";
    std::cout << "Total elapsed time: " << total_time << "\n";
    std::cout << "Throughput: " << std::fixed << std::setprecision(2) << (double)n / total_time << " processes/unit time\n";
    std::cout << "CPU Utilization: " << (100.0 * cpu_busy_time / total_time) << "%\n";
    std::cout << "Average Waiting Time: " << total_wait / n << "\n";
    std::cout << "Average Turnaround Time: " << total_turnaround / n << "\n";
    std::cout << "Average Response Time: " << total_response / n << "\n";
}

void simulateFIFO(std::vector<Process> processes) {
    std::sort(processes.begin(), processes.end(), compareArrival);
    int time = 0, cpu_busy_time = 0;
    std::vector<Process> completed;

    for (auto &p : processes) {
        if (time < p.arrival)
            time = p.arrival;

        p.start_time = time;
        time += p.burst;
        p.finish_time = time;
        completed.push_back(p);
        cpu_busy_time += p.burst;

        if (completed.size() == 500) break;
    }
    std::cout << "\n--- FIFO Scheduling ---\n";
    calculateAndPrintStats(completed, time, cpu_busy_time);
}

void simulateSJF(std::vector<Process> processes) {
    std::sort(processes.begin(), processes.end(), compareArrival);
    int time = 0, cpu_busy_time = 0, i = 0;
    std::vector<Process> ready, completed;

    while (completed.size() < 500) {
        while (i < processes.size() && processes[i].arrival <= time) {
            ready.push_back(processes[i]);
            ++i;
        }
        if (ready.empty()) {
            time = processes[i].arrival;
            continue;
        }

        std::sort(ready.begin(), ready.end(), compareBurst);
        Process p = ready.front();
        ready.erase(ready.begin());

        p.start_time = time;
        time += p.burst;
        p.finish_time = time;
        cpu_busy_time += p.burst;
        completed.push_back(p);
    }
    std::cout << "\n--- SJF (Non-preemptive) Scheduling ---\n";
    calculateAndPrintStats(completed, time, cpu_busy_time);
}

void simulatePriorityPreemptive(std::vector<Process> processes) {
    std::sort(processes.begin(), processes.end(), compareArrival);
    int time = 0, i = 0, cpu_busy_time = 0;
    std::vector<Process> completed;
    auto cmp = [](Process a, Process b) {
        return a.priority > b.priority;
    };
    std::priority_queue<Process, std::vector<Process>, decltype(cmp)> pq(cmp);

    while (completed.size() < 500) {
        while (i < processes.size() && processes[i].arrival <= time) {
            processes[i].remaining = processes[i].burst;
            pq.push(processes[i]);
            ++i;
        }

        if (pq.empty()) {
            if (i < processes.size())
                time = processes[i].arrival;
            continue;
        }

        Process p = pq.top(); pq.pop();
        if (p.start_time == -1)
            p.start_time = time;

        ++time;
        --p.remaining;
        ++cpu_busy_time;

        if (p.remaining > 0) {
            pq.push(p);
        } else {
            p.finish_time = time;
            completed.push_back(p);
        }
    }

    std::cout << "\n--- Priority (Preemptive) Scheduling ---\n";
    calculateAndPrintStats(completed, time, cpu_busy_time);
}

int main() {
    std::ifstream infile("datafile1.txt");
    std::vector<Process> processes;
    int arrival, burst, priority, pid = 0;
    std::string header;
    std::getline(infile, header);

    while (infile >> arrival >> burst >> priority) {
        processes.push_back({pid++, arrival, burst, priority, -1, 0, burst});
    }

    simulateFIFO(processes);
    simulateSJF(processes);
    simulatePriorityPreemptive(processes);

    return 0;
}
