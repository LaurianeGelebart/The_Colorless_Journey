#include <vector>
#include <map>
#include "FreeflyCamera.hpp"
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
#include "Cloud.hpp"
#include "Arpenteur.hpp"
#include "Content.hpp"
#include "Texture.hpp"


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
        
        // GLuint wood_texture;
        // glGenTextures(1, &wood_texture);
        // glBindTexture(GL_TEXTURE_2D);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wood.width(), wood.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, wood.data());
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // glBindTexture(GL_TEXTURE_2D, 0);

        // GLuint     brick_texture;
        // glGenTextures(1, &brick_texture);
        // glBindTexture(GL_TEXTURE_2D, brick_texture);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, brick.width(), brick.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, brick.data());
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // glBindTexture(GL_TEXTURE_2D, 0);

        // wood = p6::load_image_buffer("./assets/textures/stele.png") ;   

        // textures.push_back(p6::load_image_buffer("./assets/textures/wood.png"));
        // textures.push_back(p6::load_image_buffer("./assets/textures/red_brick_draw.png"));
        // textures.push_back(p6::load_image_buffer("./assets/textures/stele.png"));
        // textures.push_back(p6::load_image_buffer("./assets/textures/rock.png"));

        ObjectProgram magicProgram ; 
        ObjectProgram puitProgram ; 


    std::vector<Boid> boids;
    std::vector<Obstacle> obstacles;
    std::vector<Cloud> clouds;
    std::map<std::string, Material> materialMap;

    FreeflyCamera ViewMatrix;

    bool Z = false;
    bool S = false;
    bool Q = false;
    bool D = false;

    IHM ihm ;
    Loader loader ; 
int nb_slot = 0;
    std::vector<FacesGroup> puit = loader.LoadFromFile("./assets/models/puit.obj", materialMap, nb_slot);
    std::vector<FacesGroup> magic = loader.LoadFromFile("./assets/models/magique.obj", materialMap, nb_slot);
    std::vector<FacesGroup> content = loader.LoadFromFile("./assets/models/content.obj", materialMap, nb_slot);
    std::vector<FacesGroup> fir1 = loader.LoadFromFile("./assets/models/fir1.obj", materialMap, nb_slot);
    std::vector<FacesGroup> fir2 = loader.LoadFromFile("./assets/models/fir2.obj", materialMap, nb_slot);
    std::vector<FacesGroup> fir3 = loader.LoadFromFile("./assets/models/fir3.obj", materialMap, nb_slot);
    std::vector<FacesGroup> mushroom1 = loader.LoadFromFile("./assets/models/mushroom1.obj", materialMap, nb_slot);
    std::vector<FacesGroup> mushroom2 = loader.LoadFromFile("./assets/models/mushroom2.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rock1 = loader.LoadFromFile("./assets/models/rock1.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rock2 = loader.LoadFromFile("./assets/models/rock2.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rock3 = loader.LoadFromFile("./assets/models/rock3.obj", materialMap, nb_slot);
    std::vector<FacesGroup> house = loader.LoadFromFile("./assets/models/house.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rocks = loader.LoadFromFile("./assets/models/rocks.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rail = loader.LoadFromFile("./assets/models/rail.obj", materialMap, nb_slot);
    std::vector<FacesGroup> barel = loader.LoadFromFile("./assets/models/barel.obj", materialMap, nb_slot);
    std::vector<FacesGroup> cloud = loader.LoadFromFile("./assets/models/cloud1.obj", materialMap, nb_slot);
    // std::vector<FacesGroup> panneau = loader.LoadFromFile("./assets/models/panneau.obj", materialMap, nb_slot);

    
     for(int i=0 ; i<ihm.get_nb_boids() ; i++){
         Boid b(rock1, puitProgram) ;
         boids.push_back(b);
     }

    for(int i=0; i < ihm.get_nb_obstacles(); i++){
        float j = p6::random::number(); 
        if(j < 0.2) {
            obstacles.push_back(Obstacle(fir1, magicProgram));
        } else if(j < 0.4) {
            obstacles.push_back(Obstacle(fir2, magicProgram));
        } else if (j < 0.6){
            obstacles.push_back(Obstacle(fir3, magicProgram));
        } else if(j < 0.65) {
            obstacles.push_back(Obstacle(mushroom1, magicProgram));
        } else if (j < 0.7){
            obstacles.push_back(Obstacle(mushroom2, magicProgram));
        }else if (j < 0.8){
            obstacles.push_back(Obstacle(rock1, magicProgram));
        } else if(j < 0.9) {
            obstacles.push_back(Obstacle(rock2, magicProgram));
        } else {
            obstacles.push_back(Obstacle(rock3, magicProgram));
        }
    }

    obstacles.push_back(Obstacle(house, magicProgram, Vec(-4.0, 0.0, 0.0))) ;
    obstacles.push_back(Obstacle(puit, magicProgram, Vec(3.0, 0.0, 4.0))) ;
    obstacles.push_back(Obstacle(rail, magicProgram, Vec(-18.0, 0.0, 18.0))) ;
    obstacles.push_back(Obstacle(rocks, magicProgram, Vec(-4.0, 0.0, 4.0))) ;
    obstacles.push_back(Obstacle(barel, magicProgram, Vec(-4.0, 0.0, 0.0))) ;
    obstacles.push_back(Obstacle(magic, magicProgram, Vec(4.0, 0.0, -15.0))) ;
    // obstacles.push_back(Obstacle(panneau, magicProgram)) ;


    for(int i=0 ; i<3 ; i++){
         Cloud c(cloud, puitProgram) ;
         clouds.push_back(c);
     }

    Content box(content, magicProgram) ;
    Arpenteur Gaspard(barel, puitProgram) ; 




/* ---------------------------------------------------------------------------- */
/* ------------------ Declare your infinite update loop ----------------------- */
/* ---------------------------------------------------------------------------- */
    ctx.update = [&]() {
        glClearColor(0.7f, 0.6f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//gestion event
        if (Z) ViewMatrix.moveFront(0.1);
        if (S) ViewMatrix.moveFront(-0.1);
        if (Q) ViewMatrix.moveLeft(0.1);
        if (D) ViewMatrix.moveLeft(-0.1);

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
        for(auto& boid : boids){
            boid.draw(ViewMatrix, window_width, window_height, materialMap) ;
            boid.collision(boids, obstacles, ihm, ctx) ;
            boid.update_position() ;
        };


        for(auto& obstacle : obstacles){
            obstacle.draw(ViewMatrix, window_width, window_height, materialMap) ;
        };

        for(auto& cloud : clouds){
            cloud.draw(ViewMatrix, window_width, window_height, materialMap) ;
            cloud.update_position(ctx) ;
        }

        // contentCube.draw(ViewMatrix, window_width, window_height, materialMap) ;
        box.draw(ViewMatrix, window_width, window_height, materialMap) ;
        Gaspard.draw(ViewMatrix, window_width, window_height, materialMap) ;
        Gaspard.update_position(ViewMatrix); 

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