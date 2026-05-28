#include <easyx.h>
#include <windows.h>
#include <string>
#pragma comment(lib, "MSIMG32.lib")
#include "tool.h"

void putimagePNG(int x, int y, IMAGE* img, int alpha) {
    int w = img->getwidth(), h = img->getheight();
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, (BYTE)alpha, AC_SRC_ALPHA };
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, blend);
}

int countfiles(const std::string folderpath) {
    int count = 0;
    std::string searchpath = folderpath + "\\*.png";
    WIN32_FIND_DATAA finddata;
    HANDLE hfind = FindFirstFileA(searchpath.c_str(), &finddata);
    if (hfind != INVALID_HANDLE_VALUE) {
        do {
            count++;
        } while (FindNextFileA(hfind, &finddata));
    }
    FindClose(hfind);
    return count;
}