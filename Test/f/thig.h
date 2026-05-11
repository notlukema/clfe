#pragma once

namespace thig
{

	static thread_local int num = 0;

	void increment()
	{
		num++;
	}

	int gnum()
	{
		return num;
	}

}