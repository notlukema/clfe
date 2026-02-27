#ifndef CLFE_INPUT_KEY_H
#define CLFE_INPUT_KEY_H

#include "InputParams.h"

namespace clfe
{

	struct Key
	{
#define K_T static constexpr Key_t

		K_T Unknown = -1;

		K_T D0 = 5; /* 0 */
		K_T D1 = 6; /* 1 */
		K_T D2 = 7; /* 2 */
		K_T D3 = 8; /* 3 */
		K_T D4 = 9; /* 4 */
		K_T D5 = 10; /* 5 */
		K_T D6 = 11; /* 6 */
		K_T D7 = 12; /* 7 */
		K_T D8 = 13; /* 8 */
		K_T D9 = 14; /* 9 */
		K_T A = 20;
		K_T B = 21;
		K_T C = 22;
		K_T D = 23;
		K_T E = 24;
		K_T F = 25;
		K_T G = 26;
		K_T H = 27;
		K_T I = 28;
		K_T J = 29;
		K_T K = 30;
		K_T L = 31;
		K_T M = 32;
		K_T N = 33;
		K_T O = 34;
		K_T P = 35;
		K_T Q = 36;
		K_T R = 37;
		K_T S = 38;
		K_T T = 39;
		K_T U = 40;
		K_T V = 41;
		K_T W = 42;
		K_T X = 43;
		K_T Y = 44;
		K_T Z = 45;

		K_T Space = 50;
		K_T Enter = 51;
		K_T Escape = 52;

	};

}

#endif