#include "TrackballCamera.hpp"


static int normalizeAngle(int angle) 
{
    if (angle < 0)angle = 360 - (-angle) % 360;
    else angle = angle % 360;
}

TrackballCamera::TrackballCamera(){}

void TrackballCamera::moveFront(float delta)
{
    float x = 0.f;
    float z = 0.f;

    int angle = normalizeAngle(static_cast<int>(_angleY)); 

    if (angle < 90) {
        z = ((90 - angle) / 90.f) * delta;
        x = -((angle) / 90.f) * delta;
    } 
    else if (angle < 180) {
        z = -((angle - 90) / 90.f) * delta;
        x = -((180 - angle) / 90.f) * delta;
    } 
    else if (angle < 270) {
        z = -((270 - angle) / 90.f) * delta;
        x = ((angle - 180) / 90.f) * delta;
    } 
    else {
        z = ((angle - 270) / 90.f) * delta;
        x = ((360 - angle) / 90.f) * delta;
    }

    Vec newPosition = glm::vec3(_position.x + x, _position.y, _position.z + z); 
    
    if(checkMovingPosition(newPosition)) _position = newPosition ;
}

void TrackballCamera::moveLeft(float delta)
{
    float x = 0.f;
    float z = 0.f;

    int angle = normalizeAngle(static_cast<int>(_angleY - 90)); 

    if (angle < 90){
        z = ((90 - angle) / 90.f) * delta;
        x = -((angle) / 90.f) * delta;
    } 
    else if (angle < 180){
        z = -((angle - 90) / 90.f) * delta;
        x = -((180 - angle) / 90.f) * delta;
    }
    else if (angle < 270){
        z = -((270 - angle) / 90.f) * delta;
        x = ((angle - 180) / 90.f) * delta;
    }
    else {
        z = ((angle - 270) / 90.f) * delta;
        x = ((360 - angle) / 90.f) * delta;
    }

    Vec newPosition = glm::vec3(_position.x + x, _position.y, _position.z + z); 
    
    if(checkMovingPosition(newPosition)) this->_position = newPosition ;
}


void TrackballCamera::rotateLeft(float degrees)
{
    float newAngle = this-> _angleX + degrees ;
    if(checkRotatingAngleX(newAngle))this->_angleX = newAngle ; 
}

void TrackballCamera::rotateUp(float degrees)
{
    float newAngle = this-> _angleY + degrees ;
    if(checkRotatingAngleY(newAngle)) this->_angleY = newAngle ; 
}

Vec TrackballCamera::getPosition() const
{
    return -_position;
}

float TrackballCamera::getAngleY() const
{
    return _angleY;
}

glm::mat4 TrackballCamera::getViewMatrix() const 
{
    glm::mat4 viewMatrix(1.f);

    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.f, 0.f, -_distance));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(_angleX), glm::vec3(1.f, 0.f, 0.f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(_angleY), glm::vec3(0.f, 1.f, 0.f));
    viewMatrix = glm::translate(viewMatrix, _position);

    return viewMatrix;
}

bool TrackballCamera::checkMovingPosition(Vec position) const
{
    float margin = 0.3; 
    float width = 2.f; 
    float length = 2.f; 

    if (glm::abs(position.x) > (width-margin)){ 
        return false;
    }
    if (glm::abs(position.z) > (length-margin)){
        return false; 
    }
    
    return true ; 
}


bool TrackballCamera::checkRotatingAngleX(float angle) const
{
    if(angle<10 || angle>90) return false  ;
    return true ; 
}

bool TrackballCamera::checkRotatingAngleY(float angle) const
{
    
    return true ; 
}
    