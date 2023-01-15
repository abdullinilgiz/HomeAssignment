#include "triangle_area.h"
#include <iostream>
int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " a b c" << std::endl;
        std::cerr << "where a, b, c are triangle side lengths (as floating "
                     "numbers, e.g. 1.2 3.4 4)" << std::endl;
        return 1;
    }
    double v[3];
    for (int i = 0; i < 3; ++i) {
        v[i] = atof(argv[i + 1]);
    }
    double r = triangle_area(v[0], v[1], v[2]);
    std::cout << "Triangle area: " << r << std::endl;
    return 0;
}
