// 01-06.Container.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <unordered_map>
#include <format>

int main()
{
	// 빅오(영어 O) 표기법
	{
		// 알고리듬이나 라이브러리 성능을 이야기 할 때 빅오 표기법(Big-O notation)을 사용한다
		// 빅오 표기법은 성능을 절대적(1초가 걸렸다와 같이 명확하게)으로 표현하지 않고
		// 상대적으로 표현한다

		// 알고리듬 복잡도		빅오표기법	설명													알고리듬예시
		// 상수(constant)		O(1)		실행 시간이 입력 크기와 관계없다						배열의 원소에 접근하기
		// 로그(logarithmic)	O(log n)	실행 시간이 입력 크기에 대해 밑이 2인 로그 함수로 결정	이진탐색으로 정렬된 리스트에서 원소 찾기
		// 선형(linear)			O(n)		실행 시간이 입력 크기와 정비례한다						정렬되지 않은 리스트에서 원소 찾기
		// 선형 로그(lin log)	O(n log n)	실행 시간은 입력 크기에 대한 로그 함수의 선형 배수		병합 정렬
		// 제곱(Quadratic)		O(n^2)		실행 시간은 입력 크기의 제곱							2중 for, 선택정렬 등 느린 정렬
		// 지수(exponential)	O(2^n)		실행 시간은 입력 크기의 지수 함수						피보나치 수열

		// 빅오를 사용해서 시간복잡도(Time Complexity)와 공간복잡도(Space Complexity)를 표현하곤 합니다.
		// 시간복잡도는 특정 크기의 입력을 기준으로 할 때 필요한 연산의 횟수
		// 공간복잡도는 얼마나 많은 메모리가 필요한지

		// 왼쪽일수록 빠름(시간복잡도) / 왼쪽일수록 메모리를 적게 소모(공간복잡도)
		// O(1) O(log n) O(N) O(N log N) O(N^2) O(2^N)

		// 빅오 표기법 기준으로 성능이 좋다고해서 실제로 두 알고리듬을 비교했을때 결과가 빅오와 동일하게 나온다는 보장은 없습니다.
		// 예를 들면 입력 크기가 작을 때는 O(n^2) 알고리듬이 O(log N) 알고리듬 보다 실제로 성능이 더 빠를수도 있다.
		// 선형 메모리인 경우 cache miss가 발생할 확률이 엄청 줄어듬, 파편화된 메모리를 저근해야 하는 경우에는 cache miss 발생 확률이 높아지기 때문에

		// 결국 실제로 알고리듬을 도입하기 위해서는 타겟 디바이스에서 실제로 시간을 측정해야 정확하게 알 수 있다.
		// 그러나 빅오 뵤기법을 보고 대략적인 속도를 가늠할 수 있는 척도가 된다.
	}
	{
		// 표준 라이브러리를 사용하면, 직접 stack, 연결 리스트 등 과 같은 컨테이너를 구현하지 않아도 된다.
		// 일부 팀이나 언리얼 엔진에서는 표준보다 더 나은 성능을 추구하거나, 특수한 용도를 위해서 자체 컨테이너를 만들어서 사용하고 있습니다.
		// 일부 표준은 버전이나, platform에 따라 동작이 동일하지 않을 수 있습니다.

		// 표준 라이브러리에서 제공하는 컨테이너는 범용 데이터 구조로서 다양한 종류의 데이터(= 다양한 타입)를 묶어서 저장할수 있다
		// 템플릿을 사용해서 만들어졌다
		// STL(Standard Template Library)

		// [순차 컨테이너]
		// - array(정적 배열), vector(동적 배열), deque(덱), list, forward_list

		// [연관 컨테이너]
		// - map, multimap, set, multiset

		// [비정렬 연관 컨테이너(Hash Table; 해시 테이블)]
		// - unordered_map, unordered_multimap, unordered_set, unordered_multiset

		// [컨테이너 어댑터]
		// - queue, priority_queue, stack

		// [array]
		// #include <array>
		// 표준 C스타일 배열을 컨테이너로 구현한 것으로, 주어진 컨테이너 담긴 원소의 개수를
		// 정확히 알고 있다. vector와 다르게 size를 변경할 수 없다

		// [deque]
		// #include <deque>
		// 덱이라고 부르며, 양방향 큐(double-ended queue)의 줄임말이다.
		// 양끝에 원소를 추가하거나 삭제하는 연산이 상수(O(1)) 시간에 처리 가능하다
		// 중간에 추가하는 경우 다소 느린 선형 시간(O(N))에 처리한다
		// deque도 비선형 메모리 공간을 사용합니다. (메모리가 파편화 되어 있다)
		// vector보다 느릴 수 있다
		// 원소를 조회하는 연산을 빠르게 처리하고 싶고, 양끝에 추가가 빈번한 경우에 deque을 사용하면 유리
		// 대부분 vector를 사용하면 빠름

		// [vector] (TArray; Unreal vector)
		// #include <vector>
		// vector는 원소를 저장하고 각 원소에 임의로 접근(random access)할 수 있다.
		// vector는 배열처럼 원소를 메모리 공간에 연속적으로 저장한다
		// * vector는 동적 배열이다. 저장된 원소 수에 따라 크기가 자동으로 늘어나거나 줄어든다.
		// 마지막(끝)에 원소를 추가하거나 삭제하는 연산을 매우 빠르게 처리한다 (시간복잡도(O(1))
		// 원소가 추가될 때마다 크기도 늘어나야 한다.(공간복잡도 O(N))
		// 끝이 아닌 공간에 원소를 추가 또는 삭제하는 경우 느리다(O(N))
		// -> 새 원소를 추가하거나 삭제하려면 공간을 확보하거나 채우기 위해 모든 원소를 한칸씩 이동해야 하기 때문
		// 모든 원소를 조회(random access)하는 경우 걸리는 시간은 배열처럼 상수 시간(하나 하나 조회 기준)으로 아주 빠르다
		// 중간에 원소를 추가하거나 삭제하려면 다른 원소를 이동해서 시간이 좀 더 걸린긴 해도,
		// 다른 컨테이너보다 vector가 대채로 빠르다(원소의 갯수가 적은 경우)
		{
			{
				//std::vector<int> Vector{ 5, 0 ,3 };
				std::vector Vector{ 5, 0 ,3 };
				Vector.push_back(33);
				Vector.push_back(44);
				Vector.push_back(55);
			}
			{
				// 대략적으로 또는 명확하게 size를 예상할 수 있는 경우 반드시
				// resize(할당 + 초기화)또는 reserve(할당)로 공간을 할당해두자
				// reserve: capacity(용량)만 확보
				// resize: 용량 확보 이후 데이터 생성(초기화)
				std::vector<int> Vector;
				Vector.reserve(10);
				for (size_t i = 0; i < 10; ++i)
				{
					Vector.push_back(i);
				}
				//Vector.push_back(0);
			}
			{
				std::vector<int> Vector;
				Vector.resize(10);
				for (size_t i = 0; i < 10; ++i)
				{
					Vector[i] = i;
				}
			}
			// erase, insert
			{
				std::vector<int> Vector;
				Vector.reserve(10);
				for (size_t i = 0; i < 10; ++i)
				{
					Vector.push_back(i);
				}
				std::vector<int>::iterator It = std::find(Vector.begin(), Vector.end(), 4);
				// 못찾으면 end()가 It에 들어감
				if (It != Vector.end())
				{
					Vector.erase(It);
				}
				Vector.erase(Vector.begin() + 5);
				Vector.insert(Vector.begin() + 3, 1000);
				//Vector.insert(Vector.begin() + 3, 1000);
			}
		}

		

	}
}