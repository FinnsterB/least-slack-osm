#include <iostream>
#include <algorithm>
#include <climits>
#include "JobShop.h"
#include "Machine.h"
#include "Job.h"
#include "Task.h"
#include "Parser.h"
using namespace std;

int main(int argc, char* argv[]) {
    // Parse input file given as argument
    Parser p = Parser();
    if(argc < 2){
        std::cerr << "No file provided. " << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    JobShop js = p.parse(filename);

    
    for (unsigned short i = 0; i < p.getAmountMachines(); i++) {
        js.machines.push_back(Machine());
    }

    js.schedule();

    // Output: sort on job id
    std::sort(js.jobs.begin(), js.jobs.end(), [](Job& a, Job& b) -> bool {
        return a.getId() < b.getId();
    });

    for (Job &j : js.jobs) {
        std::cout << j.getId() << " " << j.getStartTime() << " " << (j.getStopTime()) << std::endl;
    }

    return 0;
}
