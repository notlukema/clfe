#ifndef CLFE_INPUT_KEYTABLE_H
#define CLFE_INPUT_KEYTABLE_H

#include "InputParams.h"
#include "Key.h"

namespace clfe
{

	constexpr auto WINDOWS_KEYS = 1;
	constexpr auto MAC_KEYS = 2;
	constexpr auto LINUX_KEYS = 3;

	template <int Platform>
	class KeyTable
	{
	};

	template <>
	class KeyTable<WINDOWS_KEYS>
	{
	public:
		static constexpr int Size = 90;
		static constexpr int keyMap[] = {
			-1, /* 1 */
			-1, /* 2 */
			-1, /* 3 */
			-1, /* 4 */
			-1, /* 5 */
			-1, /* 6 */
			-1, /* 7 */
			-1, /* 8 */
			-1, /* 9 */
			-1, /* 10 */
			-1, /* 11 */
			-1, /* 12 */
			Key::Enter, /* 13 */
			-1, /* 14 */
			-1, /* 15 */
			-1, /* 16 */
			-1, /* 17 */
			-1, /* 18 */
			-1, /* 19 */
			-1, /* 20 */
			-1, /* 21 */
			-1, /* 22 */
			-1, /* 23 */
			-1, /* 24 */
			-1, /* 25 */
			-1, /* 26 */
			Key::Escape, /* 27 */
			-1, /* 28 */
			-1, /* 29 */
			-1, /* 30 */
			-1, /* 31 */
			Key::Space, /* 32 */
			-1, /* 33 */
			-1, /* 34 */
			-1, /* 35 */
			-1, /* 36 */
			-1, /* 37 */
			-1, /* 38 */
			-1, /* 39 */
			-1, /* 40 */
			-1, /* 41 */
			-1, /* 42 */
			-1, /* 43 */
			-1, /* 44 */
			-1, /* 45 */
			-1, /* 46 */
			-1, /* 47 */
			Key::D0, /* 48 */
			Key::D1, /* 49 */
			Key::D2, /* 50 */
			Key::D3, /* 51 */
			Key::D4, /* 52 */
			Key::D5, /* 53 */
			Key::D6, /* 54 */
			Key::D7, /* 55 */
			Key::D8, /* 56 */
			Key::D9, /* 57 */
			-1, /* 58 */
			-1, /* 59 */
			-1, /* 60 */
			-1, /* 61 */
			-1, /* 62 */
			-1, /* 63 */
			-1, /* 64 */
			Key::A, /* 65 */
			Key::B, /* 66 */
			Key::C, /* 67 */
			Key::D, /* 68 */
			Key::E, /* 69 */
			Key::F, /* 70 */
			Key::G, /* 71 */
			Key::H, /* 72 */
			Key::I, /* 73 */
			Key::J, /* 74 */
			Key::K, /* 75 */
			Key::L, /* 76 */
			Key::M, /* 77 */
			Key::N, /* 78 */
			Key::O, /* 79 */
			Key::P, /* 80 */
			Key::Q, /* 81 */
			Key::R, /* 82 */
			Key::S, /* 83 */
			Key::T, /* 84 */
			Key::U, /* 85 */
			Key::V, /* 86 */
			Key::W, /* 87 */
			Key::X, /* 88 */
			Key::Y, /* 89 */
			Key::Z, /* 90 */

		};

	};

	template class KeyTable<WINDOWS_KEYS>;

}

#endif