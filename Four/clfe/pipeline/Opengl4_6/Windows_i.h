#ifndef CLFE_PIPELINE_OPENGL4_6_WINDOWS_H
#define CLFE_PIPELINE_OPENGL4_6_WINDOWS_H

#include "../impl/Pipeline.h"

namespace clfe
{
	
	class Pipeline_OpenGL4_6_Windows : public Pipeline
	{
	public: // Standard pipeline components
		static const char* const Name;
		static const PipelineEntry Entry;
		inline static Pipeline* getInstance()
		{
			return Entry.pipeline;
		}

	protected:
		Pipeline_OpenGL4_6_Windows();
		~Pipeline_OpenGL4_6_Windows() override;

	public:
		virtual bool init() override;
		virtual void initWindow(Window* window) override;

	};

}

#endif