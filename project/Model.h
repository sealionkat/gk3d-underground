#ifdef MODEL_H
#define MODEL_H

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Model
{
  public:
    glm::vec3 Position;
    glm::vec3 Color;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLfloat shininess;

    GLfloat vertices[];
}

#endif // !MODEL_H