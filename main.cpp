
#include <iostream> // for std::cout, std::endl
#include <fstream> // for open, close
#include <functional> // for std::function
#include <time.h> // for clock_gettime, timespec
#include <string.h> // for memset
#include <sys/socket.h>
#include <arpa/inet.h>

#include "utils.h"

unsigned long benchmark(std::function<void(const char[])> func, const int sample_size) {

    struct timespec start_time;
    struct timespec end_time;
    unsigned long total_time = 0;

    for(int i = 0; i<sample_size; ++i) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
        func("YYYYMMDD HHmmSS [ERROR] Some dummy logs for testing\n");
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
    auto file_write = [&ofs] (const char log[]) {ofs << log;};
    int total_time = benchmark(file_write, sample_size);
    ofs.close();
    std::remove("tmp.log");
    std::cout << "Writing " << sample_size
              << " logs to file took " << total_time
              << " nanoseconds." << std::endl;

    // benchmark writing to UDP socket
    struct sockaddr_in addr;
    int addrlen, sock;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }
    memset((char *)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(6000);
    addrlen = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("239.0.0.1");

    auto udp_write = [sock, &addr, addrlen] (const char log[]) {
        sendto(sock, log, sizeof(log), 0, (struct sockaddr *) &addr, addrlen);
    };
    total_time = benchmark(udp_write, sample_size);
    std::cout << "Writing " << sample_size
              << " logs to UDP socket took " << total_time
              << " nanoseconds." << std::endl;

    // benchmark writing to TCP socket
    // TODO
   
    return 0;
}

