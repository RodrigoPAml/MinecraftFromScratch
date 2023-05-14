#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	class Path
	{
	public:
		static std::string Retreat(const std::string& path, unsigned int n = 0);

		static std::string GetCurrent(const int retreat = 1);

		static bool isDirectory(const std::string& path);

		static bool isFile(const std::string& path);

		static bool DirectoryExists(const std::string& path);

		static bool FileExists(const std::string& path);

		static std::vector<std::string> ListDirectories(const std::string& root, const bool onlyName = true);

		static std::string GetNameFromPath(const std::string path);
	};
}}

