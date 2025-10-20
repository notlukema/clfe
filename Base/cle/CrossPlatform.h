#ifndef CLE_CROSSPLATFORM_H
#define CLE_CROSSPLATFORM_H

#if defined(_WIN32) || defined(_WIN64)
#define CLE_WND
#elif defined(__APPLE__)
#define CLE_MAC
#elif defined(__linux__)
#define CLE_LNX
#endif



#endif