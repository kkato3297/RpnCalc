#pragma once

#define RPNCALC_YES
#define IN2RPC_YES

#define WINDOWS			0x10001
#define ANDROID			0x10002

#define EXECUTABLE		0x20001
#define SHARED_LIBRARY	0x20002
#define STATIC_LIBRARY	0x20004

#ifndef _NOEXCEPT
#if (defined(TARGET_PLATFORM) && TARGET_PLATFORM == WINDOWS)
#define _NOEXCEPT
#else
#define _NOEXCEPT noexcept
#endif
#endif