#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

int main(int argc, char **argv)
{
    printf("QDT Guest Agent\n");
#ifdef WIN32
    MessageBoxA(NULL, "A test message", "QDT Guest Agent", MB_OK);
#endif
    return 0;
}

