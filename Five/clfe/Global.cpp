#include "Global.h"

namespace clfe
{

	ApplicationInfo::ApplicationInfo(const char* applicationName, uint32_t versionMajor, uint32_t versionMinor, uint32_t versionPatch) :
		ApplicationName(applicationName), VersionMajor(versionMajor), VersionMinor(versionMinor), VersionPatch(versionPatch)
	{}

	ApplicationInfo Global::appInfo = ApplicationInfo("CLFE Application", 1, 0, 0);

	void Global::postApplicationInfo(const ApplicationInfo& applicationInfo)
	{
		appInfo = applicationInfo;
	}

}