#include "CLFE.h"

namespace clfe
{

	bool init()
	{
		bool success = true;

		for (Attachment* attachment : AttachmentHolder::attachments)
		{
			if (attachment->init == nullptr)
			{
				continue;
			}
			success = success && attachment->init();
		}

		resetTimer();

		return success;
	}

	void step(float dt)
	{
		for (Attachment* attachment : AttachmentHolder::attachments)
		{
			if (attachment->step == nullptr)
			{
				continue;
			}
			attachment->step(dt, (double)dt);
		}
	}

	void step(double dt)
	{
		for (Attachment* attachment : AttachmentHolder::attachments)
		{
			if (attachment->step == nullptr)
			{
				continue;
			}
			attachment->step((float)dt, dt);
		}
	}

	void terminate()
	{
		for (Attachment* attachment : AttachmentHolder::attachments)
		{
			if (attachment->terminate == nullptr)
			{
				continue;
			}
			attachment->terminate();
		}

		// Perhaps do something to terminate the attachments too
	}

	// Self-timed stepping

	Timer_t StepTimer = std::chrono::high_resolution_clock::now();

	void resetTimer()
	{
		StepTimer = std::chrono::high_resolution_clock::now();
	}

	float stepf()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = currentTime - StepTimer;
		StepTimer = currentTime;

		double dt = duration.count();
		step(dt);

		return (float)dt;
	}

	double stepd()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = currentTime - StepTimer;
		StepTimer = currentTime;

		double dt = duration.count();
		step(dt);

		return dt;
	}

}