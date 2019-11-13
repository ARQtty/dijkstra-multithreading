//
// Created by iria on 11.11.2019.
//

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include "GraphReader.h"

using namespace std;

int GraphReader::toInt(string s) {
    return atoi(s.c_str());
}

void GraphReader::readNums(string s, vector<int>& nums){
    nums.clear();
    stringstream ss(s);
    string item;
    while (getline(ss, item, ' ')) {
        nums.push_back(GraphReader::toInt(item));
    }
}


void GraphReader::read_adj_list(string filename, vector<vector<pair<int, int>>>& adj_list){
    ifstream file("../" + filename);
    if (!file){
        cout << "File not opened" << endl;
        throw invalid_argument("Cant open file with this name");
    }
    int numV;
    int numE;

    string line = "";
    getline(file, line); // num edges and vertexes

    vector<int> numbers;
    readNums(line, numbers);
    numE = numbers[0];
    numV = numbers[1];

    adj_list.resize(numV);

    int from, to, weight;
    for (int i=0; i<numE; i++){
        line = "";

        getline(file, line);
        readNums(line, numbers);

        from = numbers[0];
        to = numbers[1];
        weight = numbers[2];

        adj_list[from-1].push_back(make_pair(to-1, weight));
        adj_list[to-1].push_back(make_pair(from-1, weight));
    }
}

void GraphReader::read_edge_list(string filename, vector<pair<int, int>> &edges) {
    cout << "Deprecated method GraphReader::read_edge_list()" << endl;
    ifstream file("../" + filename);
    if (!file){
        cout << "File not opened" << endl;
        return;
    }
    int numV;
    int numE;

    string line = "";
    getline(file, line); // num edges and vertexes

    vector<int> numbers;
    readNums(line, numbers);
    numE = numbers[0];
    numV = numbers[1];

    for (int i=0; i<numE; i++){
        line = "";

        getline(file, line);
        readNums(line, numbers);

        int from = numbers[0];
        int to = numbers[1];

        edges.push_back(make_pair(from, to));
    }
}
