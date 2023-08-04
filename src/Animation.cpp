#include "Animation.hpp"

Animation::Animation()
{
}

Animation::Animation(unsigned index, unsigned numFrames, unsigned animationSpeed)
{
    this->index = index;
    this->numFrames = numFrames;
    this->animationSpeed = animationSpeed;
}
