#pragma once

#include <iostream>
using namespace std;

// Vector2
template <class T>
class Vector2
{
public:
	T X = 0, Y = 0;
public:
	Vector2(const T x = 0, const T y = 0);
	Vector2(const Vector2<T> &Target);
	Vector2<T> &operator=(const const Vector2<T> &Target);

	template <typename T>
	friend ostream &operator<<(ostream &outstream, const Vector2<T> &Vector);
};

template <typename T>
Vector2<T>::Vector2(const T x, const T y) : X(x), Y(y) {}

template <typename T>
Vector2<T>::Vector2(const Vector2<T> &Target) : X(Target.X), Y(Target.Y) {}

template <typename T>
Vector2<T> &Vector2<T>::operator=(const Vector2<T> &Target)
{
	this->X = Target.X;
	this->Y = Target.Y;
	return *this;
}

template <typename T>
ostream &operator<<(ostream &outstream, const Vector2<T> &Vector)
{
	outstream << "(" << Vector.X << "," << Vector.Y << ")";
	return outstream;
}

// Vector3
template <class T>
class Vector3
{
public:
	T X = 0, Y = 0, Z = 0;
public:
	Vector3(const T x = 0, const T y = 0, const T z = 0);
	Vector3(const Vector3<T> &Target);
	Vector3<T> &operator=(const const Vector3<T> &Target);

	template <typename T>
	friend ostream &operator<<(ostream &outstream, const Vector3<T> &Vector);
};

template <typename T>
Vector3<T>::Vector3(const T x, const T y, const T z) : X(x), Y(y), Z(z) {}

template <typename T>
Vector3<T>::Vector3(const Vector3<T> &Target) : X(Target.X), Y(Target.Y),Z(Target.Z) {}

template <typename T>
Vector3<T> &Vector3<T>::operator=(const Vector3<T> &Target)
{
	this->X = Target.X;
	this->Y = Target.Y;
	this->Z = Target.Z;
	return *this;
}

template <typename T>
ostream &operator<<(ostream &outstream, const Vector3<T> &Vector)
{
	outstream << "(" << Vector.X << "," << Vector.Y <<","<<Vector.Z<< ")";
	return outstream;
}