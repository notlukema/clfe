#ifndef CLFE_PIPELINE_H
#define CLFE_PIPELINE_H

#include "clfe/window/Window.h"
#include "clfe/System.h"

namespace clfe
{

	class Pipeline
	{
	private:
		static InstanceList<Pipeline>* Pipelines;

	public:
		static const Attachment PipelineAttachment;
		static InstanceListWrapper<Pipeline>* getPipelinesList();

		static bool sinit();
		static void sterminate();

	protected:
		clid thisid;
		Pipeline(clid id);

	public:
		virtual ~Pipeline();
		clid getID() const;

		//virtual void draw() = 0;
		
		virtual void initWindow(Window* window) = 0;

		// More

	};

}

#endif