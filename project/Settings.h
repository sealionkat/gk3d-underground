#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
  public:
    static const char *WindowTitle = 'Underground';
    static const int ScreenWidth = 800;
    static const int ScreenHeight = 600;

    static const FOV = 45.0f;
    static const PerspectiveNear = 0.1f;
    static const PerspectiveFar = 100f;
}

#endif // !SETTINGS_H