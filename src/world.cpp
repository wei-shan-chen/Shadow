#include "world.h"

struct World world = {};

void create_world(std::vector<VoxData_b>  bounderVoxelData, int bounderNum) {
    world.cube = {
        //       position                  normal                 color               tex
        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },

        Vertex{  { 0.0f,  0.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },

        Vertex{  { 0.0f,  1.0f,  1.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  0.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  1.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  1.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },

        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },

        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  1.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },

        Vertex{  { 0.0f,  1.0f,  0.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  1.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  0.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
    };
    
    for(int i = 0; i < bounderNum; i++){
        int x = bounderVoxelData[i].bounderVoxelLocate.x;
        int y = bounderVoxelData[i].bounderVoxelLocate.y;
        int z = bounderVoxelData[i].bounderVoxelLocate.z;
        if(bounderVoxelData[i].bounderVoxelFaceAir[0] == 0){//0
                                        //       position                        normal                 color                 tex
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { 1.0f,  0.0f, 0.0f} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[1] == 0){//1
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f, 0.0f} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[4] == 0){//2
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[5] == 0){//3
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, .0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, .0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, .0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, .0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, .0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f, .0f} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[2] == 0){//4
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[3] == 0){//5
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f, 0.0f} });
        }
    }
    
    
    world.lightcube = {
        //       position                  
        Vertex{  { 0.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  1.0f,  0.0f, } },
        Vertex{  { 1.0f,  1.0f,  0.0f, } },
        Vertex{  { 0.0f,  1.0f,  0.0f, } },
        Vertex{  { 0.0f,  0.0f,  0.0f, } },

        Vertex{  { 0.0f,  0.0f,  1.0f, } },
        Vertex{  { 1.0f,  0.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  0.0f,  1.0f, } },

        Vertex{  { 0.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  0.0f, } },
        Vertex{  { 0.0f,  0.0f,  0.0f, } },
        Vertex{  { 0.0f,  0.0f,  0.0f, } },
        Vertex{  { 0.0f,  0.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  1.0f, } },

        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },

        Vertex{  { 0.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  1.0f, } },
        Vertex{  { 1.0f,  0.0f,  1.0f, } },
        Vertex{  { 0.0f,  0.0f,  1.0f, } },
        Vertex{  { 0.0f,  0.0f,  0.0f, } },

        Vertex{  { 0.0f,  1.0f,  0.0f, } },
        Vertex{  { 1.0f,  1.0f,  0.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  0.0f, } },
    };
    world.square = {
            Vertex{ { 0.0f, 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            Vertex{ { 1.0f, 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            Vertex{ { 1.0f, 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

            Vertex{ { 1.0f, 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            Vertex{ { 0.0f, 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            Vertex{ { 0.0f, 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    };
    world.squ_indices = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };
    world.tri= {
		Vertex{ { 0.5f, -0.5f, 0.0f}},
        Vertex{ {-0.5f, -0.5f, 0.0f}},
        Vertex{ { 0.0f,  0.5f, 0.0f}}
	};
}
void destroy_world() {
    world.square.clear();
    world.squ_indices.clear();
    world.tri.clear();
    world.cube.clear();
}