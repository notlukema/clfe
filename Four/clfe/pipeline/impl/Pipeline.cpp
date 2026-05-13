#include "Pipeline.h"

#include "clfe/AttachmentLayers.h"

namespace clfe
{

	const Attachment Pipeline::PipelineAttachment = Attachment(AttachmentLayers::Pipeline, Pipeline::sinit, nullptr, Pipeline::sterminate);
	InstanceList<Pipeline>* Pipeline::PipelineList = nullptr;

	bool Pipeline::sinit()
	{
		PipelineList = new InstanceList<Pipeline>();

		return true;
	}

	void Pipeline::sterminate()
	{
		delete PipelineList;
		PipelineList = nullptr;
	}

	// Pipeline

	Pipeline::Pipeline() : InstanceInterface(PipelineList)
	{}

}