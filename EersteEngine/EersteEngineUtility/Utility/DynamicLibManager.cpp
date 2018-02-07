#include "../Utility/DynamicLibManager.h"

namespace ee
{
	DynamicLibManager::DynamicLibManager()
	{
	}

	DynamicLib* DynamicLibManager::Load(const String& name)
	{
		String filename = name;
		const UINT32 length = (UINT32)filename.length();
		const String extension = String(".") + DynamicLib::EXTENSION;
		const UINT32 extLength = (UINT32)extension.length();
		if (length <= extLength || filename.substr(length - extLength) != extension)
			filename += extension;

		if (DynamicLib::PREFIX != nullptr)
			filename = DynamicLib::PREFIX + filename;

		auto iterFind = _loadedLibraries.find(filename);
		if (iterFind != _loadedLibraries.end())
		{
			return iterFind->second;
		}
		else
		{
			DynamicLib* newLib = new DynamicLib(filename);
			_loadedLibraries[filename] = newLib;

			return newLib;
		}
	}

	void DynamicLibManager::Unload(DynamicLib* library)
	{
		auto iterFind = _loadedLibraries.find(library->getName());
		if (iterFind != _loadedLibraries.end())
		{
			_loadedLibraries.erase(iterFind);
		}

		library->Unload();
		delete library;
	}

	DynamicLibManager::~DynamicLibManager()
	{
		for (auto& entry : _loadedLibraries)
		{
			entry.second->Unload();
			delete entry.second;
		}

		_loadedLibraries.clear();
	}

	DynamicLibManager& gDynamicLibManager()
	{
		return DynamicLibManager::Instance();
	}
}
