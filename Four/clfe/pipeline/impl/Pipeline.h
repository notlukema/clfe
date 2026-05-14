#ifndef CLFE_PIPELINE_H
#define CLFE_PIPELINE_H

#include "../PipelineData.h"
#include "clfe/System.h"
#include "clfe/window/Window.h"
#include "clfe/object/Scene.h"

namespace clfe
{

	class Pipeline : public InstanceInterface<Pipeline>
	{
	private:
		static InstanceList<Pipeline>* PipelineList;

	public:
		static const Attachment PipelineAttachment;

		static inline InstanceListHandle<Pipeline> getInstanceList()
		{
			return PipelineList->getHandle();
		}

		static bool sinit();
		static void sterminate();

	protected:
		Pipeline();

	public:
		virtual ~Pipeline() = default;

		virtual PipelineData getData() = 0;

		virtual bool compatible(Window* window) = 0;
		virtual bool attachWindow(Window* window) = 0;
		virtual bool detachWindow(Window* window) = 0;

		virtual bool attachScene(Scene* scene) = 0;
		virtual bool detachScene(Scene* scene) = 0;

		virtual void draw() = 0;

	};

	inline InstanceListHandle<Pipeline> getPipelineList()
	{
		return Pipeline::getInstanceList();
	}

}

#endif