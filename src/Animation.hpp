#pragma once

class Animation
{
  public:
    unsigned int index;
    unsigned int numFrames;
    unsigned int animationSpeed;
    Animation();
    Animation(unsigned index, unsigned numFrames, unsigned animationSpeed);
};
