#include "logic.hpp"

static constexpr float GROUND_Y = 1000.0f;

//define spike locations and dimensions

Spike spikes[] =
{
    {1000.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {1070.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {1140.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {1540.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {1610.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {1680.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {2450.0f, GROUND_Y - 160.0f, 35.0f, 60.0f},
    {3000.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {3500.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {3970.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {4400.0f, GROUND_Y - 60.0f, 35.0f, 60.0f}
};

block blocks[] =
{
    {2280.0f, GROUND_Y - 100.0f, 100.0f, 100.0f},
    {2380.0f, GROUND_Y - 100.0f, 100.0f, 100.0f}
};

//define endrect for when level ends

EndRect endRect =
{
    5250.0f, GROUND_Y - 2000.0f, 100.0f, 2000.0f
};

const int spikeCount = sizeof(spikes) / sizeof(spikes[0]);
const int blockCount = sizeof(blocks) / sizeof(blocks[0]);

void StereoMadness::run()
{
}
