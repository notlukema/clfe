#pragma once
/*
template<typename T>
class Template
{
public:
	T* obj;
	Template(T obj);
	T& getObj();

};


template<typename T>
Template<T>::Template(T obj) : obj(&obj) {}

template<typename T>
T& Template<T>::getObj()
{
	return *obj;
}
*/

template<typename T>
class Template
{
public:
	T* obj;
	Template(T obj) : obj(&obj) {}
	T& getObj()
	{
		return *obj;
	}

};