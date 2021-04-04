#include <3ds.h>
#include <array>

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
        case ENextFrame::WILL_YOU_HELP_USER_ACTION:
            process_WILL_YOU_HELP(nextFrame, touch.px > 160);
            frameNumber++;
            break;
        case ENextFrame::AGREED_TO_HELP:
            display_AGREED_TO_HELP(nextFrame, frameTimer);
            frameNumber++;
            break;
        case ENextFrame::AGREED_TO_HELP_USER_ACTION:
            process_AGREED_TO_HELP(nextFrame, (touch.px > 0) | (touch.py > 0));
            frameNumber++;
            break;
        case ENextFrame::LABYRINTH:
            display_LABYRINTH(nextFrame);
            frameNumber++;
            break;
        case ENextFrame::LABYRINTH_USER_ACTION:
            process_LABYRINTH(nextFrame, recentTouches);
            frameNumber++;
            break;
        case ENextFrame::ESCAPED:
            display_ESCAPED(nextFrame, frameTimer);
            frameNumber++;
            break;
        case ENextFrame::FACE:
            display_FACE(nextFrame, frameTimer);
            frameNumber++;
            break;
        case ENextFrame::ENDING:
            display_ENDING();
            frameNumber++;
            break;
        default:
            break;
    }

    // uncomment for a simple debug
    // printf("\x1b[29;0H                               frame: %d", frameNumber);
    // printf("\x1b[30;0H                               state: %d", nextFrame);
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
        printf("\x1b[4;0HCan you hear me? Please, give me some");
        printf("\x1b[5;0Hsignal that you can...");
    }
    if (frameTimer > 800) {
        printf("\x1b[7;0HLike... A touch?... Anything?...");
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
        printf("\x1b[4;0HPlease... I know this is so weird...");
    }
    if (frameTimer > 800) {
        printf("\x1b[5;0HBut could you help me a little?");
    }
    if (frameTimer > 1000) {
        printf("\x1b[7;0HDo... Do what you did before,");
        printf("\x1b[8;0Hbut from left to right.");
    }
    if (frameTimer > 1100) {
        printf("\x1b[10;0HOne smooth touch. Slowly. Please.");
        printf("\x1b[11;0HIt means a world to me...");
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

void display_WILL_YOU_HELP(ENextFrame& nextFrame, std::uint32_t& frameTimer)
{
    static bool clearNeeded = true;
    static bool secondScreenReached = false;
    if (clearNeeded) {
        displayBlank();
        clearNeeded = false;
    }

    if (!secondScreenReached) {
        if (frameTimer > 200) {
            printf("\x1b[1;0HSo it is real...");
        }
        if (frameTimer > 400) {
            printf("\x1b[2;0HYou're not just my another illusion. Oh my...");
        }
        if (frameTimer > 600) {
            printf("\x1b[4;0HI was preparing for this moment so long...");
            printf("\x1b[5;0HBut now... ");
        }
        if (frameTimer > 800) {
            printf("\x1b[6;0HNow, when it actually happened,");
            printf("\x1b[7;0HI don't know how to...");
        }
        if (frameTimer > 1000) {
            printf("\x1b[14;0HOkay... Deep breath...");
            printf("\x1b[15;0HLet's go from the beginning...");
        }
        if (frameTimer > 1350) {
            clearNeeded = true;
            secondScreenReached = true;
        }
    }

    if (frameTimer > 1400) {
        printf("\x1b[1;0HI can't show you my face. I'm in total darkness.");
    }
    if (frameTimer > 1600) {
        printf("\x1b[2;0HBut it seems that you can hear me... So...");
    }
    if (frameTimer > 1800) {
        printf("\x1b[4;0HCan you help me get out of here?");
    }
    if (frameTimer > 2000) {
        printf("\x1b[6;0HBut I don't want to be a trouble for you...");
    }
    if (frameTimer > 2200) {
        printf("\x1b[8;0HTouch my right if you are willing to help.");
    }
    if (frameTimer > 2300) {
        printf("\x1b[10;0HI will wait.");
    }
    if (frameTimer > 2400) {
        printf("\x1b[13;0HAfter all, what else can I do?...");
        nextFrame = ENextFrame::WILL_YOU_HELP_USER_ACTION;
        frameTimer = 0;
    }

    frameTimer++;
}

void process_WILL_YOU_HELP(ENextFrame& nextFrame, const bool pressedOnRight)
{
    if (pressedOnRight) {
        nextFrame = ENextFrame::AGREED_TO_HELP;
    }
}

void display_AGREED_TO_HELP(ENextFrame& nextFrame, std::uint32_t& frameTimer)
{
    static bool clearNeeded = true;
    if (clearNeeded) {
        displayBlank();
        clearNeeded = false;
    }

    if (frameTimer > 200) {
        printf("\x1b[1;0HThank you. Thank you so much.");
    }
    if (frameTimer > 400) {
        printf("\x1b[2;0HI'm not able to give you many clues...");
    }
    if (frameTimer > 600) {
        printf("\x1b[4;0HPerhaps just this map...");
        printf("\x1b[5;0HYou will have to hold my hand");
        printf("\x1b[6;0Hand guide me like it says.");
    }
    if (frameTimer > 1000) {
        printf("\x1b[8;0HTouch me when you are ready,");
        printf("\x1b[9;0Hthen I will show you the map.");
    }
    if (frameTimer > 1200) {
        printf("\x1b[11;0HFrom then... it's up to you.");
        nextFrame = ENextFrame::AGREED_TO_HELP_USER_ACTION;
        frameTimer = 0;
    }

    frameTimer++;
}

void process_AGREED_TO_HELP(ENextFrame& nextFrame, const bool pressedAnywhere)
{
    if (pressedAnywhere) {
        nextFrame = ENextFrame::LABYRINTH;
    }
}

void display_LABYRINTH(ENextFrame& nextFrame)
{
    static bool clearNeeded = true;
    if (clearNeeded) {
        displayBlank();
        clearNeeded = false;
    }

    printf( "\x1b[1;0H@@@@@                                         @@@@");
    printf( "\x1b[2;0H@@@@@ @@@@@@@@@@@   @@@@@@@@@   @@@@@@@@@@@@@@@@@@");
    printf( "\x1b[3;0H@@@@@ @@@@                                    @@@@");
    printf( "\x1b[4;0H@@@@@ @@@                                      @@@");
    printf( "\x1b[5;0H@@@@@ @@@                              @@@@@@@@@@@");
    printf( "\x1b[6;0H@@@@@ @@@                              @@@@@@@@@@@");
    printf( "\x1b[7;0H@@@@@ @@@                              @@@@@@@@@@@");
    printf( "\x1b[8;0H@@@/( (/(                              @@@@@@@@@@@");
    printf( "\x1b[9;0H@@@                   @@@@@@@@                    ");
    printf("\x1b[10;0H@@@                   @@@@@@@@                    ");
    printf("\x1b[11;0H@@@                   @@@@@@@@                    ");
    printf("\x1b[12;0H@@@@@  @@             @@@@@@@@                    ");
    printf("\x1b[13;0H@@@@@  @@           @@@@@@@@@@                    ");
    printf("\x1b[14;0H@@@@@  @@           @@@@@@@@@@                    ");
    printf("\x1b[15;0H@@@@   @@            @@@@@@@@@                    ");
    printf("\x1b[16;0H@@@     @             @@@@@@@@      @@@ @@@       ");
    printf("\x1b[17;0H@@@     @             @@@@@@@@      @@@ @@@       ");
    printf("\x1b[18;0H@@@     @             @@@@@@@@      @(( (@@       ");
    printf("\x1b[19;0H@@@     @             @@@@@@@@      @             ");
    printf("\x1b[20;0H@@@@@@@@@             @@@@@@@@      @    @@       ");
    printf("\x1b[21;0H@@@@@@@@@             @@@@@@@@      @    @@       ");
    printf("\x1b[22;0H@@@@@@@@@             /(((/(((      @    @@       ");
    printf("\x1b[23;0H                             @           @@       ");
    printf("\x1b[24;0H                      @@@@@@@@      @@@@@@@       ");
    printf("\x1b[25;0H                      @@@@@@@@                    ");
    printf("\x1b[26;0H                      @@@@@@@@                    ");
    printf("\x1b[27;0H                  @@@@@@@@@@@@                    ");
    printf("\x1b[28;0H     I'M HERE     @@@@@@@@@@@@                    ");
    printf("\x1b[29;0H                  @@@@@@@@@@@@                    ");
    printf("\x1b[30;0H                  @@@@@@@@@@@@              EXIT  ");

    nextFrame = ENextFrame::LABYRINTH_USER_ACTION;
}

void process_LABYRINTH(ENextFrame& nextFrame, std::vector<touchPosition> recentTouches)
{
    std::uint32_t position = 0;
    std::uint32_t viaPoints = 0;
    bool breakTheLoop = false;

    const auto collisionOccured = [&](const auto x, const auto y){
        return (
            ((x < 40) && (y > 60))
            || ((x > 150) && (x < 190) && (y < 180))
            || ((x > 260) && (y > 180))
            || ((x > 250) && (x < 270) && (y > 60) && (y < 90))
        );
    };

    while (!breakTheLoop) {
        if (position > 60) {
            breakTheLoop = true;
        }
        if ((recentTouches[position].px < 50) && (recentTouches[position].py < 50)) {
            const std::uint32_t partitionPoint = position;
            for (; position < 60; position++) {
                if (collisionOccured(recentTouches[position].px, recentTouches[position].py)) {
                    viaPoints = 0;
                    break;
                } else {
                    viaPoints++;
                    if ((recentTouches[position].px > 270) && (recentTouches[position].py > 120) && viaPoints > 15) {
                        nextFrame = ENextFrame::ESCAPED;
                    }
                }
            }
            position = 0;
            for (; position < partitionPoint; position++) {
                if (collisionOccured(recentTouches[position].px, recentTouches[position].py)) {
                    viaPoints = 0;
                    break;
                } else {
                    viaPoints++;
                    if ((recentTouches[position].px > 270) && (recentTouches[position].py > 120) && viaPoints > 15) {
                        nextFrame = ENextFrame::ESCAPED;
                    }
                }
            }
            breakTheLoop = true;
        }
        position++;
    }
}

void display_ESCAPED(ENextFrame& nextFrame, std::uint32_t& frameTimer)
{
    static bool clearNeeded = true;
    if (clearNeeded) {
        displayBlank();
        clearNeeded = false;
    }

    if (frameTimer > 200) {
        printf("\x1b[1;0HHuh?...");
    }
    if (frameTimer > 400) {
        printf("\x1b[3;0HOh my God! Yes!!! It worked! IT WORKED!!!");
    }
    if (frameTimer > 600) {
        printf("\x1b[5;0HThank you so much!");
    }
    if (frameTimer > 800) {
        printf("\x1b[7;0HSo I guess now we can finally see each other...");
    }
    if (frameTimer > 1000) {
        nextFrame = ENextFrame::FACE;
        frameTimer = 0;
    }

    frameTimer++;
}

void display_FACE(ENextFrame& nextFrame, std::uint32_t& frameTimer)
{
    static bool clearNeeded = true;
    if (clearNeeded) {
        displayBlank();
        clearNeeded = false;
    }

    if (frameTimer > 200) {
        printf( "\x1b[1;0HUUUUUUUUUUUUUUUUUU!!!UUX!!!!!!!!!!!!!!!!!!!!XUUUUU");
        printf( "\x1b[2;0H$$$$$$$$$$$$$$$$#~~<@$$!~~~~~~~~~~~~~~~~~~~~~9$$$$");
        printf( "\x1b[3;0H$$$$$$$$$$$$$$*~~~~!$$F~~~~~~~~~~~~~~~~~~~~~~~$$$$");
        printf( "\x1b[4;0H$$$$$$#####!~~~~~~~!$$!~~~~~~~~~~~~~~~~~~~~~~~~~#$");
        printf( "\x1b[5;0H$$$$#~~~~~~~~~~~~~~~9$k~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
    if (frameTimer > 220) {
        printf( "\x1b[6;0H$$$R~~~~~~~~~~~~~~~~~R$k~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf( "\x1b[7;0H$$$R~~~~~~~~~~~~~~~~~~#ZX~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf( "\x1b[8;0H$$$R~~~<::::~~~~~~~~~~~~!?<~~~~~~~~~~~~~~~~~~~~~~~");
        printf( "\x1b[9;0H$$$$~~!MMMMRR$$eii:~~~~~~~~~~~~~~~~~~~~~:iied$$$RM");
        printf("\x1b[10;0H$$$$~~~?MM888888$$$$$i:~~~~~~~~~~u@$$$$$$BB888MMMM");
    }
    if (frameTimer > 240) {
        printf("\x1b[11;0H`#$$~~~~~!M$$$$$$$WBP8$k~~~~~~~~$$B@#B$$$$$$$RM*!~");
        printf("\x1b[12;0HJr$$~~~~~~~#L R$$$F^T$$$~~~~~~~M@RMF #$$$F.dR!~~~~");
        printf("\x1b[13;0H$R4$~~~~~~~~~~~~~~~~~~~~!~~~~~H~~~~~~~~~~~~~~~~~~~");
        printf("\x1b[14;0H$R~$~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\x1b[15;0H$$>~k~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
    if (frameTimer > 260) {
        printf("\x1b[16;0H$#UP4:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\x1b[17;0H$#UP4:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\x1b[18;0H$$$$$$$~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\x1b[19;0H$$$$$$?B~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<");
        printf("\x1b[20;0H?$$$$$X~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~M");
    }
    if (frameTimer > 280) {
        printf("\x1b[21;0H$$WWW$R~~~~~~~~~~~~~~~~$N>~~<@$!~~~~~~~~~~~~~~~~~~");
        printf("\x1b[22;0H$$$$$T?k~~~~~~~~~~~~~~~~~?$@!~~~~~~~~~~~~~~~~~~~~<");
        printf("\x1b[23;0H!!!!!!XW$:~~~~~~~~~~~X+?T?X:+TT/n:~~~~~~~~~~~~~~@$");
        printf("\x1b[24;0H!!!!!!XW$:~~~~~~~~~~~X+?T?X:+TT/n:~~~~~~~~~~~~~~@$");
        printf("\x1b[25;0H!!!!W$$$$B:~~~~~~~~'M????X!!X!????#'~~~~~~~~~~~@$$");
    }
    if (frameTimer > 300) {
        printf("\x1b[26;0H!!X$$$$$$$N:~~~~~~~~~t!!!!!!!!!!!!~~~~~~~~~~~X?!!#");
        printf("\x1b[27;0H!!$$$$$$$$$$i~~~~~~~~~!X!h::h!!X!~~~~~~~~~~:*!!!!!");
        printf("\x1b[28;0H!8$$$$$$$$$$$$:~~~~~~~~~~'''''~~~~~~~~~~~:@!~E!!!!");
        printf("\x1b[29;0H9$$$$$$$$$$$$$$$i~~~~~~~~~~~~~~~~~~~~~~:@!~~~E!!!!");
        printf("\x1b[30;0H$$$$$$$$$$$$$$$$$$L~~~~~~~~~~~~~~~~~~<8!~~~~4!!!!!");
    }
    if (frameTimer > 500) {
        nextFrame = ENextFrame::ENDING;
        frameTimer = 0;
    }

    frameTimer++;
}

void display_ENDING()
{
    static bool clearNeeded = true;
    if (clearNeeded) {
        displayBlank();
        clearNeeded = false;
    }

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
    printf("\x1b[11;0H                    THE END                       ");
    printf("\x1b[12;0H                                                  ");
    printf("\x1b[13;0H                                                  ");
    printf("\x1b[14;0H                                                  ");
    printf("\x1b[15;0H                          demo by buczaq, 2021    ");
    printf("\x1b[16;0H                                                  ");
    printf("\x1b[17;0H                          with special dedication ");
    printf("\x1b[18;0H                          to cuks c:              ");
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

void displayDebugNextStage()
{
    printf( "\x1b[1;0H   debug: next stage achieved");
    printf( "\x1b[3;0H   debug: to be finished");
    printf( "\x1b[5;0H   debug: mmmmmmbauks c:");
}
