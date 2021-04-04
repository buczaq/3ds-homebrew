#pragma once

#include "ENextFrame.hpp"

#include <3ds.h>
#include <memory>
#include <cstdint>
#include <cstdio>
#include <vector>

void updateRecentTouches(std::vector<touchPosition>& recentTouches, touchPosition touch);

void displayBlank();

void display_START();

void process_START(
    ENextFrame& nextFrame,
    const std::uint32_t keyDown
);

void display_FIRST_HELLO(ENextFrame& nextFrame, std::uint32_t& frameTimer);

void process_FIRST_HELLO(ENextFrame& nextFrame, const bool pressedAnywhere);

void display_FIRST_TOUCH(ENextFrame& nextFrame, std::uint32_t& frameTimer);

void process_FIRST_TOUCH(ENextFrame& nextFrame, std::vector<touchPosition> recentTouches);

void display_WILL_YOU_HELP(ENextFrame& nextFrame, std::uint32_t& frameTimer);

void process_WILL_YOU_HELP(ENextFrame& nextFrame, const bool pressedOnRight);

void display_AGREED_TO_HELP(ENextFrame& nextFrame, std::uint32_t& frameTimer);

void process_AGREED_TO_HELP(ENextFrame& nextFrame, const bool pressedAnywhere);

void display_LABYRINTH(ENextFrame& nextFrame);

void process_LABYRINTH(ENextFrame& nextFrame, std::vector<touchPosition> recentTouches);

void display_ESCAPED(ENextFrame& nextFrame, std::uint32_t& frameTimer);

void display_FACE(ENextFrame& nextFrame, std::uint32_t& frameTimer);

void display_ENDING();

void displayDebugNextStage();

void processNextFrame(
    ENextFrame& nextFrame,
    const std::uint32_t keyDown,
    std::uint32_t& frameTimer,
    touchPosition touch,
    std::vector<touchPosition> recentTouches
);

