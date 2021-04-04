#include <3ds.h>

#include "functions.hpp"

// Notes for me:
// - there are 30 lines of text that can fit on top screen
// - lines are indexed [1;30]
// - there are 50 characters per line (so screen dims: 50x30 characters)

void processNextFrame(
    ENextFrame& nextFrame,
    const std::uint32_t keyDown
)
{
    static int frameNumber = 0;
    switch (nextFrame)
    {
        case ENextFrame::START:
            displayStartScreen();
            process_START(nextFrame, keyDown);
            frameNumber++;
            break;
        case ENextFrame::FIRST_HELLO:
            displayDebugNextStage();
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

void displayStartScreen()
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
    printf( "\x1b[1;0H   debug: in start");
    if (keyDown & KEY_START) {
        nextFrame = ENextFrame::FIRST_HELLO;
    }
}

void displayDebugNextStage()
{
    displayBlank();
    printf( "\x1b[1;0H   debug: next stage achieved");
}