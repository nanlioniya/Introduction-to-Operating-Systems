#include<iostream>
#include<queue>
#include<vector>
#include<unordered_map>
using namespace std;

int frame_num;
int input_len;
int input[100];
vector<int> frame;

bool check_in_frame(int num) {
	for (int i = 0; i < frame.size(); i++) {
		if (num == frame[i]) {
			return true;
		}
	}
	return false;
}


int main() {
	
	cin >> frame_num >> input_len;
	for (int i = 0; i < input_len; i++) {
		cin >> input[i];
	}

	int pf_FIFO = 0, pf_LRU = 0, pf_LFU = 0;

	//FIFO
	queue<int> q;
	for (int i = 0; i < input_len; i++) {
		int cur = input[i];
		if (check_in_frame(cur)) {
			continue;
		}
		else {
			pf_FIFO++;
			if (frame.size()==frame_num) {
				int replace = q.front();
				for (int i = 0; i < frame_num; i++) {
					if (replace == frame[i]) {
						frame[i] = cur;
					}
				}
				q.pop();
				q.push(cur);
			}
			else {
				frame.push_back(cur);
				q.push(cur);
			}
		}
	}

	//LRU
	frame.clear();

    // To store least recently used indexes
    // of pages.
    unordered_map<int, int> indexes;

    // Start from initial page
    for (int i = 0; i < input_len; i++){
        int cur = input[i];
        // Check if the set can hold more pages
        if (frame.size() < frame_num){
            // Insert it into set if not present
            // already which represents page fault
            if (!check_in_frame(cur)){
                frame.push_back(cur);
                // increment page fault
                pf_LRU++;
            }

            // Store the recently used index of
            // each page
            indexes[cur] = i;
        }

        // If the set is full then need to perform lru
        // i.e. remove the least recently used page
        // and insert the current page
        else
        {
            // Check if current page is not already
            // present in the set
            if (!check_in_frame(cur)){
                // Find the least recently used pages
                // that is present in the set
                int lru = INT_MAX, val;
                for (int j=0; j<frame_num; j++){
                    int tmp = frame[j];
                    if (indexes[tmp] < lru)
                    {
                        lru = indexes[tmp];
                        val = tmp;
                    }
                }

                // Remove the indexes page
                for (int i = 0; i < frame_num; i++) {
                    if (val == frame[i]) {
                        frame[i] = cur;
                    }
                }
                // Increment page faults
                pf_LRU++;
            }

            // Update the current page index
            indexes[cur] = i;
        }
    }

    //LFU
    frame.clear();
    indexes.clear();

    // To store least recently used indexes
    // of pages.

    // Start from initial page
    for (int i = 0; i < input_len; i++) {
        int cur = input[i];
        // Check if the set can hold more pages
        if (frame.size() < frame_num) {
            // Insert it into set if not present
            // already which represents page fault
            if (!check_in_frame(cur)) {
                frame.push_back(cur);
                // increment page fault
                pf_LFU++;
            }

            // Store the recently used index of
            // each page
            indexes[cur]++;
        }

        // If the set is full then need to perform lru
        // i.e. remove the least recently used page
        // and insert the current page
        else
        {
            // Check if current page is not already
            // present in the set
            if (!check_in_frame(cur)) {
                // Find the least recently used pages
                // that is present in the set
                int lru = INT_MAX, val;
                for (int j = 0; j < frame_num; j++) {
                    int tmp = frame[j];
                    if (indexes[tmp] < lru){
                        lru = indexes[tmp];
                        val = tmp;
                    }
                }

                // Remove the indexes page
                auto it = find(frame.begin(), frame.end(), val);
                frame.erase(it);
                frame.push_back(cur);
                indexes.erase(val);
                
                // Increment page faults
                pf_LFU++;
            }

            // Update the current page index
            indexes[cur]++;
        }
    }


	
	cout << pf_FIFO << "\n";
	cout << pf_LRU << "\n";
	cout << pf_LFU << "\n";
		
	return 0;
}