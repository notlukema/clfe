#ifndef CLFE_PIPELINE_H
#define CLFE_PIPELINE_H

#include "clfe/window/Window.h"
#include "List.h"

namespace clfe
{

	class Pipeline;

	struct PipelineEntry
	{

		Pipeline* pipeline; // No extra data for now so this struct is a bit redundant, but overhead is minimal and it allows for future expansion if needed

		PipelineEntry(Pipeline* pipeline);
		~PipelineEntry();

	};

	class PipelineEntryHolder
	{
	private:
		friend struct PipelineEntry;

		static List<PipelineEntry*> entries;

		static void addEntry(PipelineEntry* entry);
		static void removeEntry(PipelineEntry* entry);

	public:
		static inline const List<PipelineEntry*>& getEntries()
		{
			return entries;
		}

	};

	// Create main pipeline class, which will automatically connect to the first included pipeline

	class Pipeline
	{
	public:
		virtual ~Pipeline() = default;

		virtual bool init() = 0;
		//virtual void draw() = 0;
		
		virtual void initWindow(Window* window) = 0;

		// More

	};

}

#endif