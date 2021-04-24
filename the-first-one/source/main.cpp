#include "ENextFrame.hpp"
#include "functions.hpp"

#include <3ds.h>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <vector>

int main(int argc, char **argv) {
    gfxInitDefault();
    // Thanks to this we can see a console and print there.
    consoleInit(GFX_TOP, NULL);

    ENextFrame nextFrame = ENextFrame::START;
    // For delaying stuff :)
    std::uint32_t frameTimer = 0;
    std::uint32_t frame = 0;

    // How often new touch should be registered to recentTouches.
    constexpr std::uint32_t touchUpdateFrequency = 10;
    std::vector<touchPosition> recentTouches{};
    // 60 recent touches kept in this vector.
    recentTouches.resize(60);

    csndInit();

    // one loop = one frame
    while (aptMainLoop())
    {
        // Once per frame we get keys down...
        hidScanInput();
        const std::uint32_t keyDown = hidKeysDown();
        // ...and touch position.
        touchPosition touch;
        hidTouchRead(&touch);

        if (keyDown & KEY_START) {
            loadAudio("audio/Tranquility2.bin");
        }

        if (!(frame % touchUpdateFrequency)) {
            updateRecentTouches(recentTouches, touch);
        }

        // Displays current frame or proceeds user input. Yes, it is called around 60 times per second ;)
        processNextFrame(nextFrame, keyDown, frameTimer, touch, recentTouches);

        gfxFlushBuffers();
        gfxSwapBuffers();

        gspWaitForVBlank();

        frame++;
    }

    // Never reached, but left pro forma.
    stopAudio();
    csndExit();
    gfxExit();
    return 0;
}
