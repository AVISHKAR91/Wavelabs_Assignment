#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

int network_delay_time(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int, int>>> graph(n);
    for (auto& time : times) {
        int ui = time[0] - 1;
        int vi = time[1] - 1;
        int wi = time[2];
        graph[ui].emplace_back(vi, wi);
    }
    
    // Initialize the distance array
    vector<int> dist(n, INT_MAX);
    dist[k-1] = 0;
    
    // Initialize the priority queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, k-1);
    
    // Run Dijkstra's algorithm
    while (!pq.empty()) {
        auto [d, ui] = pq.top(); pq.pop();
        if (d > dist[ui]) continue;
        for (auto [vi, wi] : graph[ui]) {
            if (dist[ui] + wi < dist[vi]) {
                dist[vi] = dist[ui] + wi;
                pq.emplace(dist[vi], vi);
            }
        }
    }
    
    // Find the maximum distance
    int max_dist = *max_element(dist.begin(), dist.end());
    return max_dist != INT_MAX ? max_dist : -1;
}

int main() {
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    int n = 4, k = 2;
    int result = network_delay_time(times, n, k);
    cout << result << endl; 
    return 0;
}
