
#include <iostream> // for std::cout, std::endl
#include <stdio.h> // for popen
#include <string> // for std::string
//#include <sys/time.h>  

#include "utils.h"

//inline int gettime() {
//    timeval tv;
//    gettimeofday(&tv, NULL);
//    return 1000000*tv.tv_sec + tv.tv_usec;
//}

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

void pretty_print_system_specs() {

    char distro[] = "uname -v | awk '{print $1;}'";
    char architecture[] = "uname -p";
    char model[] = "grep -m 1 'model name' /proc/cpuinfo | sed 's/model name\\t: //'";
    char num_cpu[] = "grep -c processor /proc/cpuinfo";
    char ram[] = "grep MemTotal /proc/meminfo | sed 's/MemTotal:\\s*//'";
    char card[] = "lspci | grep 'Network controller' | sed 's/[0-9:\\.]* Network controller: //'";

    std::cout << std::endl << "Distro:       " << exec(distro);
    std::cout << "Architecture: " << exec(architecture);
    std::cout << "CPU Model:    " << exec(model);
    std::cout << "# CPUs:       " << exec(num_cpu);
    std::cout << "RAM:          " << exec(ram);
    std::cout << "Network Card: " << exec(card) << std::endl;
}

