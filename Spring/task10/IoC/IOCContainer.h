#include "stdafx.h"
#include "BlackJack.cpp"

class IOCContainer
{
public:
	static IOCContainer& instanceClass()
	{
		static IOCContainer instance;
		return instance;
	}

	template<class T>
	void registerClass(shared_ptr<T> t)
	{
		const type_info* typeId = &typeid(T);
		registerClass(typeId->raw_name(), t);
	}

	template<class T>
	void registerClass(const string& id, shared_ptr<T> t)
	{
		lock_guard<mutex> lock(mapMutex);

		map<string, shared_ptr<void> >::iterator iter = mapping.find(id);

		if (iter == mapping.end())
		{
			mapping[id] = t;
		}
	}

	template<class T>
	shared_ptr<T> resolveClass()
	{
		const type_info* typeId = &typeid(T);
		return resolveClass<T>(typeId->raw_name());
	}

	template<class T>
	shared_ptr<T> resolveClass(const string& id)
	{
		lock_guard<mutex> lock(mapMutex);

		map<string, shared_ptr<void> >::iterator iter = mapping.find(id);

		if (iter != mapping.end())
		{
			return static_pointer_cast<T>(iter->second);
		}
	}

private:
	map<string, shared_ptr<void> > mapping;
	mutex mapMutex;

	IOCContainer() {}
	IOCContainer(const IOCContainer&);
};