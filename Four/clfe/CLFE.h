#ifndef CLFE_CLFE_H
#define CLFE_CLFE_H

// Ties togethor the init, step, and terminate functions of various modules

#include <List>
#include <cstdint>

namespace clfe
{

	// Part placeholder (all "attachments" and the std::list)
	
	// Lower number = higher priority (0 = highest priority)
	struct Attachment
	{

		bool (*const init)();
		void (*const step)(float delf, double deld);
		void (*const terminate)();

		const uint32_t priority; // Lower number = higher priority (0 = highest priority)
		
		Attachment(uint32_t priority, bool (*initFunc)(), void (*stepFunc)(float delf, double deld), void (*termFunc)());

	};

	struct AttachmentHolder
	{

		static std::list<Attachment*> attachments;

		static void sort();

	};
	
	static void addAttachment(Attachment* attachment);
	static void removeAttachment(Attachment* attachment);
	
	bool init();
	void step();
	void terminate();

}

#endif