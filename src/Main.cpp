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
    
    if(argc < 2){
        std::cerr << "No file provided. " << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    Parser p = Parser();
    std::optional<JobShop> parsedFile = p.parse(filename);
    JobShop js = parsedFile.has_value() ? parsedFile.value() : JobShop();
    return js.run(p.getAmountMachines());
}
