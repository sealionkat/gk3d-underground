#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
  public:
    static constexpr const char *WindowTitle = "Underground";
    static const int ScreenWidth = 800;
    static const int ScreenHeight = 600;

    static constexpr float FOV = 45.0f;
    static constexpr float PerspectiveNear = 0.1f;
    static constexpr float PerspectiveFar = 100.0f;
};

#endif // !SETTINGS_H