#include <vector>
#include <map>
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
#include "Loader.hpp"
#include "FacesGroup.hpp"


#include "test.hpp"



// void add_or_remove_boids(IHM &ihm, ObjectProgram &puitProgram, ObjModel &puit)
// {
//     int nb_boids = boids.size();
//      if (nb_boids<ihm.get_nb_boids()){
//         for(int i=0 ; i< ihm.get_nb_boids()-nb_boids ; i++){
//             Boid b(puit, puitProgram) ;
//             boids.push_back(b);
//         }
//         nb_boids = ihm.get_nb_boids();
//     }
//     else if (nb_boids>ihm.get_nb_boids()){
//         for(int i=0 ; i< nb_boids-ihm.get_nb_boids() ; i++){
//             boids.pop_back();
//         }
//         nb_boids = ihm.get_nb_boids();
//     }
// }
// void add_or_remove_obstacles(IHM &ihm, ObjectProgram &magicProgram, ObjModel &magic)
// {
//     int nb_obstacles = obstacles.size();
//     if (nb_obstacles<ihm.get_nb_obstacles()){
//         for(int i=0 ; i< ihm.get_nb_obstacles()-nb_obstacles ; i++){
//             Obstacle o(magic, magicProgram) ;
//             obstacles.push_back(o);
//         }
//         nb_obstacles = ihm.get_nb_obstacles();
//     }
//     else if (nb_obstacles>ihm.get_nb_obstacles()){
//         for(int i=0 ; i< nb_obstacles-ihm.get_nb_obstacles() ; i++){
//             obstacles.pop_back();
//         }
//         nb_obstacles = ihm.get_nb_obstacles();
//     }
// }




/* ---------------------------------------------------------------------------- */
/* --------------------------------- MAIN ------------------------------------- */
/* ---------------------------------------------------------------------------- */
int main()
{
    int  window_width  = 1280;
    int  window_height = 720;
    auto ctx = p6::Context{{window_width, window_height, "Project qui se passe super bien"}};
    ctx.maximize_window();

    glEnable(GL_DEPTH_TEST) ;

        img::Image wood = p6::load_image_buffer("./assets/textures/wood.png") ;   
        img::Image brick = p6::load_image_buffer("./assets/textures/red_brick_draw.png") ;   
        // std::vector<img::Image> textures ; 
        GLuint     wood_texture;
        glGenTextures(1, &wood_texture);
        glBindTexture(GL_TEXTURE_2D, wood_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wood.width(), wood.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, wood.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        GLuint     brick_texture;
        glGenTextures(1, &brick_texture);
        glBindTexture(GL_TEXTURE_2D, brick_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, brick.width(), brick.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, brick.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        // wood = p6::load_image_buffer("./assets/textures/stele.png") ;   

        // textures.push_back(p6::load_image_buffer("./assets/textures/wood.png"));
        // textures.push_back(p6::load_image_buffer("./assets/textures/red_brick_draw.png"));
        // textures.push_back(p6::load_image_buffer("./assets/textures/stele.png"));
        // textures.push_back(p6::load_image_buffer("./assets/textures/rock.png"));

        ObjectProgram magicProgram ; 
        ObjectProgram puitProgram ; 

    std::vector<Boid> boids;
    std::vector<Obstacle> obstacles;
    std::map<std::string, Material> materialMap;

    FreeflyCamera ViewMatrix;

    bool Z = false;
    bool S = false;
    bool Q = false;
    bool D = false;

    IHM ihm ;
    Loader loader ; 

    std::vector<FacesGroup> puit = loader.LoadFromFile("./assets/models/puit.obj", materialMap);
    std::vector<FacesGroup> magic = loader.LoadFromFile("./assets/models/magique.obj", materialMap);

     for(int i=0 ; i<ihm.get_nb_boids() ; i++){
         Boid b(puit, puitProgram) ;
         boids.push_back(b);
     }

     for(int i=0 ; i<ihm.get_nb_obstacles() ; i++){
         Obstacle o(magic, magicProgram) ;
         obstacles.push_back(o);
     }




// // Création VAO2:
//     GLuint vao2;
//     glGenVertexArrays(1, &vao2) ;
//     glBindVertexArray(vao2) ;

//     // const GLuint VERTEX_ATTR_POSITION = 0;
//     // const GLuint VERTEX_ATTR_NORMAL = 1;
//     // const GLuint VERTEX_ATTR_TEXCOORDS = 2;

//     glEnableVertexAttribArray(VERTEX_ATTR_POSITION) ;
//     glEnableVertexAttribArray(VERTEX_ATTR_NORMAL) ;
//     glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS) ;

//     glBindBuffer(GL_ARRAY_BUFFER, obstacles[0]._vbo);

//     glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), 0); //(const GLvoid*)offsetof(glimac::ShapeVertex, position));
//     glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, normal));
//     glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
//     glBindBuffer(GL_ARRAY_BUFFER, 0);

//     glBindVertexArray(0) ;

//     glEnable(GL_DEPTH_TEST) ;




/* ---------------------------------------------------------------------------- */
/* ------------------ Declare your infinite update loop ----------------------- */
/* ---------------------------------------------------------------------------- */
    ctx.update = [&]() {
        glClearColor(0.7f, 0.6f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//gestion event
        if (Z) ViewMatrix.moveFront(0.1);
        if (S) ViewMatrix.moveFront(-0.1);
        if (Q) ViewMatrix.rotateLeft(0.5);
        if (D) ViewMatrix.rotateLeft(-0.5);

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

//Dessin

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, wood_texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, brick_texture);

        for(auto boid : boids){
            boid.draw(ViewMatrix, window_width, window_height, materialMap) ;
            boid.collision(boids, obstacles, ihm, ctx) ;
            boid.update_position() ;
        };
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);


        for(auto obstacle : obstacles){
            obstacle.draw(ViewMatrix, window_width, window_height, materialMap) ;
        };

        ihm.draw();

    //    add_or_remove_boids(ihm, puitProgram, puit) ;
    //    add_or_remove_obstacles(ihm, magicProgram, magic) ;

    };

    ctx.start();
    for(auto obstacle : obstacles){
        obstacle.deleteVAO_VBO() ; 
    }
    for(auto boid : boids){
        boid.deleteVAO_VBO() ; 
    }
    glfwTerminate();
}