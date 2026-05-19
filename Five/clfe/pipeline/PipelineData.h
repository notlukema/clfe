#ifndef CLFE_PIPELINEDATA_H
#define CLFE_PIPELINEDATA_H

#include "clfe/UniString.h"

namespace clfe
{

	struct PipelineData
	{
	public:
		const UniString PipelineName;
		const UniString VendorName;
		const UniString RendererName;
		const UniString VersionString;

		const int VersionMajor;
		const int VersionMinor;

		PipelineData(const UniString& pipelineName, const UniString& vendorName, const UniString& rendererName, const UniString& versionString, int versionMajor, int versionMinor) :
			PipelineName(pipelineName), VendorName(vendorName), RendererName(rendererName), VersionString(versionString), VersionMajor(versionMajor), VersionMinor(versionMinor)
		{}

	};

}

#endif