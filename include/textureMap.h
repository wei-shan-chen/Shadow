#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <cstring>
#include <omp.h>

#include "BounderVoxel.h"
#include "logger.h"

using namespace std;

void createTexture();
void createdepthTexture();
void bindTexture(int act, int bind);

extern unsigned int texture;
extern unsigned int depthCubemap;
extern unsigned int depthFBO;
extern const unsigned int SHADOW_WIDTH, SHADOW_HEIGHT;

#endif