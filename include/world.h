#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 
#include <glm/glm.hpp>
#include "Vertex.h"
#include "BounderVoxel.h"

struct World {

    std::vector<Vertex> square;
    std::vector<unsigned int> squ_indices;
    std::vector<Vertex> tri;
    std::vector<Vertex> cube;
    std::vector<Vertex> lightcube;
};

void create_world();
void destroy_world();
extern struct World world;

#endif