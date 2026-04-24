#ifndef CLFE_PIPELINE_H
#define CLFE_PIPELINE_H

#include "clfe/System.h"
#include "clfe/window/Window.h"
#include "clfe/InstanceInterface.h"
#include "clfe/SharedLink.h"

namespace clfe
{

	class Pipeline : public InstanceInterface<Pipeline>
	{
	private:
		static InstanceList<Pipeline>* PipelineList;

	public:
		static const Attachment PipelineAttachment;
		static InstanceListHandle<Pipeline> getPipelinesList();

		static bool sinit();
		static void sterminate();

	protected: // Shared links
		LinkPool<Window>* WindowPool;

	protected:
		Pipeline(void (*initfunc)(Pipeline* this_, Window* other) = nullptr, void (*termfunc)(Pipeline* this_, Window* other) = nullptr);

	public:
		virtual ~Pipeline();

		void attachWindow(Window* window);
		//virtual void draw() = 0;

		// More

	};

}

#endif