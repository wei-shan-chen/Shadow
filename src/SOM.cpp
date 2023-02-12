#include <cstdlib>
#include <ctime>
#include <iostream>

#include "SOM.h"

glm::fvec3 **lattice;
glm::fvec3 *dataset;

int initLattice = 1; // 0 random cylinder, 1 cylinder, 2 random flat, 3 flat
int go = 0;
bool stop = true;
bool is_som_finished = false;
int map_width;
int map_height;
int datasteNum = 0;
const int max_iter = 20000;
int iter = 0;
double learning_rate;
double radius;
double n_learning_rate;
double neighbor;
int *max_lattice;


glm::fvec3 **createMap(int map_width, int map_height, int *max);
glm::fvec3 *createInputDataset(std::vector<VoxData_b>  bounderVoxelData, int bounderNum);
glm::ivec2 computNeiborhood(int i, int j, glm::ivec2 node, glm::ivec2 bmu);
const glm::fvec3 getInput(glm::fvec3 *dataset, int datasteNum);
void destroy(glm::fvec3 **arr, int width, int height);
void destroyDataset(glm::fvec3 *arr, int datasteNum);
void updateNode(glm::fvec3** lattice, glm::fvec3 nowInput,glm::ivec2 bmuId, glm::ivec2 nodeId, double radius, double learning_rate);
double computerate(int iter, double fun);
double computeradius(int iter, double fun);
double computeScale(double sigma, double dist);
bool isInNeighborhood(double squaredDist, double radius);

void SOM_Create(std::vector<VoxData_b>  bounderVoxelData, int bounderNum, int *max)
{
    srand(time(NULL));
    map_width = 50;//sqrt(bounderNum)/2;
    map_height = 50;//sqrt(bounderNum)/2;
    radius = map_width/3;
    learning_rate = 0.01;
    // 1. Create lattice
    lattice = createMap(map_width, map_height, max);
    max_lattice = max;
    // 2. Create input dataset
    dataset = createInputDataset(bounderVoxelData, bounderNum);
    datasteNum = bounderNum;
}

void SOM_IterateOnce()
{
    
    // 1. Get one input from the dataset
    // 2. Find BMU
    // 3. Update BMU and the neighbors
    n_learning_rate = computerate(iter, learning_rate);
    neighbor = computeradius(iter, radius);
    const glm::fvec3 nowInput = getInput(dataset, datasteNum);
    double minDist = -1.0;
    glm::ivec2 bmu;
    // compute winner point
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            double tmp1 = 0.0;
            float dx = (lattice[i][j].x - nowInput.x);
            float dy = (lattice[i][j].y - nowInput.y);
            float dz = (lattice[i][j].z - nowInput.z);
            tmp1 = dx*dx + dy*dy + dz*dz;
            if (minDist < 0.0)
            {
                minDist = tmp1;
                continue;
            }
            
            if (minDist > tmp1)
            {
                minDist = tmp1;
                bmu = {i, j};
            }
        }
    }
    
    // renew winner point and neighnorhood
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            glm::ivec2 node = glm::ivec2(i, j);
            glm::ivec2 diff = computNeiborhood(i,j,node,bmu);//node - bmu;
            double squaredDist = static_cast<double>(diff.x * diff.x + diff.y * diff.y);
            // std::cout << "Dist " <<squaredDist<<std::endl;
            // std::cout << i<<", " << j << std::endl;
            if (isInNeighborhood(squaredDist, neighbor))
            {
                double n_radius = computeScale(neighbor, squaredDist);
                updateNode(lattice, nowInput, bmu, node, n_radius, n_learning_rate);
                
            }
        }
    }
    iter++; 
    // cout << iter <<endl;
}

void SOM_Destroy()
{
    // 1. Destroy lattice
    destroy(lattice, map_width, map_height);
    // 2. Destroy input dataset
    destroyDataset(dataset, datasteNum);
}
void SOM_Again(){
    destroy(lattice, map_width, map_height);
    go = 0;
    stop = true;
    is_som_finished = false;
    map_width;
    map_height;
    datasteNum = 0;
    iter = 0;
    learning_rate = 0.1;
    radius = 5;
    n_learning_rate = 0.1;
    neighbor = 5;
    lattice = createMap(map_width, map_height, max_lattice);
}
glm::fvec3 *createInputDataset(std::vector<VoxData_b>  bounderVoxelData, int bounderNum)
{
    glm::fvec3 *dataset = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * bounderNum);

   
    for (int i = 0; i < bounderNum; i++)
    {
        double i0 = bounderVoxelData[i].bounderVoxelLocate.x;
        double j0 = bounderVoxelData[i].bounderVoxelLocate.y;
        double k0 = bounderVoxelData[i].bounderVoxelLocate.z;
        dataset[i] = {i0, j0, k0};
    }
    return dataset;
}
glm::fvec3 **createMap(int map_width, int map_height, int *max)
{
    double val = PI / 180;

    glm::fvec3 **lattice = (glm::fvec3 **)malloc(sizeof(glm::fvec3 *) * map_height);
    for (int i = 0; i < map_height; i++)
    {
        lattice[i] = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * map_width);
    }
    switch(initLattice){
        case 0: // random cylinder
            for (int i = 0; i < map_height; i++)
            {
                for (int j = 0; j < map_width; j++)
                {
                    double i0, j0, k0;

                    i0 = (rand() % abs(max[0]-1))*(-1);
                    j0 = rand() % max[1];
                    k0 = rand() % max[2];
                    // std::cout << i0 << ", " << max[0]<<std::endl;
                    lattice[i][j] = {i0, j0, k0};
                }
            }
            break;
        case 1: // cylinder
            for (int i = 0; i < map_height; i++){
                double theta = 360.0/(double)(map_height-1);
                for(int j = 0; j < map_width; j++){
                    double i0, j0, k0;

                    i0 = (max[0]/2) * cos(i*theta*val) + (max[0]/2);
                    j0 = (max[1]/map_width) *j;
                    k0 = (max[2]/2) * sin(i*theta*val) + (max[2]/2);
                    // std::cout << i0 << ", " << max[0]<<std::endl;
                    lattice[i][j] = {i0, j0, k0};
                }
            }
            break;
        case 2: // random flat
            for (int i = 0; i < map_height; i++)
            {
                for (int j = 0; j < map_width; j++)
                {
                    double i0, j0, k0;

                    i0 = (rand() % abs(max[0]-1))*(-1);
                    j0 = rand() % max[1];
                    k0 = rand() % max[2];
                    // std::cout << i0 << ", " << max[0]<<std::endl;
                    lattice[i][j] = {i0, j0, k0};
                }
            }
            break;
        case 3: // flat

            break;
        default:
            cout << "error initLattic num" << endl;
            break;
    }

    return lattice;
}
glm::ivec2 computNeiborhood(int i, int j, glm::ivec2 node, glm::ivec2 bmu){
    // cylinder
    glm::ivec2 diff = {0,0};
    int half = (map_width-1)/2;
    if(bmu.x <= half){
        if(node.x >= half+bmu.x){
            diff.x = bmu.x+((map_width-1) - node.x); 
        }else{
            diff.x = node.x - bmu.x;
        }
    }else if(bmu.x > half){
        if(node.x >= bmu.x - half){
            diff.x = bmu.x - node.x;
        }else{
            diff.x = node.x + ((map_width-1) - bmu.x);
        }
    }
    diff.y = node.y - bmu.y;
    // diff = node - bmu;
    return diff;
}

void destroy(glm::fvec3 **arr, int width, int height)
{
    for (int i = 0; i < width; i++)
    {
        free(arr[i]);
    }
}
void destroyDataset(glm::fvec3 *arr, int datasteNum){
    free(arr);
}
double computeradius(int iter, double fun)
{
    double lamda = ((double)(max_iter)) / log(fun);
    double sigma = fun * exp(-1 * ((double)iter) / lamda);
    
    return sigma;
}
double computerate(int iter, double fun)
{
    double sigma = fun * exp(-1 * ((double)iter) / ((double)(max_iter)) );
    return sigma;
}

const glm::fvec3 getInput(glm::fvec3 *dataset, int datasteNum)
{
    int num, i;
    num = (datasteNum/RAND_MAX) + 1;
    i = (rand()*num) % datasteNum + rand()%num;
    while(i >= datasteNum){
        i = (rand()*num) % datasteNum + rand()%num;
    }
    
    return dataset[i];
}

bool isInNeighborhood(double squaredDist, double radius)
{
    if (squaredDist <= (radius * radius))
    {
        // std::cout << "dist : " << squaredDist << " radius : " << radius*radius << std::endl;
        return true;
    }
    return false;
}

double computeScale(double sigma, double dist)
{
    double theta = exp((-1 * dist) / (2 * pow(sigma, 2)));
    
    return theta;
}

void updateNode(glm::fvec3** lattice, glm::fvec3 nowInput,glm::ivec2 bmuId, glm::ivec2 nodeId, double radius, double learning_rate){
    lattice[nodeId.x][nodeId.y].x = lattice[nodeId.x][nodeId.y].x + radius * learning_rate*(nowInput.x-lattice[nodeId.x][nodeId.y].x);
    lattice[nodeId.x][nodeId.y].y = lattice[nodeId.x][nodeId.y].y + radius * learning_rate*(nowInput.y-lattice[nodeId.x][nodeId.y].y);
    lattice[nodeId.x][nodeId.y].z = lattice[nodeId.x][nodeId.y].z + radius * learning_rate*(nowInput.z-lattice[nodeId.x][nodeId.y].z);
    
}