#pragma once
//header에는 선언만
typedef enum MY_MENU {
	EXIT,
	NEW,
	SEARCH,
	PRINT,
	REMOVE
} MY_MENU;

void EventLoopRun(void);
MY_MENU PrintMenu(void);
void PrintList(void);
void PrintListReverse(void);
void Search(void);
USERDATA* SearchListByName(USERDATA* pUser, char* pszName);
void _SearchByName(void);
void EditUserData(USERDATA* pUser);