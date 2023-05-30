#include "Content.hpp"

Content::Content() = default;

Content::Content(const std::vector<ModelPart>& model, ObjectProgram& program)
    : Object(model, program)
{
    this->_position = glm::vec3(0.f);
    this->_scale    = 0.1;
}
