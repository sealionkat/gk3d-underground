/* test class */

#ifndef LIGHT_H
#define LIGHT_H

class Light
{
  public:
    vec3 pos;

    Light(vec3 pos)
    {
        this.pos = pos;
    }
}

#endif // !LIGHT_H