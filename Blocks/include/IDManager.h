#pragma once
#include <atomic>


typedef unsigned int Id;

template<typename TSystem>
class IDManager
{

private:
	static std::atomic<Id> NextId;
public:
	template<typename T>
	static Id GetId() {
		static Id id = NextId++;
		return id;
	}
};

template<typename TSystem>
std::atomic<Id> IDManager<TSystem>::NextId{ 0 };
