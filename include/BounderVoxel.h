#ifndef BOUNDERVOXEL_H
#define BOUNDERVOXEL_H
#include <glm/glm.hpp>


typedef struct VoxData_b {
    
    glm::ivec3 bounderVoxelLocate = {0,0,0}; // only bounder voxel's locate(x,y,z)
    int bounderVoxelFaceAir[6] = {0}; // 0 face air, 1 face inside 
    int show = 1;
}VoxData_b;

#endif