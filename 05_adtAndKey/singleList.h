#pragma once

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
} USERDATA;

typedef struct MYNODE
{
	void* pData;
	struct MYNODE* pNext;
	struct MYNODE* pPrev;
	char* (*GetKey)(void* thisPointer);
} MYNODE;


extern MYNODE g_HeadNode;
extern MYNODE g_TailNode;

void InitList(void);
void ReleaseList(void);
void AddNewNode(int age, char* pszName, char* pszPhone);
void SortListByAge(void);