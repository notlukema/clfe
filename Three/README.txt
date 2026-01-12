
Slight documentation:


CLFE - c library framework engine
CLF - c library framework
CLE - c library engine
CLU - c library utilities
CLM - c library math



macros:

CLFE_XX_H - header guards for components in clfe, clf, and cle
CLU_XX_H - header guards for components in clu
CLM_XX_H - header guards for components in clm

CLS_XX - c library settings, mostly used for system settings
* CLS_USEWIDESTRING - use wide strings as the system default



type aliases:

clid - unsigned int, used for global ids
clchar - system char type, either char or wchar_t