#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <limits>

namespace MI {

    inline void ignoreLine()   // função para lidar com entrada de dados
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    inline void handleInput()  // função para lidar com entrada de dados
    {
        std::cin.clear();
        std::cout << "Invalid input, please try again: ";
        ignoreLine();
    }
}

#endif // INPUT_H
