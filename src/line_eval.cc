#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <pthread.h>
#include <memory>
#include "line_fit.hh"
#include <iomanip>
#include <chrono>
#include <random>
using Data =  std::tuple<std::vector<double>,std::vector<double>>;

// Function to generate random numbers from a standard normal distribution
Data GenerateGaussianNumbers(int n, double mean, double stddev, double m, double b) {
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::normal_distribution<> norm(mean, stddev); // Standard normal distribution
     std::uniform_real_distribution<> uniform(0, 10); // Uniform distribution

    std::vector<double> x;
    std::vector<double> y;
    for (int i = 0; i < n; ++i) {
        x.push_back(uniform(gen));
        y.push_back(m*x[i] + b + norm(gen));
    }
    return std::make_tuple(x,y);
}


double ComputeLineResidual(const Line& line, const Data& data)
{
    auto& [x,y] = data;
    double residual = 0; 
    for (int i = 0; i < x.size(); i++)
    {
      auto y_pred = line.m*x[i] + line.b;
      residual += std::abs(y_pred - y[i]);     
    }
    return residual/x.size();
}

void PrintFormattedOutput(double real_m, double real_b, double pred_m, double pred_b, double residual, double time, const std::string& filename) {
    std::ofstream outfile(filename);

    if (outfile.is_open()) {
        // Print header to console and file
        std::cout << std::setw(10) << "Real_m" << std::setw(10) << "Real_b" << std::setw(10) << "Pred_m" << std::setw(10) << "Pred_b" << std::setw(25) << "Average Residual" << std::setw(10) << "Time" << std::endl;
        outfile << std::setw(10) << "Real_m" << std::setw(10) << "Real_b" << std::setw(10) << "Pred_m" << std::setw(10) << "Pred_b" << std::setw(25) << "Average Residual" << std::setw(10) << "Time" << std::endl;

        // Print values to console and file
        std::cout << std::setw(10) << real_m << std::setw(10) << real_b << std::setw(10) << pred_m << std::setw(10) << pred_b << std::setw(25) << residual << std::setw(10) << time << std::endl;
        outfile << std::setw(10) << real_m << std::setw(10) << real_b << std::setw(10) << pred_m << std::setw(10) << pred_b << std::setw(20) << residual << std::setw(10) << time << std::endl;

        outfile.close();
    } else {
        std::cerr << "Unable to open file";
    }
}



int main(int argc, char* argv[]) {
    Data trainingData  = GenerateGaussianNumbers(100,0, 5, 3, 2);
    std::unique_ptr<LineFit> fit = std::make_unique<NelderMeadLineFit>();
    auto& [x,y] = trainingData;

    //start time
    auto start = std::chrono::high_resolution_clock::now(); 
    auto line = fit->ComputeLine(x,y);    
    //end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    double metric =  ComputeLineResidual(line, trainingData);
//    PrintFormattedOutput(3, 2, line.m, line.b, metric, elapsed_seconds.count(), "output.txt");


    return 0;
}