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
    int x = coordinates[0], y = coordinates[1];
    int width = grid.size(), height = grid[0].size();
    int nachbarCount;

    // Check Left Neighbor
    if (x == 0 || grid[x-1][y].type == 1){
        nachbarWalls[0] = 1;
    }
    
    // Check Right Neighbor
    if (x == width - 1 || grid[x+1][y].type == 1){
        nachbarWalls[2] = 1;
    }

    // Check Upper Neighbor
    if (y == height - 1 || grid[x][y+1].type == 1){
        nachbarWalls[1] = 1;
    } 

    // Check Lower Neighbor
    if (y == 0 || grid[x][y-1].type == 1){
        nachbarWalls[3] = 1;
    }
    
    // Count the walls
    nachbarCount = nachbarWalls[0] + nachbarWalls[1] + nachbarWalls[2] + nachbarWalls[3];

    // update velocities
    if(nachbarWalls[0] == 0){
        velocity[0][0] = velocity[0][0] + (d/(4 - nachbarCount));
    }

    if(nachbarWalls[2] == 0){
        velocity[0][1] = velocity[0][1] - (d/(4 - nachbarCount));
    }

    if(nachbarWalls[3] == 0){
        velocity[1][1] = velocity[1][1] + (d/(4 - nachbarCount));
    }

    if(nachbarWalls[1] == 0){
        velocity[1][0] = velocity[0][1] - (d/(4 - nachbarCount));
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