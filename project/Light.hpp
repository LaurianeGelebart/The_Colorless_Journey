#pragma once

#include "glm/glm.hpp"

class Light {
protected:
    explicit Light(const glm::vec3& position);
    glm::vec3 _position;
    glm::vec3 _environmentPosition;

public:
    virtual ~Light() = default;
    Light();
    Light(const Light&)                            = default;
    Light(Light&&)                                 = delete;
    auto         operator=(const Light&) -> Light& = default;
    auto         operator=(Light&&) -> Light&      = delete;
    auto         getPosition() const -> glm::vec3;
    void         setPosition(const glm::vec3& position);
    virtual void update(const glm::mat4& viewMatrix) = 0;
};

class PointLight : public Light {
public:
    ~PointLight() override                           = default;
    PointLight(const PointLight&)                    = default;
    PointLight(PointLight&&)                         = delete;
    auto operator=(const PointLight&) -> PointLight& = default;
    auto operator=(PointLight&&) -> PointLight&      = delete;
    explicit PointLight(const glm::vec3& position);
    void update(const glm::mat4& viewMatrix) override;
};

class DirectionalLight : public Light {
public:
    ~DirectionalLight() override                                 = default;
    DirectionalLight(const DirectionalLight&)                    = default;
    DirectionalLight(DirectionalLight&&)                         = delete;
    auto operator=(const DirectionalLight&) -> DirectionalLight& = default;
    auto operator=(DirectionalLight&&) -> DirectionalLight&      = delete;
    explicit DirectionalLight(const glm::vec3& position);
    void update(const glm::mat4& viewMatrix) override;
};
