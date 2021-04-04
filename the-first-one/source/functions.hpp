#pragma once

#include "ENextFrame.hpp"

#include <memory>
#include <cstdint>
#include <cstdio>

void displayBlank();

void displayStartScreen();

void process_START(
    ENextFrame& nextFrame,
    const std::uint32_t keyDown
);

void displayDebugNextStage();

void processNextFrame(
    ENextFrame& nextFrame,
    const std::uint32_t keyDown
);

