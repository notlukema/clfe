#ifndef CLFE_INPUT_KEY_H
#define CLFE_INPUT_KEY_H

namespace clfe
{

	struct Key
	{
#define KT_M constexpr static IncType

		KT_M Unknown = -1;

		KT_M D0 = 5; /* 0 */
		KT_M D1 = 6; /* 1 */
		KT_M D2 = 7; /* 2 */
		KT_M D3 = 8; /* 3 */
		KT_M D4 = 9; /* 4 */
		KT_M D5 = 10; /* 5 */
		KT_M D6 = 11; /* 6 */
		KT_M D7 = 12; /* 7 */
		KT_M D8 = 13; /* 8 */
		KT_M D9 = 14; /* 9 */
		KT_M A = 20;
		KT_M B = 21;
		KT_M C = 22;
		KT_M D = 23;
		KT_M E = 24;
		KT_M F = 25;
		KT_M G = 26;
		KT_M H = 27;
		KT_M I = 28;
		KT_M J = 29;
		KT_M K = 30;
		KT_M L = 31;
		KT_M M = 32;
		KT_M N = 33;
		KT_M O = 34;
		KT_M P = 35;
		KT_M Q = 36;
		KT_M R = 37;
		KT_M S = 38;
		KT_M T = 39;
		KT_M U = 40;
		KT_M V = 41;
		KT_M W = 42;
		KT_M X = 43;
		KT_M Y = 44;
		KT_M Z = 45;

		KT_M Space = 50;
		KT_M Enter = 51;
		KT_M Escape = 52;

	};

}

#endif