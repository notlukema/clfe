#ifndef CLFE_GLOBAL_H
#define CLFE_GLOBAL_H

#include <cstdint>

namespace clfe
{

	struct ApplicationInfo
	{
	public:
		const char* ApplicationName;
		uint32_t VersionMajor;
		uint32_t VersionMinor;
		uint32_t VersionPatch;

		ApplicationInfo(const char* applicationName, uint32_t versionMajor, uint32_t versionMinor, uint32_t versionPatch);

	};

	struct Global
	{
	public:
		Global() = delete;

		static constexpr uint32_t VersionMajor = 0;
		static constexpr uint32_t VersionMinor = 1;
		static constexpr uint32_t VersionPatch = 0;

		static constexpr const char* VersionStr = "0.1.0";

		static constexpr const char* Name = "CLFE";

	private:
		static ApplicationInfo appInfo;

	public:
		inline static ApplicationInfo getApplicationInfo()
		{
			return appInfo;
		}

		static void postApplicationInfo(const ApplicationInfo& applicationInfo);

	};

}

#endif