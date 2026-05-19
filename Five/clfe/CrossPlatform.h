#ifndef CLFE_CROSSPLATFORM_H
#define CLFE_CROSSPLATFORM_H

#if defined(_WIN32) || defined(_WIN64)
#define CLFE_OS_WIN
#elif defined(__APPLE__) || defined(__MACH__)
#define CLFE_OS_MAC
#elif defined(__linux__)
#define CLFE_OS_LINUX
#else
#warning "Unknown operating system. Cross-platform compatibility may be limited."
#endif

#endif