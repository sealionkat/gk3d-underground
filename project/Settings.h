#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
  static const int OpenGLMajorVersion = 3;
  static const int OpenGLMinorVersion = 3;

  static constexpr const GLchar *VertexPath = "shaders/vertexShader.glsl";
  static constexpr const GLchar *FragmentPath = "shaders/fragmentShader.glsl";

  static constexpr const char *WindowTitle = "Underground";
  static const GLuint ScreenWidth = 1366;
  static const GLuint ScreenHeight = 768;

  static constexpr const float FOV = 45.0f;
  static constexpr const float PerspectiveNear = 0.1f;
  static constexpr const float PerspectiveFar = 100.0f;

  static const int ForwardKey = GLFW_KEY_W;
  static const int BackwardKey = GLFW_KEY_S;
  static const int LeftKey = GLFW_KEY_A;
  static const int RightKey = GLFW_KEY_D;
  static const int UpKey = GLFW_KEY_Q;
  static const int DownKey = GLFW_KEY_E;

  static constexpr const GLfloat CameraSpeed = 5.0f;
  static constexpr const GLfloat MouseSensitivity = 0.05f;

  static constexpr const char* objectColorLoc = "objectColor";
  static constexpr const char* viewPosLoc = "viewPos";

  static constexpr const char* materialAmbientLoc = "material.ambient";
  static constexpr const char* materialDiffuseLoc = "material.diffuse";
  static constexpr const char* materialSpecularLoc = "material.specular";
  static constexpr const char* materialShininessLoc = "material.shininess";

  static constexpr const char* modelMatrixLoc = "model";
  static constexpr const char* viewMatrixLoc = "view";
  static constexpr const char* projectionMatrixLoc = "projection";


private:
  Settings() = delete;
  Settings(const Settings &) = delete;
  const Settings &operator=(const Settings &) = delete;
};

#endif // !SETTINGS_H