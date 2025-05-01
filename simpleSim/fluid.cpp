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

// Update cell velocity
void cell::updateVel(const std::vector<std::vector<cell>>& grid, double d){

    std::array<int, 4> nachbarWalls = {0,0,0,0}; // Neighbors are stored clockwise starting at the left side
    int nachbarCount = 0;

    // Check Left Neighbor
    if (coordinates[0] == 0){
        nachbarWalls[0] = 1;
    } else {
        nachbarWalls[0] = grid[coordinates[0]-1][coordinates[1]].type;
    }
    
    // Check Right Neighbor
    if (coordinates[0] == grid.size()){
        nachbarWalls[2] = 1;
    } else {
        nachbarWalls[2] = grid[coordinates[0]+1][coordinates[1]].type;
    }

    // Check Upper Neighbor
    if (coordinates[1] == grid[coordinates[0]].size()){
        nachbarWalls[1] = 1;
    } else {
        nachbarWalls[1] = grid[coordinates[0]][coordinates[1]+1].type;
    }

    // Check Lower Neighbor
    if (coordinates[1] == 0){
        nachbarWalls[3] = 1;
    } else {
        nachbarWalls[3] = grid[coordinates[0]][coordinates[1]-1].type;
    }
    
    // Count the walls
    for (int i = 0; i < 4; i++){
        if (nachbarWalls[i] == 1){
            nachbarCount++;
        }
    }

    // update velocities

    if(nachbarWalls[0] == 0){
        velocity[0][0] = velocity[0][0] + (d/(4 - nachbarCount));
    }

    if(nachbarWalls[2] == 0){
        velocity[0][1] = velocity[0][1] + (d/(4 - nachbarCount));
    }

    if(nachbarWalls[3] == 0){
        velocity[1][1] = velocity[1][1] + (d/(4 - nachbarCount));
    }

    if(nachbarWalls[1] == 0){
        velocity[0][1] = velocity[0][1] + (d/(4 - nachbarCount));
    }
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