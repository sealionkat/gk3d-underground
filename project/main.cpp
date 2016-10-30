#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Settings.h"
#include "Shader.h"
#include "Model.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void do_movement();

const GLuint WIDTH = Settings::ScreenWidth, HEIGHT = Settings::ScreenHeight;

// Light
glm::vec3 lightPos(0.0f, 0.0f, 4.0f);

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];

// Deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Settings::OpenGLMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Settings::OpenGLMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, Settings::WindowTitle, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    /* Shaders initialization */
    std::cout << "Preparing shaders..." << std::endl;

    const GLchar *vertexPath = "shaders/vertexShader.glsl";
    const GLchar *fragmentPath = "shaders/fragmentShader.glsl";

    Shader shaderMtn(vertexPath, fragmentPath);

    /* /Shaders initialization */

    /* Objects setup */

    std::cout << "Preparing objects..." << std::endl;

    GLfloat vertices[] = {//position, normal
                          -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                          0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                          0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                          0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                          -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                          -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

                          -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                          0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                          0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                          0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                          -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                          -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

                          -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
                          -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
                          -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

                          0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
                          0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                          0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                          0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                          0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
                          0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

                          -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
                          0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
                          0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
                          0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
                          -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
                          -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

                          -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                          0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                          0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                          0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                          -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                          -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

    GLfloat verticesBig[] = {//position, normal
                             -5.0f, -5.0f, -5.0f, 0.0f, 0.0f, 1.0f,
                             5.0f, -5.0f, -5.0f, 0.0f, 0.0f, 1.0f,
                             5.0f, 5.0f, -5.0f, 0.0f, 0.0f, 1.0f,
                             5.0f, 5.0f, -5.0f, 0.0f, 0.0f, 1.0f,
                             -5.0f, 5.0f, -5.0f, 0.0f, 0.0f, 1.0f,
                             -5.0f, -5.0f, -5.0f, 0.0f, 0.0f, 1.0f,

                             -5.0f, -5.0f, 5.0f, 0.0f, 0.0f, -1.0f,
                             5.0f, -5.0f, 5.0f, 0.0f, 0.0f, -1.0f,
                             5.0f, 5.0f, 5.0f, 0.0f, 0.0f, -1.0f,
                             5.0f, 5.0f, 5.0f, 0.0f, 0.0f, -1.0f,
                             -5.0f, 5.0f, 5.0f, 0.0f, 0.0f, -1.0f,
                             -5.0f, -5.0f, 5.0f, 0.0f, 0.0f, -1.0f,

                             -5.0f, 5.0f, 5.0f, 1.0f, 0.0f, 0.0f,
                             -5.0f, 5.0f, -5.0f, 1.0f, 0.0f, 0.0f,
                             -5.0f, -5.0f, -5.0f, 1.0f, 0.0f, 0.0f,
                             -5.0f, -5.0f, -5.0f, 1.0f, 0.0f, 0.0f,
                             -5.0f, -5.0f, 5.0f, 1.0f, 0.0f, 0.0f,
                             -5.0f, 5.0f, 5.0f, 1.0f, 0.0f, 0.0f,

                             5.0f, 5.0f, 5.0f, -1.0f, 0.0f, 0.0f,
                             5.0f, 5.0f, -5.0f, -1.0f, 0.0f, 0.0f,
                             5.0f, -5.0f, -5.0f, -1.0f, 0.0f, 0.0f,
                             5.0f, -5.0f, -5.0f, -1.0f, 0.0f, 0.0f,
                             5.0f, -5.0f, 5.0f, -1.0f, 0.0f, 0.0f,
                             5.0f, 5.0f, 5.0f, -1.0f, 0.0f, 0.0f,

                             -5.0f, -5.0f, -5.0f, 0.0f, 1.0f, 0.0f,
                             5.0f, -5.0f, -5.0f, 0.0f, 1.0f, 0.0f,
                             5.0f, -5.0f, 5.0f, 0.0f, 1.0f, 0.0f,
                             5.0f, -5.0f, 5.0f, 0.0f, 1.0f, 0.0f,
                             -5.0f, -5.0f, 5.0f, 0.0f, 1.0f, 0.0f,
                             -5.0f, -5.0f, -5.0f, 0.0f, 1.0f, 0.0f,

                             -5.0f, 5.0f, -5.0f, 0.0f, -1.0f, 0.0f,
                             5.0f, 5.0f, -5.0f, 0.0f, -1.0f, 0.0f,
                             5.0f, 5.0f, 5.0f, 0.0f, -1.0f, 0.0f,
                             5.0f, 5.0f, 5.0f, 0.0f, -1.0f, 0.0f,
                             -5.0f, 5.0f, 5.0f, 0.0f, -1.0f, 0.0f,
                             -5.0f, 5.0f, -5.0f, 0.0f, -1.0f, 0.0f};

    // VBO, VAO
    GLuint VBO, VAO, VBOBig, VAOBig;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAOBig);
    glGenBuffers(1, &VBOBig);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0); //location 0 - position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat))); //location 1 - normal
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindVertexArray(VAOBig);

    glBindBuffer(GL_ARRAY_BUFFER, VBOBig);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBig), verticesBig, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0); //location 0 - position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat))); //location 1 - normal
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    /* /Objects setup */

    // Game loop
    std::cout << "Starting main loop!" << std::endl;
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        do_movement();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderMtn.Use();

        GLint objectColorLoc = glGetUniformLocation(shaderMtn.Program, "objectColor");
        GLint lightColorLoc = glGetUniformLocation(shaderMtn.Program, "lightColor");
        GLint lightPosLoc = glGetUniformLocation(shaderMtn.Program, "lightPos");
        GLint viewPosLoc = glGetUniformLocation(shaderMtn.Program, "viewPos");

        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);

        GLint matAmbientLoc = glGetUniformLocation(shaderMtn.Program, "material.ambient");
        GLint matDiffuseLoc = glGetUniformLocation(shaderMtn.Program, "material.diffuse");
        GLint matSpecularLoc = glGetUniformLocation(shaderMtn.Program, "material.specular");
        GLint matShinyLoc = glGetUniformLocation(shaderMtn.Program, "material.shininess");

        glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
        glUniform1f(matShinyLoc, 32.0f);

        GLint lightConstLoc = glGetUniformLocation(shaderMtn.Program, "lightConstant");
        GLint lightLinLoc = glGetUniformLocation(shaderMtn.Program, "lightLinear");
        GLint lightQuadLoc = glGetUniformLocation(shaderMtn.Program, "lightQuadratic");

        glUniform1f(lightConstLoc, 1.0f);
        glUniform1f(lightLinLoc, 0.09f);
        glUniform1f(lightQuadLoc, 0.032f);

        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        projection = glm::perspective(glm::radians(Settings::FOV), (float)width / (float)height, Settings::PerspectiveNear, Settings::PerspectiveFar);

        GLint modelLoc = glGetUniformLocation(shaderMtn.Program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        GLint viewLoc = glGetUniformLocation(shaderMtn.Program, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLint projectionLoc = glGetUniformLocation(shaderMtn.Program, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glBindVertexArray(VAOBig);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    std::cout << "Terminating application..." << std::endl;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    std::cout << "Key: " << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
}

void do_movement()
{
    GLfloat cameraSpeed = Settings::CameraSpeed * deltaTime;
    if (keys[Settings::UpKey])
    {
        cameraPos += cameraSpeed * cameraUp;
    }
    if (keys[Settings::DownKey])
    {
        cameraPos -= cameraSpeed * cameraUp;
    }
    if (keys[Settings::ForwardKey])
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (keys[Settings::BackwardKey])
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (keys[Settings::LeftKey])
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (keys[Settings::RightKey])
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

bool firstMouse = true;
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = Settings::MouseSensitivity;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
