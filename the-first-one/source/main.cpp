#include "ENextFrame.hpp"
#include "functions.hpp"

#include <3ds.h>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <vector>

int main(int argc, char **argv) {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    ENextFrame nextFrame = ENextFrame::START;
    std::uint32_t frameTimer = 0;
    std::uint32_t frame = 0;
    constexpr std::uint32_t touchUpdateFrequency = 10;
    std::vector<touchPosition> recentTouches{};
    recentTouches.resize(60);

    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();
        const std::uint32_t keyDown = hidKeysDown();
        touchPosition touch;
        hidTouchRead(&touch);
        if (!(frame % touchUpdateFrequency)) {
            updateRecentTouches(recentTouches, touch);
        }

        processNextFrame(nextFrame, keyDown, frameTimer, touch, recentTouches);
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

        frame++;
    }

    gfxExit();
    return 0;
}
