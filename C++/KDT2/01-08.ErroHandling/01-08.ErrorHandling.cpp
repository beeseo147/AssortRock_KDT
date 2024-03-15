// 01-08.ErroHandling.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cassert>
//error code 방식
// return 0; nullptr erro
int Function(int* InPointer) {
    if (InPointer == nullptr) {
        return 0;
    }
    *InPointer = 100;
    return 1;
}

enum EErrorCode : uint8_t
{
    Nullptr =0,
    Success =1,
};
class FClass
{
public:
    FClass(int i)/*noexcept*/ //예외를 던지지않겠다(이렇게 선언하고 throw하면 crash발생)
    {
        if (i == 0)
        {
            throw 0;
        }
    }
};
EErrorCode Function2(int* InPointer) 
{
    //_ASSERT(InPointer);
    if (InPointer == nullptr) {
        //check . ensure
        //_ASSERT(false);
        return EErrorCode::Nullptr;
    }
    *InPointer = 100;
    return EErrorCode::Success;
}

void FunctionException(int* InPointer) 
{
    if (InPointer == nullptr)
    {
        throw "InPointer is nullptr";
    }
    *InPointer = 100;
}
int main()
{
    {
        int Value = 0;
        int ErrorCode = Function(&Value);
        switch (ErrorCode)
        {
        case 0:
            std::cout << "inpult Value is nullptr\n";
            break;
        case 1:
            std::cout << "성공\n";
            break;
        default:
            break;
        }
    }
    {
        int Value = 0;
        EErrorCode ErrorCode = Function2(&Value);
        /*if (ErrorCode == EErrorCode::Nullptr) {
            return;
        }*/
        if (ErrorCode) {
            std::cout << "성공\n";
        }
        switch (ErrorCode)
        {
        case Nullptr:
            std::cout << "inpult Value is nullptr\n";
            break;
        case Success:
            std::cout << "성공\n";
            break;
        default:
            break;
        }
    }
    {
        try
        {
            int Value = 0;
            FunctionException(&Value);
            FClass Class(1);
            FClass Class2(0);
            FunctionException(nullptr);
        }
        catch (const char * Error) 
        {
            std::cout << "Error\n";
        }
        catch (int Error) {
            std::cout << Error << std::endl;
        }
        catch (...)
        {
            std::cout << "UnKnown Error\n";
        }
    }
}