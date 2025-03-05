#pragma once

#define WIN_LEAN_AND_MEAN				// 윈도우 매크로 간추린 버전?
#define NOMINMAX						// c의 min max, window 의 min max 충돌 방지.

#include <windows.h>					// 메시지 박스 출력용.
#include <comdef.h>						// 에러.

// 오류 메시지 출력 매크로 함수.
#define ShowErrorMessage(message, reason)                \
wchar_t buffer[256] = {};                                \
swprintf_s(buffer, 256, TEXT("[File: %s]\n[Line: %d]\n[Function: %s]\n[Message: %s]\n[Reason: %s]"), TEXT(__FILE__), __LINE__, TEXT(__FUNCTION__), message, reason );    \
MessageBox(nullptr, buffer, TEXT("Error"), MB_OK);


// D3D 호출 실패 확인 매크로 함수.
#define ThrowIfFailed(result, message)					\
if(FAILED(result))										\
{														\
	_com_error error(result);							\
	ShowErrorMessage(message, error.ErrorMessage());	\
	__debugbreak();										\
}