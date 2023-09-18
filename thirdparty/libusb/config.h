/* config.h.  Manual config for Godot, mostly handled in SConstruct. */

#ifdef __GNUC__
#define _GNU_SOURCE 1
#define DEFAULT_VISIBILITY __attribute__((visibility("default")))
#define PRINTF_FORMAT(a, b) __attribute__((format(printf, a, b)))
#else
#define DEFAULT_VISIBILITY
#define PRINTF_FORMAT(a, b)
#endif // __GNUC__

#ifdef _MSC_VER
#if (_MSC_VER < 1800)
#error "Visual Studio 2013 or later is required."
#endif
#if (_MSC_VER <= 1900)
#define __func__ __FUNCTION__
#endif
#if (_MSC_VER >= 1900)
#define _TIMESPEC_DEFINED 1
#endif
#pragma warning(disable : 4127) // Conditional expression is constant.
#pragma warning(disable : 4200) // Nonstandard extension used: zero-sized array in struct/union.
#pragma warning(disable : 4201) // Nonstandard extension used: nameless struct/union.
#pragma warning(disable : 4324) // Structure was padded due to __declspec(align()).
#pragma warning(disable : 4996) // 'GetVersionExA': was declared deprecated.
#if defined(_PREFAST_)
#pragma warning(disable : 28719) // Banned API Usage: 'GetVersionExA' is insecure and has been marked deprecated.
#pragma warning(disable : 28125) // The function 'InitializeCriticalSection' must be called from within a try/except block.
#endif
#endif // _MSC_VER
