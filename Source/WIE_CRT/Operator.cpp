#include <Wintexports/Wintexports.h>

#pragma region new / delete

#include <vcruntime_new.h>

/*
 * This implementation like old MSVC which returned a null pointer on an allocation failure,
 * while new MSVC throws std::bad_alloc.
 * So C28196(__WARNING_RETURNING_BAD_RESULT) and C6387(__WARNING_INVALID_PARAM_VALUE_1) are dismissed for a while.
 * See also: https://learn.microsoft.com/en-us/cpp/build/reference/zc-throwingnew-assume-operator-new-throws
 */

namespace std
{
    const std::nothrow_t nothrow;
}

#pragma warning(push)
#pragma warning(disable: __WARNING_RETURNING_BAD_RESULT)
#pragma warning(disable: __WARNING_INVALID_PARAM_VALUE_1)

_NODISCARD
_Ret_notnull_
_Post_writable_byte_size_(_Size)
_VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t _Size)
{
    return RtlAllocateHeap(CURRENT_PROCESS_HEAP, 0, _Size);
}

_NODISCARD
_Ret_notnull_
_Post_writable_byte_size_(_Size)
_VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t _Size)
{
    return RtlAllocateHeap(CURRENT_PROCESS_HEAP, 0, _Size);
}

#pragma warning(pop)

_NODISCARD
_Ret_maybenull_
_Success_(return != NULL)
_Post_writable_byte_size_(_Size)
_VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t _Size, ::std::nothrow_t const&) noexcept
{
    return RtlAllocateHeap(CURRENT_PROCESS_HEAP, 0, _Size);
}

_NODISCARD
_Ret_maybenull_
_Success_(return != NULL)
_Post_writable_byte_size_(_Size)
_VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t _Size, ::std::nothrow_t const&) noexcept
{
    return RtlAllocateHeap(CURRENT_PROCESS_HEAP, 0, _Size);
}

void __CRTDECL operator delete(void* _Block) noexcept
{
    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, _Block);
}

void __CRTDECL operator delete(void* _Block, ::std::nothrow_t const&) noexcept
{
    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, _Block);
}

void __CRTDECL operator delete[](void* _Block) noexcept
{
    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, _Block);
}

void __CRTDECL operator delete[](void* _Block, ::std::nothrow_t const&) noexcept
{
    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, _Block);
}

void __CRTDECL operator delete(void* _Block, size_t _Size) noexcept
{
    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, _Block);
}

void __CRTDECL operator delete[](void* _Block, size_t _Size) noexcept
{
    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, _Block);
}

#pragma endregion new / delete
