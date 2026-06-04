#include "stereomadness.hpp"

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
    {2080.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {2150.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {2700.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {3000.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {3070.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {3600.0f, GROUND_Y - 60.0f, 35.0f, 60.0f}
};

//define blocks (fix, doesnt display)

block blocks[] =
{
    {2500.0f, GROUND_Y - 200.0f, 200.0f, 20.0f},
    {2700.0f, GROUND_Y - 300.0f, 200.0f, 20.0f}
};

//define endrect for when level ends

EndRect endRect =
{
    4000.0f, GROUND_Y - 2000.0f, 100.0f, 2000.0f
};

const int spikeCount = sizeof(spikes) / sizeof(spikes[0]);
const int blockCount = sizeof(blocks) / sizeof(blocks[0]);

void StereoMadness::run()
{
}