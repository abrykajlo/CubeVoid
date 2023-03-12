/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "cubevoid.h"

int
main(int argc, char** argv)
{
    CubeVoidGame game;
    // Initialize and catch errors
    if (game.Init() < 0) {
        return -1;
    }
    // run main loop
    game.Run();
    // Quit and catch errors
    if (game.Quit() < 0) {
        return -1;
    }
    return 0;
}