#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <windef.h>
#include <fstream>
#include <CSTDLIB>
#include <CTIME>
#include <CMATH>
#include <iosfwd>
#include <SHLWAPI.H>
#include <MMSYSTEM.H>
#include <memory>
#pragma comment(lib,"SHLWAPI.LIB")
#pragma comment(lib,"MSIMG32.LIB")
#define nTime 30
#define PI 3.1415926535897932384626433832795028841971
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
int x = 1920, y = 1080;
using namespace std;
typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE unused;
    };
} *PRGBQUAD;
HCRYPTPROV prov;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF fe(int length) {
    if (red != length) {
        red < length; red++;
        if (ifblue == true) {
            return RGB(red, 0, length);
        }
        else {
            return RGB(red, 0, 0);
        }
    }
    else {
        if (green != length) {
            green < length; green++;
            return RGB(length, green, 0);
        }
        else {
            if (blue != length) {
                blue < length; blue++;
                return RGB(0, length, blue);
            }
            else {
                red = 0; green = 0; blue = 0;
                ifblue = true;
            }
        }
    }
}
DWORD xs;
//VOID SeedXorshift32(DWORD dwSeed) {
//    xs = dwSeed;
//}

DWORD Xorshift32() {
    xs ^= xs << 13;
    xs ^= xs << 17;
    xs ^= xs << 5;
    return xs;
}
static ULONGLONG r, n;
int randy() { 
    return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; 
}
VOID WINAPI qq(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
    BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
    ReleaseDC(NULL, hdc);
}
//------------------------------------------------------------------------
void cursors() {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(NULL);
    DrawIcon(hdc, rand() % w, rand() % h, LoadCursor(NULL, IDC_ARROW));
    DrawIcon(hdc, rand() % w, rand() % h, LoadCursor(NULL, IDC_CROSS));
    DrawIcon(hdc, rand() % w, rand() % h, LoadCursor(NULL, IDC_HELP));
    DrawIcon(hdc, rand() % w, rand() % h, LoadCursor(NULL, IDC_IBEAM));
    DrawIcon(hdc, rand() % w, rand() % h, LoadCursor(NULL, IDC_NO));
    DrawIcon(hdc, rand() % w, rand() % h, LoadCursor(NULL, IDC_SIZEALL));
    DrawIcon(hdc, rand() % w, rand() % h, LoadCursor(NULL, IDC_UPARROW));
    DrawIcon(hdc, rand() % w, rand() % h, LoadCursor(NULL, IDC_WAIT));
}
void textout() {
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"Polonium.exe has ruined your PC";
    hdc = GetWindowDC(GetDesktopWindow());
    sx = GetSystemMetrics(0);
    sy = GetSystemMetrics(1);
    SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
    SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
    TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));

}
void rgb() {
    HDC hdc = 0;
    int sx = 0, sy = 0;
    int rx = 0, ry = 0;
    hdc = GetWindowDC(GetDesktopWindow());
    sx = GetSystemMetrics(SM_CXSCREEN);
    sy = GetSystemMetrics(SM_CYSCREEN);
    HBRUSH brush = CreateSolidBrush(RGB(rand() % 225, rand() % 225, rand() % 225));
    SelectObject(hdc, brush);
    PatBlt(hdc, 0, 0, sx, sy, PATINVERT);
    ReleaseDC(0, hdc);
    DeleteObject(brush);
}
void lines() {
    int sw, sh;
    sw = GetSystemMetrics(SM_CXSCREEN);
    sh = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(0);
    POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
    HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
    HPEN hPen = CreatePen(PS_SOLID, 5, fe(255));
    SelectObject(hdc, hPen);
    Polyline(hdc, p, 4);
    DeleteObject(hPen);
    ReleaseDC(0, hdc);
}
void bigicon() {
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hwnd);
    DrawIconEx(hdc, rand() % GetSystemMetrics(0), rand() % GetSystemMetrics(1), LoadIcon(NULL, MAKEINTRESOURCE(32512 + rand() % 7)), rand() % GetSystemMetrics(0), rand() % GetSystemMetrics(1), NULL, NULL, DI_NORMAL);
}
//------------------------------------------------------------------------
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((t / 91 & t ^ t / 90 & t) - 1));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((t >> 9 ^ (t >> 9) - 1 ^ 1) % 13 * t & 31) * (2 + (t >> 4)));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((t >> 6 | t >> 12) & 15 & t >> 9));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (4 | t >> 13 & 3) >> (~t >> 11 & 1) & 128 | t * (t >> 11 & t >> 13) * (~t >> 9 & 3) & 127);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 6 ^ t & t >> 9 ^ t >> 12 | ((t >> 6 | t << 1) + (t >> 5 | t << 3 | t >> 3) | t >> 2 | t << 1));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 10 ^ t >> 11) % 5 * ((t >> 14 & 3 ^ t >> 15 & 1) + 1) * t % 99 + ((3 + (t >> 14 & 3) - (t >> 16 & 1)) / 3 * t % 99 & 64));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound7() {//This sound is from Monoxide
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t & ((t >> 18) + ((t >> 11) & t))) * t + (((t >> 8 & t) - (t >> 3 & t >> 8 | t >> 16)) & 128));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t & 5 * t | t >> 4) + (t | t >> 4 * t << 7) ^ t >> 12);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound9() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(128 * sin(sin(t / 100) - t / (2 + (t >> 10 & t >> 12) % 9)) + 128);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound10() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> (t & 4096 ? t * t >> 12 : t >> 12)) | t << (t >> 8) | t >> 4);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound11() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((((t & t >> 8) - (t >> 13 & t)) & ((t & t >> 8) - (t >> 13))) ^ (t >> 8 & t)));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound12() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((t & 4095) * (25 & t * (t & t >> 19)) >> 2) + (127 & t * (254 & t >> 6 & t >> 3) >> (2 & t >> 12)));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound13() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[16000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 10 & t >> 13));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
//------------------------------------------------------------------------
/*
void payloadStart() {
    WinExec("mstsc.exe", 5);
	WinExec("notepad.exe",5);
    WinExec("cmd.exe", 5);
    WinExec("regedit.exe", 5);
    WinExec("mmc.exe", 5);
    WinExec("taskmgr.exe", 5);
    WinExec("charmap.exe", 5);
    WinExec("eventvwr.exe", 5);
    WinExec("prefmon.exe", 5);
}
*/
void payload1() {//fault
    int dwStartTime = time(NULL);
    sound1();
    for (int t = 0;time(NULL) < (dwStartTime + nTime); t++) {
        bigicon();
        int width, height;
        HWND hwnd;
        width = GetSystemMetrics(SM_CXSCREEN);
        height = GetSystemMetrics(SM_CYSCREEN);
        hwnd = GetDesktopWindow();    HDC hdc = GetDC(NULL);
        RECT rekt;
        GetWindowRect(hwnd, &rekt);
        HBRUSH rainbow = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, rainbow);
        int xyrng = rand() % width, h = height - rand() % width - (width / 2 - 110);
        POINT pt3[3];
        int inc3 = 60;
        inc3++;
        pt3[0].x = rekt.left + inc3;
        pt3[0].y = rekt.top - inc3;
        pt3[1].x = rekt.right + inc3;
        pt3[1].y = rekt.top + inc3;
        pt3[2].x = rekt.left - inc3;
        pt3[2].y = rekt.bottom - inc3;
        bigicon();
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        Sleep(100);
    }
}
void payload2() {//screenmove
    HDC hdc = GetDC(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    int dwStartTime = time(NULL);
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    sound2();
    PRGBQUAD prgbScreen;
    HDC hcdc = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
    SelectObject(hcdc, hBitmap);
    
    for (int t = 0;time(NULL) < (dwStartTime + nTime); t++){
        hdc = GetDC(NULL);
        cursors();
        StretchBlt(hcdc, 0, h, w - 20, -h, hdc, 20, 0, w - 20, h, SRCCOPY);
        StretchBlt(hcdc, w - 20, h, 20, -h, hdc, 0, 0, 20, h, SRCCOPY);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int pos = x + y * w;
                int r = prgbScreen[pos].r, g = prgbScreen[pos].g, b = prgbScreen[pos].b;
                prgbScreen[pos].rgb = RGB((r + g + b) / 3, (r + g + b) / 3, (r + g + b) / 3);
            }
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
    
        ReleaseDC(NULL, hdc);
        DeleteObject(hdc);
        Sleep(50);
    }
    ReleaseDC(NULL, hcdc);
    DeleteDC(hcdc);
    DeleteObject(hBitmap);
}
void payload3() {//screenrotate
    int dwStartTime = time(NULL);
    sound3();
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
        rgb();
        int wQ = GetSystemMetrics(SM_CXSCREEN), hQ = GetSystemMetrics(SM_CYSCREEN);
        HDC hdcccccccc = GetDC(NULL);
        DrawIcon(hdcccccccc, rand() % wQ, rand() % hQ, LoadIcon(NULL, IDI_SHIELD));
        DrawIcon(hdcccccccc, rand() % wQ, rand() % hQ, LoadIcon(NULL, IDI_WARNING));
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        POINT pos[3];
        pos[0].x = 10, pos[0].y = -30;
        pos[1].x = w + 10, pos[1].y = 30;
        pos[2].x = -40, pos[2].y = h - 30;
        PlgBlt(hdc, pos, hdc, 0, 0, w, h, 0, 0, 0);
        ReleaseDC(NULL, hdc);
        DeleteObject(hdc);
    }
}
void payload4(){//bokeh
    int dwStartTime = time(NULL);
    sound4();
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
        lines();
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int y = 0; y <= h; y++) {
            BitBlt(hcdc, 10 * ((rand() % 5) - 3), y, w, 1, hcdc, 0, y, SRCCOPY);
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(1);
    }
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}
void payload5() {//shader1
    int dwStartTime = time(NULL);
    HDC hdcDest = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    sound5();
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++)
    {
        cursors();
        lines();
        int wQ = GetSystemMetrics(SM_CXSCREEN), hQ = GetSystemMetrics(SM_CYSCREEN);
        HDC hdcccccccc = GetDC(NULL);
        DrawIcon(hdcccccccc, rand() % wQ, rand() % hQ, LoadIcon(NULL, IDI_ERROR));
        DrawIcon(hdcccccccc, rand() % wQ, rand() % hQ, LoadIcon(NULL, IDI_WARNING));
        DrawIcon(hdcccccccc, rand() % wQ, rand() % hQ, LoadIcon(NULL, IDI_WINLOGO));
        DrawIcon(hdcccccccc, rand() % wQ, rand() % hQ, LoadIcon(NULL, IDI_QUESTION));
        DrawIcon(hdcccccccc, rand() % wQ, rand() % hQ, LoadIcon(NULL, IDI_INFORMATION));
        DrawIcon(hdcccccccc, rand() % wQ, rand() % hQ, LoadIcon(NULL, IDI_SHIELD));
        StretchBlt(hdcDest, -10, -10, w - 20, h - 20, hdcDest, 0, 0, w, h, 0x440328u);
        StretchBlt(hdcDest, 10, 10, w - 20, h - 20, hdcDest, 0, 0, w, h, 0x660046u);
        Sleep(50);
    }
}
void payload6() {//shader2
    HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
    INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    BITMAPINFO bmi = { 0 };
    PRGBQUAD rgbScreen = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
    SelectObject(hdcMem, hbmTemp);
    int dwStartTime = time(NULL);
    sound6();
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
        textout();
        hdcScreen = GetDC(0);
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        for (INT i = 0; i < w * h; i++) {
            INT x = i % w, y = i / w;
            rgbScreen[i].rgb += (x ^ y);
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        //Sleep(100);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}
void payload7() {//shader3
    int dwStartTime = time(NULL);
    sound7();
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
        textout();
        cursors();
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        StretchBlt(hcdc, 20 * ((t % 3) - 1), 20 * ((t % 3) - 1), w - 40 * ((t % 3) - 1), h - 40 * ((t % 3) - 1), hcdc, 0, 0, w, h, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(5);
    }
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}
void payload8() {//tunnel
    int dwStartTime = time(NULL);
    sound8();
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
        lines();
        cursors();
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        POINT pos[3];
        pos[0].x = h / 40, pos[0].y = h / 40;
        pos[1].x = w - (h / 40), pos[1].y = 0;
        pos[2].x = h / 40, pos[2].y = h;
        PlgBlt(hcdc, pos, hcdc, 0, 0, w, h, 0, 0, 0);
        SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
        PatBlt(hcdc, 0, 0, w, h, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(100);
    }
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}
void payload9() {//glitch+rgb
    int dwStartTime = time(NULL);
    FreeConsole();
        HDC desk = GetDC(0);
        int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
        RECT rekt; POINT wPt[3];
        sound9();
        for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
            rgb();
            GetWindowRect(GetDesktopWindow(), &rekt);
            wPt[0].x = rand() % sw; wPt[0].y = rand() % sh;
            wPt[1].x = rand() % sw; wPt[1].y = rand() % sh;
            wPt[2].x = rand() % sw; wPt[2].y = rand() % sh;
            PlgBlt(desk, wPt, desk, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
        }
}
void payload10() {//Flashbang
    sound10();
    int dwStartTime = time(NULL);
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
        bigicon();
        cursors();
        BitBlt(hdc, rand() % w, rand() % h, w, h, hdc, rand() % w, rand() % h, NOTSRCCOPY);
        StretchBlt(hdc, rand() % w, rand() % h, w, h, hdc, rand() % w, rand() % h, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
    }
}
void payload11() {//swir
    sound11();
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
    int dwStartTime = time(NULL);
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
        lines();
        cursors();
        textout();
        hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
        SelectObject(hdcMem, screenshot);
        BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < sh * 2; i++) {
            int wave = sin(i / ((float)xSize) * PI) * (ySize);
            BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCCOPY);
        }
        for (int i = 0; i < sw * 2; i++) {
            int wave = sin(i / ((float)xSize) * PI) * (ySize);
            BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, SRCCOPY);
        }
        BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
        Sleep(1);
    }
}
void payload12() {//colorlineblock
    int dwStartTime = time(NULL);
    sound12();
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
        cursors();
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
        PatBlt(hcdc, 0, (t % 40) * (h / 40), w, h / 40, PATINVERT);
        SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
        PatBlt(hcdc, (t % 40) * (w / 40), 0, w / 40, h, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(5);
    }
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}
void payload13() {//shader4
    sound13();
    int dwStartTime = time(NULL);
    HDC hdc = GetDC(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    PRGBQUAD prgbScreen;
    HDC hcdc = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
    SelectObject(hcdc, hBitmap);
    for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
        hdc = GetDC(NULL);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < w * h; i++) {
            prgbScreen[i].rgb = ((10 * t + i) / 10) % RGB(255, 255, 255);
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteObject(hdc);
        Sleep(10);
    }
    DeleteObject(hBitmap);
    DeleteDC(hcdc);
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}
//------------------------------------------------------------------------
void MainPayload() {
    payload1();
    payload2();
    payload3();
    payload4();
    payload5();
    payload6();
    payload7();
    payload8();
    payload9();
    payload10();
    payload11();
    payload12();
    payload13();
}
//------------------------------------------------------------------------
int main() {
    if (MessageBoxW(NULL, L"If you don't know what is it,just exit this program.\r\n\It's a malware.\r\n\Run only on vitrual machines.\r\n\r\n\Press 'Yes' button to start,\r\n\press 'No' button to exit.", L"Polonium.exe", MB_YESNO | MB_ICONWARNING) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"Last warning!\r\n\Are you sure to run this program?", L"Polonium", MB_YESNO | MB_ICONWARNING) == IDNO)
        {
            ExitProcess(0);
        }
        else{
            MainPayload();
        }
    }
    return 0;
}