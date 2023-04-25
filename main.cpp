#include <vector>
#include "glimac/FreeflyCamera.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"


struct EarthProgram 
{
    p6::Shader m_Program;

    GLint      uMVPMatrix;
    GLint      uMVMatrix;
    GLint      uNormalMatrix;

    GLint uKd;
    GLint uKs;
    GLint uShininess;

    //GLint uLightPos_vs;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    // EarthProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/pointlight.fs.glsl"))
    EarthProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/directionallight.fs.glsl"))
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");

        uKd        = glGetUniformLocation(m_Program.id(), "uKd");
        uKs        = glGetUniformLocation(m_Program.id(), "uKs");
        uShininess = glGetUniformLocation(m_Program.id(), "uShininess");

        //uLightPos_vs    = glGetUniformLocation(m_Program.id(), "uLightPos_vs");
        uLightDir_vs    = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.id(), "uLightIntensity");
    }
};

struct MoonProgram 
{
    p6::Shader m_Program;

    GLint      uMVPMatrix;
    GLint      uMVMatrix;
    GLint      uNormalMatrix;

    GLint uKd;
    GLint uKs;
    GLint uShininess;

    //GLint uLightPos_vs;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    // MoonProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/pointlight.fs.glsl"))
    MoonProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/directionallight.fs.glsl"))
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");

        uKd        = glGetUniformLocation(m_Program.id(), "uKd");
        uKs        = glGetUniformLocation(m_Program.id(), "uKs");
        uShininess = glGetUniformLocation(m_Program.id(), "uShininess");

        //uLightPos_vs    = glGetUniformLocation(m_Program.id(), "uLightPos_vs");
        uLightDir_vs    = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.id(), "uLightIntensity");
    }
};


/* ---------------------------------------------------------------------------- */
/* --------------------------------- MAIN ------------------------------------- */
/* ---------------------------------------------------------------------------- */
int main()
{
    int  window_width  = 1920;
    int  window_height = 1080;
    auto ctx = p6::Context{{window_width, window_height, "Project qui se passe super bien"}};
    ctx.maximize_window();

    EarthProgram earthProgram;
    MoonProgram  moonProgram;
    FreeflyCamera ViewMatrix ; 

    const int nb_lunes = 32 ; 
    
    bool Z = false;
    bool S = false;
    bool Q = false;
    bool D = false;

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / (float)window_height, 0.1f, 100.f);
    glm::mat4 MVMatrix ; 

    std::vector<glm::vec3> rot_axis ; 
    std::vector<glm::vec3> axis ; 
    std::vector<glm::vec3> colors ; 

    for (int i=0 ; i<nb_lunes ; i++){
        rot_axis.push_back(glm::sphericalRand(1.0)); 
        axis.push_back(glm::ballRand(10.0)); 
        colors.push_back(glm::sphericalRand(1.0));
    }


// Création d'un  VBO:
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    const std::vector<glimac::ShapeVertex> sphere = glimac::sphere_vertices(1.f, 32, 16);  

    glBufferData(GL_ARRAY_BUFFER, sphere.size()*sizeof(glimac::ShapeVertex), sphere.data(), GL_STATIC_DRAW);


// Création d'un VAO:
    GLuint vao;
    glGenVertexArrays(1, &vao) ; 
    glBindVertexArray(vao) ; 

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    // const GLuint VERTEX_ATTR_TEXTURE = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION) ; 
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL) ; 
    // glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE) ; 

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    // glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0) ; 

    glEnable(GL_DEPTH_TEST) ; 




/* ---------------------------------------------------------------------------- */
/* ------------------ Declare your infinite update loop ----------------------- */
/* ---------------------------------------------------------------------------- */
    ctx.update = [&]() {
        glClearColor(0.f, 0.f, 0.f, 1.f);
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

        glBindVertexArray(vao) ;

//dessin de la terre   
        earthProgram.m_Program.use();

        // glUniform1i(earthProgram.locuTexture1, 0);
        // glUniform1i(earthProgram.locuTexture2, 1);
       
        glm::mat4 earthMVMatrix = ViewMatrix.getViewMatrix();  
        earthMVMatrix = glm::scale(earthMVMatrix, glm::vec3(0.5));  

        glm::mat4 VLightMatrix = ViewMatrix.getViewMatrix() ; 
        glm::mat4 MLightMatrix = glm::rotate(glm::mat4(1), ctx.time(), glm::vec3(0,1,0)); 
       // glm::vec3 lightPos = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,0,1) );
        glm::vec3 lightDir = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,1,0) );
        
        glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
        glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
        glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * earthMVMatrix));        
        
        earthMVMatrix = glm::rotate(earthMVMatrix, ctx.time(), glm::vec3(0, 1, 0));
        
        glUniform1f(earthProgram.uShininess, 0.5); 
        glUniform3fv(earthProgram.uKd, 1, glm::value_ptr(glm::vec3(0.2,0.5,0.5))); 
        glUniform3fv(earthProgram.uKs, 1, glm::value_ptr(glm::vec3(0.1,0.2,0.2))); 
        // glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(lightPos)); 
        glUniform3fv(earthProgram.uLightDir_vs, 1, glm::value_ptr(lightDir)); 
        glUniform3fv(earthProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(1))); 

        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, earthTexture);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, terre_texture->getWidth(), terre_texture->getHeight(), 0, GL_RGBA, GL_FLOAT, terre_texture->getPixels()  ) ;
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, cloudTexture);

        glDrawArrays(GL_TRIANGLES, 0, sphere.size());

        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, 0);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, 0);

//dessin des lunes
        moonProgram.m_Program.use();
        for (uint32_t i=0 ; i<nb_lunes ; i++){
            // glActiveTexture(GL_TEXTURE0);
            // glBindTexture(GL_TEXTURE_2D, earthTexture);
            // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lune_texture->getWidth(), lune_texture->getHeight(), 0, GL_RGBA, GL_FLOAT, lune_texture->getPixels()  ) ;

            MVMatrix = ViewMatrix.getViewMatrix();
            MVMatrix = glm::scale(MVMatrix, glm::vec3(0.1));   
            MVMatrix = glm::rotate(MVMatrix, ctx.time(), glm::vec3(rot_axis[i])); 
            MVMatrix = glm::translate(MVMatrix, glm::vec3(axis[i])); 

            glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix)); 
            glUniformMatrix4fv(moonProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix)))); 
            glUniformMatrix4fv(moonProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix)); 

            glUniform1f(moonProgram.uShininess, 0.5); 
            glUniform3fv(moonProgram.uKd, 1, glm::value_ptr(glm::vec3(colors[i]))); 
            glUniform3fv(moonProgram.uKs, 1, glm::value_ptr(glm::vec3(0.1,0.2,0.2))); 
            // glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(lightPos)); 
            glUniform3fv(moonProgram.uLightDir_vs, 1, glm::value_ptr(lightDir)); 
            glUniform3fv(moonProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.5))); 
            
            glDrawArrays(GL_TRIANGLES, 0, sphere.size()*sizeof(glimac::ShapeVertex));
        }

        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, 0); 
        
        glBindVertexArray(0) ; 


// event part 2
        

    };

    ctx.start();
    glDeleteBuffers(0, &vbo); 
    glDeleteVertexArrays(0, &vao); 
    glfwTerminate();
}