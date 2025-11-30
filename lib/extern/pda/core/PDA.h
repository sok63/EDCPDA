#pragma once

#include <cstdint>
#include <vector>

class PDA
{
public:
    void run_cycle();

private:
    uint32_t default_app_uid = 0;
};