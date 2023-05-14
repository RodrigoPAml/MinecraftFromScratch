#include <BuildCraft.hpp>
#include "Path.hpp"

#include <Windows.h>

namespace BuildCraft {
namespace Base {

	std::string Path::Retreat(const std::string& path, unsigned int n)
	{
		if(!path.empty())
		{
			int cut = path.size();

			for(int i = path.size() - 1; i >= 0; i--)
			{
				if(n == 0) break;

				if(path[i] == '/' || path[i] == '\\')
				{
					cut = i;
					n--;
				}
			}

			return path.substr(0, cut);
		}

		return "";
	}

	std::string Path::GetCurrent(const int retreat)
	{
		char buffer[MAX_PATH];

		GetModuleFileNameA(NULL, buffer, MAX_PATH);

		std::string path = std::string(buffer);

		return Path::Retreat(path, retreat);
	}

	bool Path::isDirectory(const std::string& path)
	{
		return std::filesystem::is_directory(path);
	}

	bool Path::isFile(const std::string& path)
	{
		return std::filesystem::is_regular_file(path);
	}

	bool Path::DirectoryExists(const std::string& path)
	{
		return std::filesystem::exists(path);
	}

	bool Path::FileExists(const std::string& path)
	{
		return std::filesystem::exists(path);
	}

	std::vector<std::string> Path::ListDirectories(const std::string& root, const bool onlyName)
	{
		std::vector<std::string> paths;

		for(auto& it : std::filesystem::directory_iterator(root))
		{
			if(onlyName)
			{
				std::string name = GetNameFromPath(it.path().generic_string());

				paths.push_back(name);
			}
			else
			{
				paths.push_back(it.path().generic_string());
			}
		}

		return paths;
	}

	std::string Path::GetNameFromPath(const std::string path)
	{
		int size = path.find_last_of('/');

		if(size != -1)
		{
			return path.substr(size + 1);
		}
		else
		{
			return path;
		}
	}
}}
