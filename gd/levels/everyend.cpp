#include "everyend.hpp"
#include "logic.hpp"

static constexpr float GROUND_Y = 1000.0f;

Spike spikes_everyend[] =
{
    {800.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {900.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {1000.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {1500.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {2000.0f, GROUND_Y - 60.0f, 35.0f, 60.0f},
    {2500.0f, GROUND_Y - 60.0f, 35.0f, 60.0f}
};

block blocks_everyend[] =
{
    {1300.0f, GROUND_Y - 100.0f, 100.0f, 100.0f},
    {1400.0f, GROUND_Y - 100.0f, 100.0f, 100.0f},
    {1800.0f, GROUND_Y - 200.0f, 100.0f, 100.0f}
};

EndRect endRect_everyend =
{
    3200.0f, GROUND_Y - 2000.0f, 100.0f, 2000.0f
};

const int spikeCount_everyend = sizeof(spikes_everyend) / sizeof(spikes_everyend[0]);
const int blockCount_everyend = sizeof(blocks_everyend) / sizeof(blocks_everyend[0]);

void EveryEnd::run()
{
}