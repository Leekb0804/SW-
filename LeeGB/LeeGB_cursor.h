#ifndef __CURSOR_H__
#define __CURSOR_H__

#include <Windows.h>

void SetCurrentCursorPos(int x, int y); // ���ϴ� ��ǥ������ Ŀ�� �̵�
COORD GetCurrentCursorPos(void);        // ���� Ŀ�� ��ġ ��ȯ
void RemoveCursor(void);                // Ŀ�� ��� ���ֱ�

#endif // !__CURSOR_H__
