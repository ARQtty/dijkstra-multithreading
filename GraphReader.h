//
// Created by iria on 11.11.2019.
//
#pragma once
#include <string>
#include <vector>

using namespace std;

class GraphReader {
private:
    string filename;
    int toInt(string s);
    void readNums(string s, vector<int>& nums);
public:
    void read_adj_list(string filename, vector<vector<pair<int, int>>>& adj_list);
    void read_edge_list(string filename, vector<pair<int, int>>& edges);
};
