//
// Created by iria on 13.11.2019.
//

#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include "Timer.h"
#define MAX_INT 999999

using namespace std;

mutex dijkstra_min_dist;



void dijkstra_sync(const vector<vector<pair<int, int>>>& adj_list, int from, vector<int>& dists){
    int vs = adj_list.size();
    dists.assign(vs, MAX_INT);
    dists[from] = 0;
    vector<bool> used;
    used.assign(vs, false);
    int curr_v;

    Timer timer = Timer();

    for (int i=0; i<vs; i++){
        // search unused
        curr_v = -1;

        for (int v=0; v<vs; v++) {
            if (!used[v] && (curr_v == -1 || dists[v] < dists[curr_v])) {
                curr_v = v;
            }
        }
        // have visited all reachable vertexes
        if (dists[curr_v] == MAX_INT){
            return;
        }

        used[curr_v] = true;

        int to, weight;
        // Search least path
        for (int j=0; j<adj_list[curr_v].size(); j++){
            to = adj_list[curr_v][j].first;
            weight = adj_list[curr_v][j].second;
            if (dists[curr_v] + weight < dists[to]){
                // Relax
                dists[to] = dists[curr_v] + weight;
            }
        }
    }
}



void search_min_f_dijkstra(vector<int>& array, vector<bool>& conditional, int from, int to, int& min_dist){
    int local_min = MAX_INT;
    for (int i=from; i<=to; i++){
        if (array[i] < local_min && !conditional[i]){
            local_min = array[i];
        }
    }
    dijkstra_min_dist.lock();
    if (local_min < min_dist){
        min_dist = local_min;
    }
    dijkstra_min_dist.unlock();
}
void search_min(vector<int>& array, vector<bool>& conditional, int& min_dist){
    int num_workers = 8;
    vector<thread> threads;

    int a, b;
    int step = array.size() / num_workers;
    for (int w=0; w<num_workers; w++){
        a = w*(step+1);
        b = min(a+step, (int)array.size()-1);
        threads.push_back(thread(search_min_f_dijkstra, ref(array), ref(conditional), a, b, ref(min_dist)));
    }
    for (auto & thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}


void dijkstra_async(const vector<vector<pair<int, int>>>& adj_list, int from, vector<int>& dists, Timer& measure_min){
    int vs = adj_list.size();
    dists.assign(vs, MAX_INT);
    dists[from] = 0;
    vector<bool> used;
    used.assign(vs, false);
    int curr_v;

    Timer timer = Timer();

    for (int i=0; i<vs; i++){
        // search unused
        search_min(dists, used, curr_v);

        // have visited all reachable vertexes
        if (dists[curr_v] == MAX_INT){
            return;
        }

        used[curr_v] = true;

        int to, weight;
        // Search least path
        for (int j=0; j<adj_list[curr_v].size(); j++){
            to = adj_list[curr_v][j].first;
            weight = adj_list[curr_v][j].second;
            if (dists[curr_v] + weight < dists[to]){
                // Relax
                dists[to] = dists[curr_v] + weight;
            }
        }
    }
}