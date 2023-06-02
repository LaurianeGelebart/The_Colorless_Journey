#include "TrackballCamera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

static auto normalizeAngle(int angle) -> int;
static auto checkRotatingAngleX(float angle) -> bool;
static auto isCollisionBorder(glm::vec3 position) -> bool;
static auto checkMovingPosition(const glm::vec3& position, const std::vector<Obstacle>& obstacles) -> bool;
static auto isCollisionObstacles(const glm::vec3& position, const std::vector<Obstacle>& obstacles) -> bool;

TrackballCamera::TrackballCamera() = default;

void TrackballCamera::moveFront(float delta, const std::vector<Obstacle>& obstacles)
{
    float x = 0.f;
    float z = 0.f;

    int angle = normalizeAngle(static_cast<int>(this->_angleY));

    if (angle < 90)
    {
        z = ((90 - angle) / 90.f) * delta;
        x = -((angle) / 90.f) * delta;
    }
    else if (angle < 180)
    {
        z = -((angle - 90) / 90.f) * delta;
        x = -((180 - angle) / 90.f) * delta;
    }
    else if (angle < 270)
    {
        z = -((270 - angle) / 90.f) * delta;
        x = ((angle - 180) / 90.f) * delta;
    }
    else
    {
        z = ((angle - 270) / 90.f) * delta;
        x = ((360 - angle) / 90.f) * delta;
    }

    glm::vec3 newPosition = glm::vec3(this->_position.x + x, this->_position.y, this->_position.z + z);

    if (checkMovingPosition(newPosition, obstacles))
        this->_position = newPosition;
}

void TrackballCamera::moveLeft(float delta, const std::vector<Obstacle>& obstacles)
{
    float x = 0.f;
    float z = 0.f;

    int angle = normalizeAngle(static_cast<int>(_angleY - 90));

    if (angle < 90)
    {
        z = ((90 - angle) / 90.f) * delta;
        x = -((angle) / 90.f) * delta;
    }
    else if (angle < 180)
    {
        z = -((angle - 90) / 90.f) * delta;
        x = -((180 - angle) / 90.f) * delta;
    }
    else if (angle < 270)
    {
        z = -((270 - angle) / 90.f) * delta;
        x = ((angle - 180) / 90.f) * delta;
    }
    else
    {
        z = ((angle - 270) / 90.f) * delta;
        x = ((360 - angle) / 90.f) * delta;
    }

    glm::vec3 newPosition = glm::vec3(_position.x + x, _position.y, _position.z + z);

    if (checkMovingPosition(newPosition, obstacles))
        this->_position = newPosition;
}

void TrackballCamera::rotateLeft(float degrees)
{
    float newAngle = this->_angleX + degrees;
    if (checkRotatingAngleX(newAngle))
        this->_angleX = newAngle;
}

void TrackballCamera::rotateUp(float degrees)
{
    float newAngle = this->_angleY + degrees;
    this->_angleY  = newAngle;
}

auto TrackballCamera::getPosition() const -> glm::vec3
{
    return -this->_position;
}

auto TrackballCamera::getAngleX() const -> float
{
    return this->_angleX;
}

auto TrackballCamera::getAngleY() const -> float
{
    return this->_angleY;
}

auto TrackballCamera::getViewMatrix() const -> glm::mat4
{
    glm::mat4 viewMatrix(1.f);

    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.f, 0.f, -this->_distance));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(this->_angleX), glm::vec3(1.f, 0.f, 0.f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(this->_angleY), glm::vec3(0.f, 1.f, 0.f));
    viewMatrix = glm::translate(viewMatrix, this->_position);

    return viewMatrix;
}

static auto normalizeAngle(int angle) -> int
{
    if (angle < 0)
        angle = 360 - (-angle) % 360;
    else
        angle = angle % 360;
}

static auto checkRotatingAngleX(float angle) -> bool
{
    return angle >= 15 && angle <= 90;
}

static auto isCollisionBorder(glm::vec3 position) -> bool
{
    float margin = 0.3;
    float width  = 2.f;
    float length = 2.f;

    if (glm::abs(position.x) > (width - margin))
    {
        return true;
    }
    if (glm::abs(position.z) > (length - margin))
    {
        return true;
    }
    return false;
}

static auto checkMovingPosition(const glm::vec3& position, const std::vector<Obstacle>& obstacles) -> bool
{
    if (isCollisionBorder(position))
        return false;
    if (isCollisionObstacles(position, obstacles))
        return false;
    return true;
}

static auto isCollisionObstacles(const glm::vec3& position, const std::vector<Obstacle>& obstacles) -> bool
{
    // for(auto& obstacle : obstacles) {
    //     float distance = glm::distance(position, obstacle.getPosition());
    //     if(distance < 0.05) return true ;
    // }
    return false;
}