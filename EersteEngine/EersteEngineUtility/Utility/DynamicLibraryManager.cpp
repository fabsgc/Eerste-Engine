#include "../Utility/DynamicLibraryManager.h"

namespace ee
{
	DynamicLibraryManager::DynamicLibraryManager()
	{
	}

	DynamicLibrary* DynamicLibraryManager::Load(const String& name)
	{
		String filename = name;
		const UINT32 length = (UINT32)filename.length();
		const String extension = String(".") + DynamicLibrary::EXTENSION;
		const UINT32 extLength = (UINT32)extension.length();
		if (length <= extLength || filename.substr(length - extLength) != extension)
			filename += extension;

		if (DynamicLibrary::PREFIX != nullptr)
			filename = DynamicLibrary::PREFIX + filename;

		auto iterFind = _loadedLibraries.find(filename);
		if (iterFind != _loadedLibraries.end())
		{
			return iterFind->second;
		}
		else
		{
			DynamicLibrary* newLib = new DynamicLibrary(filename);
			_loadedLibraries[filename] = newLib;

			return newLib;
		}
	}

	void DynamicLibraryManager::Unload(DynamicLibrary* library)
	{
		auto iterFind = _loadedLibraries.find(library->getName());
		if (iterFind != _loadedLibraries.end())
		{
			_loadedLibraries.erase(iterFind);
		}

		library->Unload();
		delete library;
	}

	DynamicLibraryManager::~DynamicLibraryManager()
	{
		for (auto& entry : _loadedLibraries)
		{
			entry.second->Unload();
			delete entry.second;
		}

		_loadedLibraries.clear();
	}

	DynamicLibraryManager& gDynamicLibraryManager()
	{
		return DynamicLibraryManager::Instance();
	}
}
