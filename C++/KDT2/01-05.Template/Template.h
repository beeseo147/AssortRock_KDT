#pragma once
#include <iostream>

inline int Sum(const int a, const int b)
{
	return a + b;
}

inline double Sum(const double a, const double b)
{
	return a + b;
}

// 동일하게 동작
//template<typename T>
template<class T>
T TemplateSum(const T& a, const T& b)
{
	return a + b;
}

template<class T1, class T2, class T3 = double>
T3 TemplateSum2(const T1& a, const T2& b)
{
	return (T3)a + b;
}

inline int Sum2(const int a, const int b = 20)
{
	return a + b;
}

template<class T, size_t WIDTH = 640, size_t HEIGHT = 480>
class FClass
{
public:
	size_t GetWidth() const { return Width; }
	size_t GetHeight() const { return Height; }
	size_t GetDefaultWidth() const { return WIDTH; }
	size_t GetDefaultHeight() const { return HEIGHT; }

	void Function(const T& InValue)
	{
		Value = InValue;

		// template에서 받아온 인자는 수정 불가!
		//WIDTH = Value;
		//Width = Value;
	}

	template<typename T2>
	T2 Function2()
	{
		T2 Var = 10.5;
		return (T2)Width + Var;
	}

private:
	T Value{};
	// 별도의 변수를 만들어서 초기값으로 넣어주면 수정 가능
	size_t Width = WIDTH;
	size_t Height = HEIGHT;//asdasd
};
template<typename T, size_t WIDTH = 640, size_t HEIGHT = 480>
class FClass2 : public FClass<T, WIDTH, HEIGHT>
{

};
class FClass3 : public FClass<int>
{

};
template<size_t WIDTH = 640, size_t HEIGHT = 480>
class FClass4 : public FClass<int, WIDTH, HEIGHT>
{

};

struct FStruct
{
private:
	int Value = 0;
	int Value2 = 2;

	// 특정 함수를 friend 처리 해서 private 맴버에 접근 가능하게 할 수 있다
	friend FStruct operator+(const FStruct& p1, const FStruct& p2);
};

inline FStruct operator+(const FStruct& InA, const FStruct& InB) {
	FStruct temp;
	temp.Value = InA.Value + InB.Value;
	temp.Value2 = InA.Value2 + InB.Value2;
	return temp;
}
