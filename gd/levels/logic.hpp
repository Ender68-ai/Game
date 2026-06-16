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

struct block
{
    float x;
    float y;
    float width;
    float height;
};

extern block blocks[];
extern const int blockCount;

struct EndRect
{
    float x;
    float y;
    float width;
    float height;
};

extern EndRect endRect;

class StereoMadness
{
public:
    void run();
};
