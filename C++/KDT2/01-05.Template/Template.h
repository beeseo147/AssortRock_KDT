#pragma once
#include <iostream>
#include <format>
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

//템플릿 특수화
//특정 타입에 대해서는 해당 버젼의 Template 함수를 호출
template<>
inline double TemplateSum(const double &InA,const double &InB) {
	std::cout << "Double 버전의 Template Sum\n";
	return InA + InB;
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
inline void HandleValue(int InValue) {
	std::cout << "int : " << InValue << std::endl;
}
inline void HandleValue(float InValue) {
	std::cout << "float : " << InValue << std::endl;
}

inline void HandleValue(std::string_view InValue) {
	std::cout << "string_view : " << InValue << std::endl;
}

template<typename...T>
void ProcessValue(const T&... InValues) {
	(HandleValue(InValues), ...);
}

// consteval 키워드를 붙히면 컴파일 타임에 함수호출 결과를 받아올 수 있습니다.
// 컴파일 타임에 값을 예측할 수 있는 경우 계산해서 바로 값을 넣어버린다.
consteval inline unsigned long long Factorial(unsigned char f)
{
	if (f == 0)
	{
		return 1;
	}
	else
	{
		return f * Factorial(f - 1);
	}
}

template <unsigned char f>
class FactorialTemplate
{
public:
	static const unsigned long long Value{ f * FactorialTemplate<f - 1>::Value };
};

template<>
class FactorialTemplate<0>
{
public:
	static const unsigned long long Value{ 1 };
};

template<int i>
class TLoop
{
public:
	template<typename FuncType>
	static inline void Run(FuncType Function)
	{
		TLoop<i - 1>::Run(Function);
		Function(i);
	}
};

template<>
class TLoop<0>
{
public:
	template<typename FuncType>
	static inline void Run(FuncType) {}
};