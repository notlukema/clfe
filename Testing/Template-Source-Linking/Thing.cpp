#include "Thing.h"

namespace a
{
	Template<int>* blast(int f) {
		return new Template<int>(f);
	}
}