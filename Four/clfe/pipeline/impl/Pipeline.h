#ifndef CLFE_PIPELINE_H
#define CLFE_PIPELINE_H

#include "clfe/System.h"
#include "clfe/window/Window.h"

namespace clfe
{

	class Pipeline
	{
	private:
		static InstanceList<Pipeline>* Pipelines;

	public:
		static const Attachment PipelineAttachment;
		static InstanceListHandle<Pipeline> getPipelinesList();

		static bool sinit();
		static void sterminate();

	protected:
		clid thisid;
		Pipeline(clid id);
		InstanceHandle<Pipeline>* instlink;

		//LinkWell<Pipeline, Window> windowLinkWell;

	public:
		virtual ~Pipeline();
		clid getID() const;

		//virtual void draw() = 0;
		//Window* thid;
		//virtual void initWindow(clfe::Window* window) = 0;

		// More

	};

}

#endif