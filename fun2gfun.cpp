#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include "utility.h"
#include "cxxopts.h"

template<typename Sequence>
std::string generateGridFunction(Sequence values, int extendedCellCount) {
    std::stringstream result;
    result << "FiniteElementSpace\n"
           << "FiniteElementCollection: L2_2D_P0\n"
           << "VDim: 1\n"
           << "Ordering: 0\n\n";

    std::vector<double> mfemValues;
    for (int i = 0; i < extendedCellCount; i++) {
        mfemValues.insert(mfemValues.end(), values.begin(), values.end());
    }
    for (const auto &value : mfemValues) {
        result << value << "\n";
    }
    return result.str();
}

int main(int argc, char *argv[]) {

    cxxopts::Options options(
            "fun2gfun",
            "Program to covert 1D function to 2D grid function on a mesh obtained by pos2mesh"
    );
    options.add_options()
            ("i,input", "Input file with positions list (required)", cxxopts::value<std::string>())
            ("o,output", "File to write the output (required)", cxxopts::value<std::string>())
            ("c,count", "Cell count (required)", cxxopts::value<int>())
            ("h,help", "Print usage");
    auto parsedOptions = options.parse(argc, argv);

    if (parsedOptions.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    std::string input, output;
    int cellCount;
    try {
        input = parsedOptions["input"].as<std::string>();
        output = parsedOptions["output"].as<std::string>();
        cellCount = parsedOptions["count"].as<int>();
    } catch (const std::domain_error& error){
        std::cout << "Invalid options, see help:" << std::endl;
        std::cout << options.help() << std::endl;
        exit(0);
    }

    std::ifstream inputFile(input);
    std::ofstream outputFile(output);
    outputFile << generateGridFunction(
            CSVReader<double>(inputFile, 1).getColumn(0),
            cellCount
    );

    std::cout << "Grid function was written to: " << output << std::endl;
    return 0;
}
