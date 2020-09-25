#ifndef D1EXTENDER_UTILITY_H
#define D1EXTENDER_UTILITY_H

#include <string>
#include <vector>
#include <sstream>

template <typename T>
class CSVReader {
public:
    explicit CSVReader(std::istream &inputStream, size_t columnsCount)
            : columns(columnsCount) {
        std::string line;
        while (std::getline(inputStream, line)) {
            std::stringstream ss(line);

            for (int i = 0; i < columnsCount; i++) {
                std::string valueString;
                std::getline(ss, valueString, ',');
                auto value = std::stod(valueString);
                columns[i].emplace_back(value);
            }
        }
    }

    const std::vector<T> &getColumn(int i) const {
        return columns[i];
    }

    std::vector<std::vector<T>> columns;
};

template<typename T>
std::vector<T> linspace(T a, T b, size_t N) {
    T h = (b - a) / static_cast<T>(N - 1);
    std::vector<T> xs(N);
    typename std::vector<T>::iterator x;
    T val;
    for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h)
        *x = val;
    return xs;
}

#endif //D1EXTENDER_UTILITY_H
