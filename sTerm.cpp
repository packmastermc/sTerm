#include <iostream>
#include <cstdlib>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::string e(const char* v) {
#ifdef _WIN32
    char* b = nullptr; size_t s = 0;
    return _dupenv_s(&b, &s, v) == 0 && b ? std::string(b) : "u";
#else
    const char* b = getenv(v);
    return b ? std::string(b) : "u";
#endif
}

std::string p() {
#ifdef _WIN32
    char h[256]; DWORD s = sizeof(h);
    return e("USERNAME") + "@" + (GetComputerNameA(h, &s) ? h : "u") + "> ";
#else
    char h[256];
    return e("USER") + "@" + (gethostname(h, sizeof(h)) == 0 ? h : "u") + "> ";
#endif
}

void x(const std::string& c) {
    if (c == "exit") exit(0);
#ifdef _WIN32
    if (c == "clear") system("cls");
#else
    if (c == "clear") system("clear");
#endif
    else system(c.c_str());
}

int main() {
    for (std::string i; std::cout << p(), std::getline(std::cin, i);) x(i);
}
