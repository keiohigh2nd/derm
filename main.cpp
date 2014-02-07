#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include "k-nn_cvmat.hpp"
#include "sift_pull.cpp"
#include <fstream>

int main(int argc, char *argv[]) {
    double start = gettimeofday_sec();

    std::string pos_name = "sample_pics/dm2.jpg"; 
    std::string neg_name = "sample_pics/non1.png";
    std::string test_name = "sample_pics/dm7.jpg";

    sift_calc(pos_name, neg_name, test_name);

    double end = gettimeofday_sec();
    cout << "Time = " << end - start << " sec." << endl;

    return 0;

}
