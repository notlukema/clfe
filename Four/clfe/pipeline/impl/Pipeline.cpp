#include "Pipeline.h"

#include "clfe/AttachmentLayers.h"
#include "clfe/InstanceTypes.h"
#include "clfe/System.h"

namespace clfe
{

	const Attachment Pipeline::PipelineAttachment = Attachment(AttachmentLayers::Pipeline, Pipeline::sinit, nullptr, Pipeline::sterminate);
	InstanceList<Pipeline>* Pipeline::Pipelines = nullptr;

	InstanceListHandle<Pipeline> Pipeline::getPipelinesList()
	{
		return Pipelines->getHandle();
	}

	bool Pipeline::sinit()
	{
		Pipelines = new InstanceList<Pipeline>(InstanceTypes::Pipeline);

		return true;
	}

	void Pipeline::sterminate()
	{
		delete Pipelines;
		Pipelines = nullptr;
	}

	// Pipeline

	Pipeline::Pipeline(clid id) : thisid(id)
	{
		Pipelines->add(this, id);
	}

	Pipeline::~Pipeline()
	{
		Pipelines->remove(thisid);
	}

	clid Pipeline::getID() const
	{
		return thisid;
	}

}