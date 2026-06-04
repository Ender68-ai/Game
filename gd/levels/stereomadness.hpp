#pragma once

#include <raylib.h>

struct Spike
{
    float x;
    float y;
    float width;
    float height;
};

extern Spike spikes[];
extern const int spikeCount;

class StereoMadness
{
public:
    void run();
};