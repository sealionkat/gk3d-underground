/* test class */

#ifndef LIGHT_H
#define LIGHT_H

class Light
{
  public:
    vec3 Position;
    vec3 Color;

    Light(vec3 position, vec3 color)
    {
        this.Position = position;
        this.Color = color;
    }
}

#endif // !LIGHT_H