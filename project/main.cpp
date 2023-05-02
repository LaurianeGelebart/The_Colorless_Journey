#include <vector>
#include "glimac/FreeflyCamera.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

#include "IHM.hpp"
#include "Obstacle.hpp"
#include "Boid.hpp"
#include "Object.hpp"
#include "ObjectProgram.hpp"
#include "ObjModel.hpp"


std::vector<Boid> boids;
std::vector<Obstacle> obstacles;

ObjModel magic ;
ObjModel puit ;

ObjectProgram magicProgram ; 
ObjectProgram puitProgram ; 

void add_or_remove_boids(IHM &ihm)
{
    int nb_boids = boids.size();
     if (nb_boids<ihm.get_nb_boids()){
        for(int i=0 ; i< ihm.get_nb_boids()-nb_boids ; i++){
            Boid b(magic, magicProgram) ;
            boids.push_back(b);
        }
        nb_boids = ihm.get_nb_boids();
    }
    else if (nb_boids>ihm.get_nb_boids()){
        for(int i=0 ; i< nb_boids-ihm.get_nb_boids() ; i++){
            boids.pop_back();
        }
        nb_boids = ihm.get_nb_boids();
    }
}
void add_or_remove_obstacles(IHM &ihm)
{
    int nb_obstacles = obstacles.size();
    if (nb_obstacles<ihm.get_nb_obstacles()){
        for(int i=0 ; i< ihm.get_nb_obstacles()-nb_obstacles ; i++){
            Obstacle o(magic, magicProgram) ;
            obstacles.push_back(o);
        }
        nb_obstacles = ihm.get_nb_obstacles();
    }
    else if (nb_obstacles>ihm.get_nb_obstacles()){
        for(int i=0 ; i< nb_obstacles-ihm.get_nb_obstacles() ; i++){
            obstacles.pop_back();
        }
        nb_obstacles = ihm.get_nb_obstacles();
    }
}




/* ---------------------------------------------------------------------------- */
/* --------------------------------- MAIN ------------------------------------- */
/* ---------------------------------------------------------------------------- */
int main()
{
    int  window_width  = 1280;
    int  window_height = 720;
    auto ctx = p6::Context{{window_width, window_height, "Project qui se passe super bien"}};
    ctx.maximize_window();

    FreeflyCamera ViewMatrix;

    bool Z = false;
    bool S = false;
    bool Q = false;
    bool D = false;

    IHM ihm ;

    std::cout << "en vie " ;
    puit.LoadFromFile("./assets/models/puit.obj");
    magic.LoadFromFile("./assets/models/magique.obj");


     for(int i=0 ; i<ihm.get_nb_boids() ; i++){
         Boid b(puit, puitProgram) ;
         boids.push_back(b);
     }

     for(int i=0 ; i<ihm.get_nb_obstacles() ; i++){
         Obstacle o(magic, magicProgram) ;
         obstacles.push_back(o);
     }


// Load texture 
    // std::unique_ptr<glimac::Image> terre_texture = glimac::loadImage("/home/lauriane/Documents/OpenGL/GLImac-Template/TP5/index/EarthMap.jpg") ;  
    // std::unique_ptr<glimac::Image> lune_texture = glimac::loadImage("/home/lauriane/Documents/OpenGL/GLImac-Template/TP5/index/MoonMap.jpg") ;  
    // std::unique_ptr<glimac::Image> nuage_texture = glimac::loadImage("/home/lauriane/Documents/OpenGL/GLImac-Template/TP5/index/CloudMap.jpg") ;  
    
    // GLuint earthTexture;
    // GLuint cloudTexture;
    // glGenTextures(1,&earthTexture); 
    // glGenTextures(1,&cloudTexture); 

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, earthTexture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, terre_texture->getWidth(), terre_texture->getHeight(), 0, GL_RGBA, GL_FLOAT, terre_texture->getPixels()  ) ;
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, cloudTexture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nuage_texture->getWidth(), nuage_texture->getHeight(), 0, GL_RGBA, GL_FLOAT, nuage_texture->getPixels()  ) ;
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, 0); 
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, 0); 


// Création d'un  VBO:
    // GLuint vboSphere;
    // glGenBuffers(1, &vboSphere);
    // glBindBuffer(GL_ARRAY_BUFFER, vboSphere);

    // const std::vector<glimac::ShapeVertex> sphere = glimac::sphere_vertices(1, 32, 16);

    // glBufferData(GL_ARRAY_BUFFER, sphere.size()*sizeof(glimac::ShapeVertex), sphere.data(), GL_STATIC_DRAW);

// // Création d'un  VBO:
//     GLuint vboPumpkin;
//     glGenBuffers(1, &vboPumpkin);
//     glBindBuffer(GL_ARRAY_BUFFER, vboPumpkin);

//     std::vector<float> verticesPumpkin = pumpkin.getVertextData();
//     int vertexPumpkinCount = pumpkin.getVertextCount();

//     glBufferData(GL_ARRAY_BUFFER, verticesPumpkin.size()*sizeof(float), &verticesPumpkin[0], GL_STATIC_DRAW);

// Création d'un  VBO:
    // GLuint vboTeapot;
    // glGenBuffers(1, &vboTeapot);
    // glBindBuffer(GL_ARRAY_BUFFER, vboTeapot);

    // std::vector<float> verticesTeapot = teapot.getVertextData();
    // int vertexTeapotCount = teapot.getVertextCount();

    // glBufferData(GL_ARRAY_BUFFER, verticesTeapot.size()*sizeof(float), &verticesTeapot[0], GL_STATIC_DRAW);



// Création VAO1:
    GLuint vao;
    glGenVertexArrays(1, &vao) ;
    glBindVertexArray(vao) ;

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION) ;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL) ;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS) ;

    glBindBuffer(GL_ARRAY_BUFFER, boids[0]._vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), 0); //(const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0) ;

    glEnable(GL_DEPTH_TEST) ;


// Création VAO2:
    GLuint vao2;
    glGenVertexArrays(1, &vao2) ;
    glBindVertexArray(vao2) ;

    // const GLuint VERTEX_ATTR_POSITION = 0;
    // const GLuint VERTEX_ATTR_NORMAL = 1;
    // const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION) ;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL) ;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS) ;

    glBindBuffer(GL_ARRAY_BUFFER, obstacles[0]._vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), 0); //(const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0) ;

    glEnable(GL_DEPTH_TEST) ;




/* ---------------------------------------------------------------------------- */
/* ------------------ Declare your infinite update loop ----------------------- */
/* ---------------------------------------------------------------------------- */
    ctx.update = [&]() {
        glClearColor(0.7f, 0.6f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//gestion event
        if (Z) ViewMatrix.moveFront(0.1);
        if (S) ViewMatrix.moveFront(-0.1);
        if (Q) ViewMatrix.rotateLeft(0.1);
        if (D) ViewMatrix.rotateLeft(-0.1);

        ctx.key_pressed = [&Z, &S, &Q, &D](const p6::Key& key) {
            if (key.physical == GLFW_KEY_W) Z = true;
            if (key.physical == GLFW_KEY_S) S = true;
            if (key.physical == GLFW_KEY_A) Q = true;
            if (key.physical == GLFW_KEY_D) D = true;
        };

        ctx.key_released = [&Z, &S, &Q, &D](const p6::Key& key) {
            if (key.physical == GLFW_KEY_W) Z = false;
            if (key.physical == GLFW_KEY_S) S = false;
            if (key.physical == GLFW_KEY_A) Q = false;
            if (key.physical == GLFW_KEY_D) D = false;
        };


//dessin des boids
        // boids[0]._program.m_Program.use();

        // glm::mat4 MVMatrix = ViewMatrix.getViewMatrix();
        // MVMatrix = glm::scale(MVMatrix, glm::vec3(0.05));
        // glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / (float)window_height, 0.1f, 100.f);

        // glm::mat4 VLightMatrix = ViewMatrix.getViewMatrix() ;
        //glm::mat4 MLightMatrix = glm::rotate(glm::mat4(1), ctx.time(), glm::vec3(0,1,0));
    // glm::vec3 lightPos = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,0,1) );
        //glm::vec3 lightDir = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,1,0) );
        // glm::vec3 lightDir = glm::vec3( (VLightMatrix)*glm::vec4(1,1,1,0) );

		glBindVertexArray(vao) ;

        for(size_t i=0 ; i<boids.size() ; i++)
        {

            // boids[i].draw(ViewMatrix, window_width, window_height) ;
            boids[i].collision(boids, obstacles, ihm, ctx) ;
            boids[i].update_position() ;


            // glUniformMatrix4fv(boidsProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
            // glUniformMatrix4fv(boidsProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

            // MVMatrix = glm::translate(MVMatrix, glm::vec3(boids[i].get_position()));
            // glUniformMatrix4fv(boidsProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));

            // glUniform1f(boidsProgram.uShininess, 0.5);
            // glUniform3fv(boidsProgram.uKd, 1, glm::value_ptr(glm::vec3(0.2,0.5,0.5)));
            // glUniform3fv(boidsProgram.uKs, 1, glm::value_ptr(glm::vec3(0.1,0.2,0.2)));
            // // glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(lightPos));
            // glUniform3fv(boidsProgram.uLightDir_vs, 1, glm::value_ptr(lightDir));
            // glUniform3fv(boidsProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.2)));


            // glDrawArrays(GL_TRIANGLES, 0, vertexPumpkinCount);

        };

		glBindVertexArray(0) ;

        // obstacles[0]._program.m_Program.use();

// dessins des obstacles
        // glm::mat4 oMVMatrix = ViewMatrix.getViewMatrix();
        // oMVMatrix = glm::scale(oMVMatrix, glm::vec3(0.1));
        // glm::mat4 oProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / (float)window_height, 0.1f, 100.f);

		glBindVertexArray(vao2) ;

        for(size_t i=0 ; i<obstacles.size() ; i++)
        {
            // obstacles[i].draw(ViewMatrix, window_width, window_height) ;

            // glUniformMatrix4fv(obstaclesProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(oMVMatrix))));
            // glUniformMatrix4fv(obstaclesProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(oProjMatrix * oMVMatrix));

            // oMVMatrix = glm::translate(oMVMatrix, glm::vec3(obstacles[i].get_position()));
            // glUniformMatrix4fv(obstaclesProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(oMVMatrix));

            // glUniform1f(obstaclesProgram.uShininess, 0.5);
            // glUniform3fv(obstaclesProgram.uKd, 1, glm::value_ptr(glm::vec3(0.2,0.5,0.5)));
            // glUniform3fv(obstaclesProgram.uKs, 1, glm::value_ptr(glm::vec3(0.1,0.2,0.2)));
            // // glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(lightPos));
            // glUniform3fv(obstaclesProgram.uLightDir_vs, 1, glm::value_ptr(lightDir));
            // glUniform3fv(obstaclesProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.2)));

            // glDrawArrays(GL_TRIANGLES, 0, vertexTeapotCount);

        };

        glBindVertexArray(0) ;

        ihm.draw();

       add_or_remove_boids(ihm) ;
       add_or_remove_obstacles(ihm) ;

    };

    ctx.start();
    // glDeleteBuffers(0, &vboPumpkin);
    // glDeleteBuffers(0, &vboSphere);
    // glDeleteBuffers(0, &vboTeapot);
    glDeleteVertexArrays(0, &vao);
    glDeleteVertexArrays(0, &vao2);
    glfwTerminate();
}