#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

struct process {
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
}p[20];

int n;

void sortByArrival() {
    struct process temp;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {

    int i, j, k = 0, r = 0, time = 0, tq, flag = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int idx;

    // read data
    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> p[i].arrival_time;
    }
    for (i = 0; i < n; i++) {
        cin >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
    }
    cin >> tq;

    // sort by arrival time
    sortByArrival();

    time = p[0].arrival_time; // time count
    int completed = 0; // completed tasks count
    queue<int> q1, q2; // level 1 queue, level 2 queue
    bool pre_is_q2 = false; // record preemption
    vector<bool> mark(20, false); // mark that whether the process has entered first queue


    while (completed != n) {

        //put processes into q1
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && mark[i] == false) {
                q1.push(i);
                mark[i] = true;
            }
        }

        // if q1 is empty
        if (q1.empty()) {
            // if q2 is also empty, check whether there will be incoming processes
            if (q2.empty()) {
                for (int i = 0; i < n; i++) {
                    if (p[i].remaining_time > 0) {
                        q1.push(i);
                        time = max(time, p[i].arrival_time);
                        mark[i] = true;
                        pre_is_q2 = false;
                    }
                }
                continue;
            }

            // if q1 is empty, execute q2
            idx = q2.front();
            p[idx].remaining_time--;
            time++;
            pre_is_q2 = true;

            // if process is done
            if (p[idx].remaining_time == 0) {
                p[idx].turnaround_time = time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                completed++;
                q2.pop();
            }
        }
        else {
            // preemption occured
            if (pre_is_q2) {
                idx = q2.front();
                q2.pop();
                q2.push(idx);
                pre_is_q2 = false;
            }

            // execute q1
            idx = q1.front();
            q1.pop();

            // if process is done
            if (p[idx].remaining_time <= tq) {
                time += min(p[idx].remaining_time, tq);
                p[idx].remaining_time = 0;
                p[idx].turnaround_time = time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                completed++;
            }
            // if process is not done, put it into q2
            else {
                p[idx].remaining_time -= tq;
                q2.push(idx);
                time += tq;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << p[i].waiting_time << " " << p[i].turnaround_time << "\n";
    }
    cout << total_waiting_time << "\n";
    cout << total_turnaround_time << "\n";

    return 0;

}