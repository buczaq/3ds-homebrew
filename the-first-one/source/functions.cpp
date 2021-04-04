#include <3ds.h>

#include "functions.hpp"

// Notes for me:
// - there are 30 lines of text that can fit on top screen
// - lines are indexed [1;30]
// - there are 50 characters per line (so screen dims: 50x30 characters)

void updateRecentTouches(std::vector<touchPosition>& recentTouches, touchPosition touch)
{
    static std::uint32_t position = 0;

    if (position >= 60) {
        position = 0;
    }

    recentTouches[position] = touch;
}

void processNextFrame(
    ENextFrame& nextFrame,
    const std::uint32_t keyDown,
    std::uint32_t& frameTimer,
    touchPosition touch,
    std::vector<touchPosition> recentTouches
)
{
    static int frameNumber = 0;
    switch (nextFrame)
    {
        case ENextFrame::START:
            display_START();
            process_START(nextFrame, keyDown);
            frameNumber++;
            break;
        case ENextFrame::FIRST_HELLO:
            display_FIRST_HELLO(nextFrame, frameTimer);
            frameNumber++;
            break;
        case ENextFrame::FIRST_HELLO_USER_ACTION:
            process_FIRST_HELLO(nextFrame, (touch.px > 0) | (touch.py > 0));
            frameNumber++;
            break;
        case ENextFrame::FIRST_TOUCH:
            display_FIRST_TOUCH(nextFrame, frameTimer);
            frameNumber++;
            break;
        case ENextFrame::FIRST_TOUCH_USER_ACTION:
            process_FIRST_TOUCH(nextFrame, recentTouches);
            frameNumber++;
            break;
        case ENextFrame::WILL_YOU_HELP:
            display_WILL_YOU_HELP(nextFrame, frameTimer);
            frameNumber++;
            break;
        default:
            break;
    }

    printf("\x1b[29;0H                               frame: %d", frameNumber);
    printf("\x1b[30;0H                               state: %d", nextFrame);
}

void displayBlank()
{
    printf( "\x1b[1;0H                                                  ");
    printf( "\x1b[2;0H                                                  ");
    printf( "\x1b[3;0H                                                  ");
    printf( "\x1b[4;0H                                                  ");
    printf( "\x1b[5;0H                                                  ");
    printf( "\x1b[6;0H                                                  ");
    printf( "\x1b[7;0H                                                  ");
    printf( "\x1b[8;0H                                                  ");
    printf( "\x1b[9;0H                                                  ");
    printf("\x1b[10;0H                                                  ");
    printf("\x1b[11;0H                                                  ");
    printf("\x1b[12;0H                                                  ");
    printf("\x1b[13;0H                                                  ");
    printf("\x1b[14;0H                                                  ");
    printf("\x1b[15;0H                                                  ");
    printf("\x1b[16;0H                                                  ");
    printf("\x1b[17;0H                                                  ");
    printf("\x1b[18;0H                                                  ");
    printf("\x1b[19;0H                                                  ");
    printf("\x1b[20;0H                                                  ");
    printf("\x1b[21;0H                                                  ");
    printf("\x1b[22;0H                                                  ");
    printf("\x1b[23;0H                                                  ");
    printf("\x1b[24;0H                                                  ");
    printf("\x1b[25;0H                                                  ");
    printf("\x1b[26;0H                                                  ");
    printf("\x1b[27;0H                                                  ");
    printf("\x1b[28;0H                                                  ");
    printf("\x1b[29;0H                                                  ");
    printf("\x1b[30;0H                                                  ");
}

void display_START()
{
    printf( "\x1b[1;0H                                                  ");
    printf( "\x1b[2;0H                                                  ");
    printf( "\x1b[3;0H                                                  ");
    printf( "\x1b[4;0H                                                  ");
    printf( "\x1b[5;0H                                                  ");
    printf( "\x1b[6;0H                                                  ");
    printf( "\x1b[7;0H                                                  ");
    printf( "\x1b[8;0H          #############################           ");
    printf( "\x1b[9;0H              LADY                                ");
    printf("\x1b[10;0H                    IN                            ");
    printf("\x1b[11;0H                         THE                      ");
    printf("\x1b[12;0H                               DARK               ");
    printf("\x1b[13;0H          #############################           ");
    printf("\x1b[14;0H                                                  ");
    printf("\x1b[15;0H                                                  ");
    printf("\x1b[16;0H                                                  ");
    printf("\x1b[17;0H                                                  ");
    printf("\x1b[18;0H                             by buczaq, 2021      ");
    printf("\x1b[19;0H                                                  ");
    printf("\x1b[20;0H                                                  ");
    printf("\x1b[21;0H                                                  ");
    printf("\x1b[22;0H   press START to begin...                        ");
}

void process_START(
    ENextFrame& nextFrame,
    const std::uint32_t keyDown
)
{
    if (keyDown & KEY_START) {
        nextFrame = ENextFrame::FIRST_HELLO;
    }
}

void display_FIRST_HELLO(ENextFrame& nextFrame, std::uint32_t& frameTimer)
{
    static bool clearNeeded = true;
    if (clearNeeded) {
        displayBlank();
        clearNeeded = false;
    }

    if (frameTimer > 200) {
        printf("\x1b[1;0HHello?");
    }
    if (frameTimer > 400) {
        printf("\x1b[2;0HAnybody here?");
    }
    if (frameTimer > 600) {
        printf("\x1b[3;0HCan you hear me? Please, give me some");
        printf("\x1b[4;0Hsignal that you can...");
    }
    if (frameTimer > 800) {
        printf("\x1b[5;0HLike... A touch?... Anything?...");
        nextFrame = ENextFrame::FIRST_HELLO_USER_ACTION;
        frameTimer = 0;
    }

    frameTimer++;
}

void process_FIRST_HELLO(ENextFrame& nextFrame, const bool pressedAnywhere)
{
    if (pressedAnywhere) {
        nextFrame = ENextFrame::FIRST_TOUCH;
    }
}

void display_FIRST_TOUCH(ENextFrame& nextFrame, std::uint32_t& frameTimer)
{
    static bool clearNeeded = true;
    if (clearNeeded) {
        displayBlank();
        clearNeeded = false;
    }

    if (frameTimer > 200) {
        printf("\x1b[1;0HOh... Oh my God!");
    }
    if (frameTimer > 400) {
        printf("\x1b[2;0HYes! I can feel you're here!");
    }
    if (frameTimer > 600) {
        printf("\x1b[3;0HPlease... I know this is so weird...");
    }
    if (frameTimer > 800) {
        printf("\x1b[4;0HBut could you help me a little?");
    }
    if (frameTimer > 1000) {
        printf("\x1b[6;0HDo... Do what you did before,");
        printf("\x1b[7;0Hbut from left to right.");
    }
    if (frameTimer > 1100) {
        printf("\x1b[9;0HOne smooth touch. Slowly. Please.");
        printf("\x1b[10;0HIt means a world to me...");
        nextFrame = ENextFrame::FIRST_TOUCH_USER_ACTION;
        frameTimer = 0;
    }

    frameTimer++;
}

void process_FIRST_TOUCH(ENextFrame& nextFrame, std::vector<touchPosition> recentTouches)
{
    std::uint32_t position = 0;
    bool breakTheLoop = false;

    while (!breakTheLoop) {
        if (position > 60) {
            breakTheLoop = true;
        }
        if (recentTouches[position].px < 30) {
            const std::uint32_t partitionPoint = position;
            std::uint32_t previousPositionX = recentTouches[position].px;
            for (; position < 60; position++) {
                if (recentTouches[position].px > previousPositionX) {
                    previousPositionX = recentTouches[position].px;
                    if (recentTouches[position].px > 290) {
                        nextFrame = ENextFrame::WILL_YOU_HELP;
                    }
                } else {
                    break;
                }
            }
            position = 0;
            for (; position < partitionPoint; position++) {
                if (recentTouches[position].px > previousPositionX) {
                    previousPositionX = recentTouches[position].px;
                    if (recentTouches[position].px > 290) {
                        nextFrame = ENextFrame::WILL_YOU_HELP;
                    }
                } else {
                    break;
                }
            }
            breakTheLoop = true;
        }
        position++;
    }
}

void display_WILL_YOU_HELP(ENextFrame& /*nextFrame*/, std::uint32_t& /*frameTimer*/)
{
    static bool clearNeeded = true;
    if (clearNeeded) {
        displayBlank();
        clearNeeded = false;
    }

    displayDebugNextStage();
}

void displayDebugNextStage()
{
    printf( "\x1b[1;0H   debug: next stage achieved");
    printf( "\x1b[3;0H   debug: to be finished");
    printf( "\x1b[5;0H   debug: mmmmmmbauks c:");
}
