#include <cmath>
#include <array>
#include <vector>
#include "fluid.h"


















// Update the paticles current position and velocity
void particle::updatePart(const std::array<double,2>& acc, double dt){
    position = addArray(position, arrayScale(velocity, dt));
    velocity = addArray(velocity, arrayScale(acc, dt));
}

// Get the cell that the particle is currently in
std::array<int, 2> particle::getCell(double height){
    int cellX = floor((position[0]/height));
    int cellY = floor((position[1]/height));

    std::array<int, 2> cell = {cellX, cellY};
    return cell;
}

// Get the delta of the x and y for a particle's position
std::array<double, 2> particle::getDelta(const std::array<int, 2>& cell, double height){
    double deltaX = position[0] - (cell[0] * height);
    double deltaY = position[1] - (cell[1] * height);

    std::array<double, 2> delta = {deltaX, deltaY};
    return delta;
}



// Get the divergence of a cell
double cell::divergence(){
    double d = (velocity[0][1] - velocity[0][0]) + (velocity[1][0] - velocity[1][1]);
    return d;
}





// Finds the magnitude of an array
double magnitude(const std::array<double, 2>& vec){
    return sqrt(pow(vec[0], 2) + pow(vec[1], 2));
}

// Function used to add two position arrays or velocity arrays
std::array<double, 2> addArray(const std::array<double, 2>& arr1, const std::array<double, 2>& arr2){
    
    std::array<double, 2> arrTot;

    for (int i = 0; i < 2; i++){    
        arrTot[i] = arr1[i] + arr2[i];
    }

    return arrTot;
}

// multiply an array by a scalar
std::array<double, 2> arrayScale(const std::array<double, 2>& arr1, double scalar){

    std::array<double, 2> arrTot;

    for(int i = 0; i < 2; i++){
        arrTot[i] = arr1[i] * scalar;
    }
    return arrTot;
}