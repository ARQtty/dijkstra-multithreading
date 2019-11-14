#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <unistd.h>
#include "Timer.h"
#include "GraphReader.h"
#include "dijkstra.h"

using namespace std;

int main(){
    // Params
    Timer timer = Timer();
    GraphReader csv_reader = GraphReader();
    auto global_start_time = chrono::system_clock::now();
    vector <thread> threads;
    // weighted adj list
    vector <vector<pair<int, int>>> adj_list;

    // Get number of workers from argv
    int workers = 2;


    timer.log_time("Start reading csv data");
    csv_reader.read_adj_list("./datafile.txt", adj_list);
    timer.log_time("Success read csv data");


    vector<int> closest_dists_sync;
    int from = 0;
//    timer.log_time("Start dijkstra sync");
//    dijkstra_sync(adj_list, from, closest_dists_sync);
//    timer.log_time("Finish dijkstra sync");


    vector<int> closest_dists_async;
    timer.log_time("Start dijkstra async");
    dijkstra_async(adj_list, from, closest_dists_async, timer);
    timer.log_time("Finish dijkstra async");


    cout << "Kernels: " << thread::hardware_concurrency() << endl;

    return 0;
}
