#ifndef CLFE_PIPELINE_H
#define CLFE_PIPELINE_H

#include "clfe/window/Window.h"
#include "List.h"

namespace clfe
{

	class Pipeline;

	struct PipelineEntry // A form of the singleton pattern
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
		static void removeEntry(PipelineEntry* entry); // Should never be called unless the user creates their own pipeline then chains a series of confusing operations relating to creating and deleting the registration of the pipeline (very odd case)

	public:
		static inline const List<PipelineEntry*>& getEntries()
		{
			return entries;
		}

	};

	Pipeline* getMainPipeline();
	Pipeline& MainPipeline();

	class Pipeline
	{
	protected:
		virtual ~Pipeline();

	public:
		virtual bool init() = 0;
		//virtual void draw() = 0;
		
		virtual void initWindow(Window* window) = 0;

		// More

	};

}

#endif