#include "CLFE.h"

#include "Attachment.h"

#include "Chrono.h"

namespace clfe
{

	bool init()
	{
		bool success = true;

		for (Attachment* attachment : AttachmentHolder::getAttachmentsSortedByInitPriority())
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

	bool init(const ApplicationInfo& applicationInfo)
	{
		Global::postApplicationInfo(applicationInfo);
		return init();
	}

	void step(float dt)
	{
		for (Attachment* attachment : AttachmentHolder::getAttachmentsSortedByStepPriority())
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
		for (Attachment* attachment : AttachmentHolder::getAttachmentsSortedByStepPriority())
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
		for (Attachment* attachment : AttachmentHolder::getAttachmentsSortedByTermPriority())
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

	using Timer_t = chrono::SteadyClock::time_point;
	Timer_t StepTimer = chrono::HighResClock::now();

	void resetTimer()
	{
		StepTimer = chrono::HighResClock::now();
	}

	float stepf()
	{
		auto currentTime = chrono::HighResClock::now();
		chrono::Duration<double> duration = currentTime - StepTimer;
		StepTimer = currentTime;

		double dt = duration.count();
		step(dt);

		return (float)dt;
	}

	double stepd()
	{
		auto currentTime = chrono::HighResClock::now();
		chrono::Duration<double> duration = currentTime - StepTimer;
		StepTimer = currentTime;

		double dt = duration.count();
		step(dt);

		return dt;
	}

}