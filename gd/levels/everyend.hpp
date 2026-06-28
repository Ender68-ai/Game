#pragma once
#include <raylib.h>
#include "logic.hpp"

extern Spike spikes_everyend[];
extern block blocks_everyend[];
extern EndRect endRect_everyend;
extern const int spikeCount_everyend;
extern const int blockCount_everyend;

class EveryEnd
{
public:
    void run();
};