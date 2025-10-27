#ifndef CLE_CROSSPLATFORM_H
#define CLE_CROSSPLATFORM_H
// technically unneeded since the individual Macros already have include guards

#if defined(_WIN32) || defined(_WIN64)

#ifndef CLE_WND
#define CLE_WND
#endif

#elif defined(__APPLE__)

#ifndef CLE_MAC
#define CLE_MAC
#endif

#elif defined(__linux__)

#ifndef CLE_LNX
#define CLE_LNX
#endif

#endif



#endif