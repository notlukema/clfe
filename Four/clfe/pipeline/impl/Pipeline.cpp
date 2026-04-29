#include "Pipeline.h"

#include "clfe/AttachmentLayers.h"
#include "clfe/System.h"

namespace clfe
{

	const Attachment Pipeline::PipelineAttachment = Attachment(AttachmentLayers::Pipeline, Pipeline::sinit, nullptr, Pipeline::sterminate);
	InstanceList<Pipeline>* Pipeline::PipelineList = nullptr;

	InstanceListHandle<Pipeline> Pipeline::getPipelinesList()
	{
		return PipelineList->getHandle();
	}

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

	Pipeline::Pipeline(void (*initfunc)(Pipeline* this_, Window* other), void (*termfunc)(Pipeline* this_, Window* other)) : InstanceInterface(PipelineList)
	{
		WindowPool = new LinkPool<Window>(this, initfunc, termfunc);
	}

	Pipeline::~Pipeline()
	{
		delete WindowPool;
	}

	bool Pipeline::attachWindow(Window* window)
	{
		if (validateWindow(window))
		{
			//WindowPool->attach(window->pullPipelineLink());
			return true;
		}
		return false;
	}

}