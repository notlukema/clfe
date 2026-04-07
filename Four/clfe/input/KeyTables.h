#ifndef CLFE_INPUT_KEYTABLE_H
#define CLFE_INPUT_KEYTABLE_H

#include "InputParams.h"
#include "Key.h"

namespace clfe
{

	inline constexpr int WindowsKeys = 1;
	inline constexpr int MacKeys = 2;
	inline constexpr int LinuxKeys = 3;

	template <int Platform>
	class KeyTable
	{
	};

	template <>
	class KeyTable<WindowsKeys>
	{
	public:
		static constexpr int Size = 100;

		// Avoid direct access to discourage inline code bloat
		static constexpr Key_t KeyMap[Size] = {
			-1, /* 0 */
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
			Key::N0, /* 48 */
			Key::N1, /* 49 */
			Key::N2, /* 50 */
			Key::N3, /* 51 */
			Key::N4, /* 52 */
			Key::N5, /* 53 */
			Key::N6, /* 54 */
			Key::N7, /* 55 */
			Key::N8, /* 56 */
			Key::N9, /* 57 */
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
			-1, /* 91 */
			-1, /* 92 */
			-1, /* 93 */
			-1, /* 94 */
			-1, /* 95 */
			-1, /* 96 */
			-1, /* 97 */
			-1, /* 98 */
			-1, /* 99 */

		};

	};

	template class KeyTable<WindowsKeys>;

}

#endif