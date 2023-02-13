#include "Drawmodel.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

MatrixStack model;
MatrixStack view;
MatrixStack projection;
MatrixStack lightSpaceMatrix;

Shader ourShader;
Shader lightShader;
Shader depthShader;
Shader depthdebug;

Item cube;
Item lightcube;
Item ground;

// glm::vec3 lightPos = glm::vec3(-2.0,4.0,-1.0);
glm::vec3 lightPos = glm::vec3(5.0,5.0,5.0);
float near_plane = 0.1f, far_plane = 1000.0f;

void Shader_Create();
void Shader_init(int n, bool settex);
void ViewProjection_Create(glm::vec3 position, glm::mat4 viewMatrix, float zoom, int n);
void Model_Floor_Create(Shader shader);
void Model_cube_create(Shader shader);
void Model_lightCube_create(Shader shader);
void ourShader_model();
void depthShader_model();
void depthdebug_model();

void debug();
void Shader_Create()
{
    create_world();
    ourShader = Shader("shader/shader.vs", "shader/shader.fs");
    lightShader = Shader("shader/lightShader.vs", "shader/lightShader.fs");
    depthShader = Shader("shader/depthShader.vs", "shader/depthShader.fs");
    depthdebug = Shader("shader/depthdebug.vs", "shader/depthdebug.fs");

    cube = Item(world.cube);
    ground = Item((world.square));
    lightcube = Item(world.lightcube);

}
void Shader_init(int n, bool settex){
    if(n == 0){
        ourShader.use();
        if(settex){
            ourShader.setInt("texturemap", 0);
            ourShader.setInt("shadowMap", 1);
        }
        
    }else if(n == 1){
        lightShader.use();
    }else if(n == 2){
        depthShader.use(); 
        if(settex){
            depthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix.Top());
            // debug();
        }
    }else if(n == 3){
        depthdebug.use();
        if(settex){
            depthdebug.setInt("depthMap", 0);
        }    
    }
}   
void ViewProjection_Create(glm::vec3 position, glm::mat4 viewMatrix, float zoom, int n){
    view.Save(viewMatrix);
    projection.Save(glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f));
    if(n == 0){
        ourShader.setMat4("view", view.Top());
        ourShader.setMat4("projection", projection.Top());
        ourShader.setVec3("viewPos", position);
        ourShader.setVec3("lightPos", lightPos);
        ourShader.setMat4("lightSpaceMatrix", lightSpaceMatrix.Top());
    }else if(n == 1){
        lightShader.setMat4("view", view.Top());
        lightShader.setMat4("projection", projection.Top());
    }else if(n == 2){
        MatrixStack lightProjection, lightView;
        lightProjection.Save(glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane));
        lightView.Save(glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0)));
        lightSpaceMatrix.Save(lightProjection.Top() * lightView.Top());


        
    }else if(n == 3){
        depthdebug.setFloat("near_plane", near_plane);
        depthdebug.setFloat("far_plane", far_plane);
    }
}
void ourShader_model(){
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bindTexture(0,0);
    bindTexture(1,1);
    Model_Floor_Create(ourShader);
    Model_cube_create(ourShader);
}
void lightShader_model(){
    Model_lightCube_create(lightShader);
}
void depthShader_model(){
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        bindTexture(0,0);
        // Model_Floor_Create(depthShader);
        Model_cube_create(depthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void depthdebug_model(){
    
    bindTexture(0,1);
    // Model_Floor_Create(depthdebug);
    // Model_cube_create(depthdebug);
}

void Model_Floor_Create(Shader shader){
    model.Push();
    model.Save(glm::scale(model.Top(), glm::vec3( 2000.0f, 1.0f, 2000.0f)));
    model.Save(glm::translate(model.Top(), glm::vec3(-0.5f, 0.0f, -0.5)));
    shader.setMat4("model", model.Top());
    shader.setBool("shader",true);
    glBindVertexArray(ground.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model.Pop();
    // log_debug("%ld", ground.VAO);

}
void Model_cube_create(Shader shader){
    model.Push();
    shader.setMat4("model", model.Top());
    shader.setBool("shader",false);
    glBindVertexArray(cube.VAO);
    glDrawArrays(GL_TRIANGLES, 0, world.cube.size());
    // log_debug("%u", world.cube.size());

    
    model.Pop();
}
void Model_lightCube_create(Shader shader){
    model.Push();
    model.Save(glm::translate(model.Top(),lightPos));
    model.Save(glm::scale(model.Top(), glm::vec3( 0.2f, 0.2f, 0.2f)));
    shader.setMat4("model", model.Top());
    glBindVertexArray(lightcube.VAO);
    glDrawArrays(GL_TRIANGLES, 0, world.lightcube.size());
    model.Pop();
    // log_debug("%ld", lightcube.VAO);
}
void Model_del(){
    cube.Item_del();
    ground.Item_del();
    lightcube.Item_del();
}