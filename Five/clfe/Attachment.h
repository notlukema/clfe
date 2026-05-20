#ifndef CLFE_ATTACHMENT_H
#define CLFE_ATTACHMENT_H

#include "List.h"

#include <cstdint>

namespace clfe
{

	// Lower number = higher priority (0 = highest priority)
	using Priority_t = uint32_t;

	struct Attachment
	{

		bool (* const init)();
		void (* const step)(float delf, double deld);
		void (* const terminate)();

		const Priority_t initPriority; // Lower number = higher priority (0 = highest priority)
		const Priority_t stepPriority;
		const Priority_t termPriority;

		Attachment(Priority_t priority, bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)());
		Attachment(Priority_t initPriority, Priority_t stepPriority, Priority_t termPriority, bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)());
		Attachment(const Priority_t priorities[3], bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)());
		~Attachment();

	};

	class AttachmentHolder
	{
	private:
		friend struct Attachment;

		static List<Attachment*> attachments;

		static void addAttachment(Attachment* attachment);
		static void removeAttachment(Attachment* attachment);

	public:
		AttachmentHolder() = delete;

		static inline const List<Attachment*>& getAttachments()
		{
			return attachments;
		}

		static const List<Attachment*>& getAttachmentsSortedByInitPriority();
		static const List<Attachment*>& getAttachmentsSortedByStepPriority();
		static const List<Attachment*>& getAttachmentsSortedByTermPriority();

	};

	// Attachment layers

	using AttLayer_t = uint32_t;

	struct AttachmentLayers
	{
#define AL_T static constexpr AttLayer_t

		AL_T System[3] = { 10, 10, 99999 };

		AL_T Pipeline = 30;

		AL_T Window = 50;

		AL_T WinWindow = 70;

		AL_T MacWindow = 75;

		AL_T LnxWindow = 80;

		AL_T SystemInput = 100;

	};

}

#endif