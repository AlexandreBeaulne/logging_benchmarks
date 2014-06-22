
#include <iostream> // for std::cout, std::endl
#include <fstream> // for open, close
#include <functional> // for std::function
#include <time.h> // for clock_gettime, timespec

#include "utils.h"

unsigned long benchmark(std::function<void(const char[])> func, const int sample_size) {

    struct timespec start_time;
    struct timespec end_time;
    unsigned long total_time = 0;

    for(int i = 0; i<sample_size; ++i) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
        func("YYYYMMDD,HHmmSS [ERROR] Some dummy logs for testing\n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
        total_time += 1000000000*(end_time.tv_sec - start_time.tv_sec);
        total_time += (end_time.tv_nsec - start_time.tv_nsec);
    }
    return total_time;
}

int main() {

    pretty_print_system_specs();

    int sample_size = 100000;

    // benchmark writing to file
    std::ofstream ofs ("tmp.log", std::ofstream::out);
    auto lambda = [&ofs] (const char log[]) {ofs << log;};
    int total_time = benchmark(lambda, sample_size);
    ofs.close();
    std::remove("tmp.log");
    std::cout << "Printing " << sample_size
              << " logs to file took " << total_time
              << " nanoseconds." << std::endl;

    // benchmark writing to UDP socket
    // TODO

    // benchmark writing to TCP socket
    // TODO
   
    return 0;
}

