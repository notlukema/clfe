#ifndef CLFE_PIPELINE_H
#define CLFE_PIPELINE_H

#include "clfe/System.h"
#include "clfe/window/Window.h"
#include "clfe/SharedLink.h"

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

	protected: // Shared links
		//LinkPool* WindowPool;


	protected:
		clid thisid;
		Pipeline(clid id);
		InstanceHandle<Pipeline>* instlink;

	public:
		virtual ~Pipeline();
		clid getID() const;

		//virtual void draw() = 0;
		virtual void initWindow(clfe::Window* window) = 0;

		// More

	};

}

#endif