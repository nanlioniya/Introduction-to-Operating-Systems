#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
using namespace std;

struct process {
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int remaining_time;
    int waiting_time;
};

int main() {

    int n;
    struct process p[20];
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    // record completed status
    int is_completed[20];
    memset(is_completed,0,sizeof(is_completed));

    // read data
    cin>>n;
    for(int i = 0; i < n; i++) {
        cin>>p[i].arrival_time;
    }
    for(int i = 0; i < n; i++) {
        cin>>p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
    }


    int current_time = 0; // time count
    int completed = 0; // completed task count

    while(completed != n) {
        int idx = -1;
        int mn = 10000000;

        // find the process with shortest remaining time
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                // put process in queue
                if(p[i].remaining_time < mn) {
                    mn = p[i].remaining_time;
                    idx = i;
                }
                if(p[i].remaining_time == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].remaining_time;
                        idx = i;
                    }
                }
            }
        }

        // process found
        if(idx != -1) {

            // time pass
            p[idx].remaining_time -= 1;
            current_time++;
            
            if(p[idx].remaining_time == 0) {
                p[idx].turnaround_time = current_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        // process not found
        else {
             current_time++;
        }  
    }

    // output answer
    for (int i = 0; i < n; i++) {
        cout << p[i].waiting_time << " " << p[i].turnaround_time << "\n";
    }
    cout << total_waiting_time << "\n" << total_turnaround_time << "\n";
    return 0;
}