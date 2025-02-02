#include <iostream>
#include <fstream>
#include <vector>
#include "csv.h"
#include <tuple>
#include <pthread.h>

using Data =  std::tuple<std::vector<double>,std::vector<double>>;

Data ReadCSV(const std::string& filename) {
    io::CSVReader<2> in(filename); // 2 columns per row
    in.read_header(io::ignore_extra_column, "X", "Y"); // You can specify header names if needed
    std::vector<double> x, y; 
    double col1, col2;
    while (in.read_row(col1, col2)) {
        x.push_back(col1);
        y.push_back(col2);
    }
}


int main(char* argv[], int argc) {
    Data trainingData  = ReadCSV("train.csv");
    Data testData  = ReadCSV("test.csv");
    return 0;
}