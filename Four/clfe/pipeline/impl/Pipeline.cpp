#include "Pipeline.h"

namespace clfe
{
	
	// PipelineEntry

	PipelineEntry::PipelineEntry(Pipeline* pipeline) : pipeline(pipeline)
	{
		PipelineEntryHolder::addEntry(this);
	}

	PipelineEntry::~PipelineEntry()
	{
		PipelineEntryHolder::removeEntry(this);
	}

	// PipelineEntryHolder struct

	List<PipelineEntry*> PipelineEntryHolder::entries = List<PipelineEntry*>();

	void PipelineEntryHolder::addEntry(PipelineEntry* entry)
	{
		entries.push_back(entry);
	}

	void PipelineEntryHolder::removeEntry(PipelineEntry* entry)
	{
		entries.remove(entry);
	}

	// namespace

	Pipeline* getMainPipeline()
	{
		if (PipelineEntryHolder::getEntries().empty()) {
			return nullptr;
		}
		return PipelineEntryHolder::getEntries().front()->pipeline;
	}

	Pipeline& MainPipeline()
	{
		Pipeline* pipeline = getMainPipeline();
		if (pipeline == nullptr)
		{
			CLFE_RUNTIME_ERROR("No pipeline entries found. A pipeline must be registered before MainPipeline() can be used.");
			// This should be a very rare error to find because pipelines can't get removed after registration (they are basically equivalent of static) so the only expainable case is that there was no pipeline registered at all
		}

		return *pipeline;
	}

	// Pipeline

	Pipeline::~Pipeline()
	{
		// Empty
	}

}