#ifndef CLFE_INPUT_KEY_H
#define CLFE_INPUT_KEY_H

#include "InputParams.h"

namespace clfe
{

	struct Key
	{
#define K_T static constexpr Key_t

		K_T Unknown = -1;

		K_T N0 = 1; /* 0 */
		K_T N1 = 2; /* 1 */
		K_T N2 = 3; /* 2 */
		K_T N3 = 4; /* 3 */
		K_T N4 = 5; /* 4 */
		K_T N5 = 6; /* 5 */
		K_T N6 = 7; /* 6 */
		K_T N7 = 8; /* 7 */
		K_T N8 = 9; /* 8 */
		K_T N9 = 10; /* 9 */
		K_T A = 11;
		K_T B = 12;
		K_T C = 13;
		K_T D = 14;
		K_T E = 15;
		K_T F = 16;
		K_T G = 17;
		K_T H = 18;
		K_T I = 19;
		K_T J = 20;
		K_T K = 21;
		K_T L = 22;
		K_T M = 23;
		K_T N = 24;
		K_T O = 25;
		K_T P = 26;
		K_T Q = 27;
		K_T R = 28;
		K_T S = 29;
		K_T T = 30;
		K_T U = 31;
		K_T V = 32;
		K_T W = 33;
		K_T X = 34;
		K_T Y = 35;
		K_T Z = 36;

		K_T Space = 40;
		K_T Enter = 41;
		K_T Escape = 42;

	};

	struct KeyChars
	{

		static const char* getChar(Key_t key);

		// Avoid direct access to discourage inline code bloat
		static constexpr const char* CharMap[KeyCount] = {
			" ", /* 0 */
			"0", /* 1 */
			"1", /* 2 */
			"2", /* 3 */
			"3", /* 4 */
			"4", /* 5 */
			"5", /* 6 */
			"6", /* 7 */
			"7", /* 8 */
			"8", /* 9 */
			"9", /* 10 */
			"A", /* 11 */
			"B", /* 12 */
			"C", /* 13 */
			"D", /* 14 */
			"E", /* 15 */
			"F", /* 16 */
			"G", /* 17 */
			"H", /* 18 */
			"I", /* 19 */
			"J", /* 20 */
			"K", /* 21 */
			"L", /* 22 */
			"M", /* 23 */
			"N", /* 24 */
			"O", /* 25 */
			"P", /* 26 */
			"Q", /* 27 */
			"R", /* 28 */
			"S", /* 29 */
			"T", /* 30 */
			"U", /* 31 */
			"V", /* 32 */
			"W", /* 33 */
			"X", /* 34 */
			"Y", /* 35 */
			"Z", /* 36 */
			" ", /* 37 */
			" ", /* 38 */
			" ", /* 39 */
			" ", /* 40 */
			"Enter", /* 41 */
			"Escape", /* 42 */
			" ", /* 43 */
			" ", /* 44 */
			" ", /* 45 */
			" ", /* 46 */
			" ", /* 47 */
			" ", /* 48 */
			" ", /* 49 */

		};

	};

}

#endif