#pragma once
#include "CoreTypes.h"

// weak_ptr 사용성 개선 목적으로 제작
// _Ty는 UObject와 관련이 있어야 합니다.
template<class _Ty>
class engine_weak_ptr : public weak_ptr<_Ty>
{
public:
	engine_weak_ptr() noexcept {}
	engine_weak_ptr(const engine_weak_ptr& InOther) noexcept : weak_ptr<_Ty>(InOther) { }

	template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
	engine_weak_ptr(const shared_ptr<_Ty2>& InOther) noexcept : weak_ptr<_Ty>(InOther) { }

	engine_weak_ptr& operator=(const engine_weak_ptr& InOther) noexcept
	{
		engine_weak_ptr(InOther).swap(*this);
		return *this;
	}

	template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
	engine_weak_ptr& operator=(const engine_weak_ptr<_Ty2>& _Right) noexcept {
		engine_weak_ptr(_Right).swap(*this);
		return *this;
	}

	engine_weak_ptr& operator=(engine_weak_ptr&& _Right) noexcept {
		engine_weak_ptr(_STD move(_Right)).swap(*this);
		return *this;
	}

	template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
	engine_weak_ptr& operator=(engine_weak_ptr<_Ty2>&& _Right) noexcept {
		engine_weak_ptr(_STD move(_Right)).swap(*this);
		return *this;
	}

	template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
	engine_weak_ptr& operator=(const shared_ptr<_Ty2>& _Right) noexcept {
		engine_weak_ptr(_Right).swap(*this);
		return *this;
	}

	template <class _Ty2 = _Ty, enable_if_t<!disjunction_v<is_array<_Ty2>, is_void<_Ty2>>, int> = 0>
	_NODISCARD _Ty2& operator*() const noexcept {
		return *Get();
	}

	template <class _Ty2 = _Ty, enable_if_t<!is_array_v<_Ty2>, int> = 0>
	_NODISCARD _Ty2* operator->() const noexcept {
		return Get();
	}
	template <class _Ty2 = _Ty, enable_if_t<!is_array_v<_Ty2>, int> = 0>
	_NODISCARD _Ty2* Get() const noexcept {
#if WITH_DEBUG
		if (!IsValid())
		{
			_ASSERT(false);
		}
#endif
		return this->lock().get();
	}

	explicit operator bool() const noexcept
	{
		return IsValid();
	}

	bool IsValid() const noexcept
	{
		if (!this) { return false; }
		return !this->expired();
	}
};