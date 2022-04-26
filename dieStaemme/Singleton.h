#pragma once
#ifndef TSINGLETON
#define TSINGLETON


template <class T>
class TSingleton
{
protected:

	//Membervars
	static T* m_pSingleton;		//static object

public:

	//Memberfunctions

	//Destructor
	virtual ~TSingleton() { }

	//Get
	inline static T* Get()
	{
		if (!m_pSingleton)
			m_pSingleton = new T;

		return (m_pSingleton);
	}

	static void Del()
	{
		if (m_pSingleton)
		{
			delete (m_pSingleton);
			m_pSingleton = NULL;
		}
	}
};

template <class T>
T* TSingleton<T>::m_pSingleton = 0;

#endif