#pragma once

#include <array>
#include <vector>
#include <cmath>


// helper functions
double magnitude(const std::array<double, 2>& vec);
std::array<double, 2> addArray(const std::array<double, 3>& arr1, const std::array<double, 3>& arr2);
std::array<double, 2> arrayScale(const std::array<double, 3>& arr1, double scalar);


// Cell object for a grid
class cell{
    public:

        // Public attributes
        std::array<int, 2> coordinates;
        double height;
        std::array<std::array<double, 2>, 2> velocity; // The first row is horizontal velocity from left to right. the second row is vertical L to R = Up to Down
        double pressure;
        int type; // 0 is air and 1 is wall

        // Public methods
        double divergence();
        void updateVel(const std::vector<std::vector<cell>>& grid,double d);

};

// particle object
class particle{
    public:

        // Public attributes
        std::array<double, 2> velocity;
        std::array<double, 2> position;


        // Public functions
        void updatePart(const std::array<double, 2>& acc, double dt);
        std::array<int, 2> getCell(double height);
        std::array<double, 2> getDelta(const std::array<int, 2>& cell, double height);
};