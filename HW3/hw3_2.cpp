#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <queue> 
using namespace std;

struct process {
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
};

bool compare1(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}


int main() {

    int n;
    int tq;
    struct process p[20];
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int idx;

    cin >> n; // number of processes

    for (int i = 0; i < n; i++) {
        cin >> p[i].arrival_time;
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
    }
    cin >> tq; // time quantum

    // sort the processes according to their arrival time
    sort(p, p + n, compare1);

    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    vector<int> mark(20, 0);
    mark[0] = 1;

    while (completed != n) {

        // pick the first element
        idx = q.front();
        q.pop();

        if (p[idx].remaining_time == p[idx].burst_time) {
            current_time = max(current_time, p[idx].arrival_time);
        }

        if (p[idx].remaining_time - tq > 0) {
            p[idx].remaining_time -= tq;
            current_time += tq;
        }
        else {
            current_time += p[idx].remaining_time;
            p[idx].remaining_time = 0;
            completed++;

            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
        }

        // put processes that has not completed and arrive before previous process quit using CPU
        for (int i = 1; i < n; i++) {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }
        // if the current process not completed, add it to end of queue
        if (p[idx].remaining_time > 0) {
            q.push(idx);
        }

        // current queue is currently empty, but there is gonna be incoming processes
        if (q.empty()) {
            for (int i = 1; i < n; i++) {
                if (p[i].remaining_time > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    // output answer
    for (int i = 0; i < n; i++) {
        cout << p[i].waiting_time << " " << p[i].turnaround_time << "\n";
    }
    cout << total_waiting_time << "\n" << total_turnaround_time << "\n";
    return 0;

}
