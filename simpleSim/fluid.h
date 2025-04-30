#pragma once

#include <array>
#include <vector>
#include <cmath>


// Cell object for a grid
class cell{
    public:

        // Public attributes
        std::array<double, 2> center;
        float size;
        float velX;
        float velY;
        float pressure;
        int type;

};

// particle object
class particle{
    public:

        // Public attributes
        std::array<double, 2> velocity;
        std::array<double, 2> position;
};