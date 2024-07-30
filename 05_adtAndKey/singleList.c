#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singleList.h"

MYNODE g_HeadNode = { 0 };
MYNODE g_TailNode = { 0 };
static unsigned int g_listCount = 0;


void InitList(void)
{
	ReleaseList();
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;
}

int IsEmpty(void)
{
	if (g_HeadNode.pNext == &g_TailNode ||
		g_HeadNode.pNext == NULL)
		return 1;

	return 0;
}

void ReleaseList(void)
{
	if (IsEmpty())
		return; 

	MYNODE* pTmp = g_HeadNode.pNext;
	MYNODE* pDelete;
	while (pTmp != &g_TailNode)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;
		free(pDelete->pData);
		free(pDelete);
	}

	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;
}

char* GetKey(void* thisPointer)
{
	// 매개변수로 넘어온 thisPointer는 USERDATA일 것.
	USERDATA* pUser = (USERDATA*)thisPointer;
	return pUser->name; // 이게 key가 된다.
	//return pUser->phone; 
}

void AddNewNode(int age, char* pszName, char* pszPhone)
{
	USERDATA* pNewData = calloc(1, sizeof(USERDATA));
	pNewData->age = age;
	strcpy_s(pNewData->name, sizeof(pNewData->name), pszName);
	strcpy_s(pNewData->phone, sizeof(pNewData->phone), pszPhone);

	MYNODE* pNewNode = calloc(1, sizeof(MYNODE));
	pNewNode->pData = pNewData;
	pNewNode->GetKey = GetKey;

	MYNODE* pPrevNode = g_TailNode.pPrev;
	pPrevNode->pNext = pNewNode;
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = &g_TailNode;
	g_TailNode.pPrev = pNewNode;

	++g_listCount;
}


void SwapNode(MYNODE* pLeft, MYNODE* pRight)
{
	void* pTmp = pLeft->pData;
	pLeft->pData = pRight->pData;
	pRight->pData = pTmp;
}

void SortListByAge(void)
{
	if (IsEmpty())
		return;

	MYNODE* pTmp = g_HeadNode.pNext;
	MYNODE* pSelected = NULL;
	MYNODE* pCmp = NULL;
	while (pTmp != NULL && pTmp != g_TailNode.pPrev)
	{
		pSelected = pTmp;
		pCmp = pTmp->pNext;
		while (pCmp != NULL && pCmp != &g_TailNode)
		{
			if (strcmp(
					pSelected->GetKey(pSelected->pData),
					pCmp->GetKey(pCmp->pData)) > 0)
				pSelected = pCmp;

			pCmp = pCmp->pNext;
		}

		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);

		pSelected = NULL;
		pTmp = pTmp->pNext;
	}
}