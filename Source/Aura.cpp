#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    return 0;
}

#ifdef aura_gcc
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR, int show)
{
    return wWinMain(instance, previous, GetCommandLineW(), show);
}
#endif
#endif
#endif