#ifndef SOM_H
#define SOM_H

#include <vector>
#include <glm/glm.hpp>

#include "BounderVoxel.h"
#include "Vertex.h"

#define PI 3.14159265

using namespace std;

void SOM_Create(std::vector<VoxData_b>  bounderVoxelData, int bounderNum, int *max);
void SOM_IterateOnce();
void SOM_Destroy();
void SOM_Again();

extern glm::fvec3** lattice;
extern glm::fvec3* dataset;
extern const int max_iter;
extern int map_width;
extern int map_height;
extern int go;
extern bool stop;
extern int iter;
extern double n_learning_rate;
extern double neighbor;

// enum Alphabet : int {
//     A,
//     B,
//     C,
// };

// Alphabet::A;

// class A {
// public:
//     static print();
// };
// class B {
// private:
//     B();
// public:
//     static B* Get();
//     static print();
// };

// B* b1 = B::Get();

// static int count = 0;
// void print() {
//     //static int count = 0;
//     count++;
// }

// void print2() {
//     count = 100;
// }

#endif