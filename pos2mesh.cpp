#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include "utility.h"
#include "cxxopts.h"

template<typename Sequence>
std::string generateMesh(const Sequence &xPositions, const Sequence &yPositions) {
    using namespace std;
    vector<string> elements;
    vector<string> vertices;
    vector<string> borders;
    auto lenX = xPositions.size();
    auto lenY = yPositions.size();

    for (int j = 0; j < lenY; j++) {
        auto y0 = yPositions[j];
        for (int i = 0; i < lenX; i++) {
            auto x0 = xPositions[i];
            auto index = j * xPositions.size() + i;

            if (i == 0 and j < lenY - 1) {
                std::stringstream border;
                border << "1 1 " << index << " " << index + lenX;
                borders.emplace_back(border.str());
            } else if (i == lenX - 1 and j < lenY - 1) {
                std::stringstream border;
                border << "2 1 " << index << " " << index + lenX;
                borders.emplace_back(border.str());
            }

            if (j == 0 and i < lenX - 1) {
                std::stringstream border;
                border << "3 1 " << index << " " << index + 1;
                borders.emplace_back(border.str());
            } else if (j == lenY - 1 and i < lenX - 1) {
                std::stringstream border;
                border << "4 1 " << index << " " << index + 1;
                borders.emplace_back(border.str());
            }

            if (i != lenX - 1 and j != lenY - 1) {
                std::stringstream element;
                element << "1 3 " << index << " " << index + 1 << " " << index + lenX + 1 << " " << index + lenX;
                elements.emplace_back(element.str());
            }
            std::stringstream vertex;
            vertex << x0 << " " << y0;
            vertices.emplace_back(vertex.str());
        }
    }

    std::stringstream result;
    result << "MFEM mesh v1.0\n\n";
    result << "dimension\n2\n";
    result << "\nelements\n" << elements.size() << "\n";
    for (const auto &element : elements) {
        result << element << "\n";
    }

    result << "\nboundary\n" << borders.size() << "\n";
    for (const auto &border : borders) {
        result << border << "\n";
    }

    result << "\nvertices\n" << vertices.size() << "\n2\n";
    for (const auto &vertex : vertices) {
        result << vertex << "\n";
    }
    return result.str();
}

int main(int argc, char *argv[]) {

    cxxopts::Options options("pos2mesh", "Program to convert a list of positions to 2D mesh");
    options.add_options()
            ("i,input", "Input file with positions list (required)", cxxopts::value<std::string>())
            ("o,output", "File to write the output", cxxopts::value<std::string>()->default_value("mesh.mfem"))
            ("c,count", "Cell count (required)", cxxopts::value<int>())
            ("f,from", "Y coordinate from (required)", cxxopts::value<double>())
            ("t,to", "Y coordinate to (required)", cxxopts::value<double>())
            ("h,help", "Print usage");
    auto parsedOptions = options.parse(argc, argv);

    if (parsedOptions.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }


    std::string input, output;
    int cellCount;
    double from, to;
    try {
        input = parsedOptions["input"].as<std::string>();
        output = parsedOptions["output"].as<std::string>();
        cellCount = parsedOptions["count"].as<int>();
        from = parsedOptions["from"].as<double>();
        to = parsedOptions["to"].as<double>();
    } catch (const std::domain_error& error){
        std::cout << "Invalid options, see help:" << std::endl;
        std::cout << options.help() << std::endl;
        exit(0);
    }

    std::ifstream positionsCSVFile(input);
    if (positionsCSVFile.fail()) {
        std::cerr << "File " << input << " does not exist!" << std::endl;
        return 1;
    }
    std::ofstream meshFile(output);
    meshFile << generateMesh(
            CSVReader<double>(positionsCSVFile, 1).getColumn(0),
            linspace(from, to, cellCount + 1)
    );

    std::cout << "Mesh was written to: " << output << std::endl;
    return 0;
}
