#include "Pipeline.h"

namespace clfe
{

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

}