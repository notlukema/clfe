#include "InstanceExample.h"

namespace ex
{

	InstanceList<InstanceExample>* InstanceExample::ExampleList = nullptr;
	const Attachment InstanceExample::ExampleAttachment = Attachment(AttachmentLayers::Example, InstanceExample::init, InstanceExample::step, InstanceExample::terminate);

	bool InstanceExample::init()
	{
		ExampleList = new InstanceList<InstanceExample>(InstanceTypes::Example);
		return true;
	}

	void InstanceExample::step(float delf, double deld)
	{
	}

	void InstanceExample::terminate()
	{
		delete ExampleList;
		ExampleList = nullptr;
	}

}