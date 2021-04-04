#include "ENextFrame.hpp"
#include "functions.hpp"

#include <3ds.h>
#include <cstdint>
#include <cstdio>
#include <memory>

int main(int argc, char **argv) {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    ENextFrame nextFrame{ENextFrame::START};

    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();
        const std::uint32_t keyDown = hidKeysDown();

        processNextFrame(nextFrame, keyDown);
        // hidScanInput();
        
        // touchPosition touch;
        // hidTouchRead(&touch);
        // printf("\x1b[1;0HX coordinate: %i       ",touch.px);
        // printf("\x1b[2;0HdY coordinate: %i       ",touch.py);

        // u32 kHeld = hidKeysHeld();
        // if (kHeld & KEY_TOUCH)
        //     printf("\x1b[3;0HIs Active: TRUE ");
        // else
        //     printf("\x1b[3;0HIs Active: FALSE");

        gfxFlushBuffers();
        gfxSwapBuffers();

        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
