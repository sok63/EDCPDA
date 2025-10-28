#pragma once 

#include <M5Unified.h>

#include <pda/ADevice.h>



class PaperS3: public ADevice {
public:
    void init() override;
    void launch() override;

    void update() override;
    void powerOff() override;
};