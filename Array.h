#ifndef ARRAY_H
#define ARRAY_H

template<typename Type>
class Array<Type>
{
	Array<Type>();
	Array<Type>(Array<Type> &);
	~Array<Type>();
};

#endif