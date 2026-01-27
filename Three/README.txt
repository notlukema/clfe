
Slight documentation:


CLFE - c library framework engine
CLF - c library framework
CLE - c library engine
CLU - c library utilities
CLM - c library math


Math library is currently usable but lacks many utility functions. Will add when time is given and/or I need them.
Does not yet support string types other than char and wchar (such as char32 or char16 etc).


macros:

CLFE_XX_H - header guards for components in clfe, clf, and cle
CLU_XX_H - header guards for components in clu
CLM_XX_H - header guards for components in clm

CLX_XX - c library settings, mostly used for system settings
* CLS_USEWIDESTRING - use wide strings as the system default
* CLM_USEREALMULT - use common value-to-value multiplication for matrices



type aliases:

clid - unsigned int, used for global ids
clchar - system char type, either char or wchar_t







Component priorities:
System - 10
Window - 50
Windows Window - 70
Mac Window - 71
Linux Window - 72