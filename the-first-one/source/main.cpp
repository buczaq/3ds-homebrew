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

        gfxFlushBuffers();
        gfxSwapBuffers();

        gspWaitForVBlank();

        frame++;
    }

    gfxExit();
    return 0;
}
