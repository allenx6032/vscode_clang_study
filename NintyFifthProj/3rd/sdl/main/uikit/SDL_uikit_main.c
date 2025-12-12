/*
    SDL_uiki_main.c, placed in the public domain by Sam Lantinga  3/18/2019
*/
#include "../../SDL_internal.h"


#ifdef __MACOS__
/* Include the SDL main definition header */
#include "SDL_main.h"

#ifdef main
#undef main
#endif

int
main(int argc, char *argv[])
{
    return SDL_UIKitRunApp(argc, argv, SDL_main);
}

/* vi: set ts=4 sw=4 expandtab: */
#endif
