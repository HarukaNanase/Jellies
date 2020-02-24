#pragma once

#include <unordered_map>
#include <memory>
#include <string>


/*!
 * \class ResourceManager
 *
 * \brief  A templated class that allows for the loading and destruction of the resources. This class ensures
 *		   strong ownership of the resources by the managers.
 */
template<typename ManagerType, class Type>
class ResourceManager
{

private:
	std::unordered_map<std::string, std::unique_ptr<Type>> Resources;
	Type* Find(const std::string& _assetName);

public:
	std::unordered_map<std::string, std::unique_ptr<Type>>& GetResources();
	Type* Get(const std::string& _assetName);
	void AddResource(const std::string& _assetName, std::unique_ptr<Type>& _asset);
	void RemoveResource(const std::string& _assetName);
	virtual void DestroyResource(const std::string& _assetName) = 0;
	virtual Type& LoadResource(const std::string& _assetName, const std::string& _assetPath) = 0;
	unsigned int CurrentId = 0;
protected:


};

template<typename ManagerType, class Type>
std::unordered_map<std::string, std::unique_ptr<Type>>& ResourceManager<ManagerType, Type>::GetResources()
{
	return this->Resources;
}

template<typename ManagerType, class Type>
inline Type* ResourceManager<ManagerType, Type>::Find(const std::string& _assetName)
{
	auto it = Resources.find(_assetName);
	if (it != Resources.end())
		return it->second.get();
	else
		return nullptr;
}

template<typename ManagerType, class Type>
inline void ResourceManager<ManagerType, Type>::RemoveResource(const std::string& _assetName)
{
		this->Resources.erase(_assetName);
}

template<typename ManagerType, class Type>
inline void ResourceManager<ManagerType, Type>::AddResource(const std::string& _assetName, std::unique_ptr<Type>& _asset)
{
	this->Resources.emplace(_assetName, std::move(_asset));
}

template<typename ManagerType, class Type>
inline Type* ResourceManager<ManagerType, Type>::Get(const std::string& _assetName)
{
	auto asset = Find(_assetName);
	if (asset)
		return asset;
	else {
		std::string message = std::string("Couldn't find asset: ") + _assetName;
		return nullptr;
	}
		
}

