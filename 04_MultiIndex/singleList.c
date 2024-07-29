#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singleList.h"


USERDATA g_HeadNode = { 0, "_DummyHead_" };
USERDATA g_TailNode = { 0, "_DummyTail_" };
static unsigned int g_listCount = 0;

USERDATA** g_idxListAge = NULL;
USERDATA** g_idxListName = NULL;


unsigned int GetListCount(void)
{
	return g_listCount;
}

unsigned int RecalcListCount(void)
{
	unsigned int cnt = 0;
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		++cnt;
		pTmp = pTmp->pNext;
	}
	return g_listCount;
}


void InitList(void)
{
	ReleaseList();
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;

	g_idxListAge = NULL;
	g_idxListName = NULL;
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

	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pDelete;
	while (pTmp != &g_TailNode)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		printf("Delete: %d, %s, %s\n",
			pDelete->age, pDelete->name, pDelete->phone);

		free(pDelete);
	}

	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;

	if (g_idxListAge != NULL)
	{
		free(g_idxListAge);
		g_idxListAge = NULL;
	}

	if (g_idxListName != NULL)
	{
		free(g_idxListName);
		g_idxListName = NULL;
	}
}


void NodeDataCopy(USERDATA* pLeft, USERDATA* pRight)
{
	pLeft->age = pRight->age;
	strcpy_s(pLeft->name, sizeof(pLeft->name), pRight->name);
	strcpy_s(pLeft->phone, sizeof(pLeft->phone), pRight->phone);
}

void SwapNode(USERDATA* pLeft, USERDATA* pRight)
{
	USERDATA tmp = *pLeft;
	NodeDataCopy(pLeft, pRight);
	NodeDataCopy(pRight, &tmp);
}

void SortListByName(void)
{
	if (IsEmpty())
		return;

	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pSelected = NULL;
	USERDATA* pCmp = NULL;
	while (pTmp != NULL && pTmp != g_TailNode.pPrev)
	{
		pSelected = pTmp;
		pCmp = pTmp->pNext;
		while (pCmp != NULL && pCmp != &g_TailNode)
		{
			if (strcmp(pSelected->name, pCmp->name) > 0)
				pSelected = pCmp;

			pCmp = pCmp->pNext;
		}

		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);

		pSelected = NULL;
		pTmp = pTmp->pNext;
	}
}

void SortListByAge(void)
{
	if (IsEmpty())
		return;

	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pSelected = NULL;
	USERDATA* pCmp = NULL;
	while (pTmp != NULL && pTmp != g_TailNode.pPrev)
	{
		pSelected = pTmp;
		pCmp = pTmp->pNext;
		while (pCmp != NULL && pCmp != &g_TailNode)
		{
			if (pSelected->age > pCmp->age)
				pSelected = pCmp;

			pCmp = pCmp->pNext;
		}

		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);

		pSelected = NULL;
		pTmp = pTmp->pNext;
	}
}

int SearchListByName(USERDATA* pUser, char* pszName)
{
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (strcmp(pTmp->name, pszName) == 0)
		{
			memcpy(pUser, pTmp, sizeof(USERDATA));
			return 1;
		}

		pTmp = pTmp->pNext;
	}

	return 0;
}

int SearchListByPhone(USERDATA* pUser, char* pszPhone)
{
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (strcmp(pTmp->phone, pszPhone) == 0)
		{
			memcpy(pUser, pTmp, sizeof(USERDATA));
			return 1;
		}

		pTmp = pTmp->pNext;
	}

	return 0;
}

int RemoveByName(char* pszName)
{
	USERDATA* pCur = g_HeadNode.pNext;
	USERDATA* pNextNode;
	USERDATA* pPrevNode;
	while (pCur != NULL && pCur != &g_TailNode)
	{
		if (strcmp(pCur->name, pszName) == 0)
		{
			pNextNode = pCur->pNext;
			pPrevNode = pCur->pPrev;

			pNextNode->pPrev = pCur->pPrev;
			pPrevNode->pNext = pCur->pNext;

			free(pCur);
			--g_listCount;
			UpdateIndexAll();
			return 1;
		}

		pCur = pCur->pNext;
	}

	return 0;
}

void AddNewNode(int age, char* pszName, char* pszPhone)
{
	USERDATA* pNewNode = calloc(1, sizeof(USERDATA));
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);

	USERDATA* pPrevNode = g_TailNode.pPrev;
	pPrevNode->pNext = pNewNode;
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = &g_TailNode;
	g_TailNode.pPrev = pNewNode;

	++g_listCount;
	UpdateIndexAll();
}

int SearchListByAge(int age)
{
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (pTmp->age == age)
			return 1;

		pTmp = pTmp->pNext;
	}

	return 0;
}

void** SearchByAgeRange(int min, int max, int* pCount)
{
	*pCount = 0;
	USERDATA* pMin = NULL;
	USERDATA* pMax = NULL;
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (pTmp->age >= min)
		{
			pMin = pTmp;
			break;
		}
		pTmp = pTmp->pNext;
	}

	if (pMin != NULL)
		pTmp = pMin->pNext;
	else
		pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (pTmp->age <= max)
			pMax = pTmp;
		else if (pTmp->age > max)
			break;

		pTmp = pTmp->pNext;
	}

	if (pMin != NULL && pMax != NULL)
	{
		USERDATA* pTmp = pMin;
		int cnt = 1;
		while (pTmp != pMax)
		{
			++cnt;
			pTmp = pTmp->pNext;
		}

		*pCount = cnt;
		void** pNodePtrList = malloc(sizeof(void*) * cnt);

		pTmp = pMin;
		int i = 0;
		for (; pTmp != pMax; ++i)
		{
			pNodePtrList[i] = pTmp;
			pTmp = pTmp->pNext;
		}
		pNodePtrList[i] = pMax;

		return pNodePtrList;
	}

	return NULL;
}

void** MakeIndexAge(int* pCnt)
{
	*pCnt = 0;
	if (IsEmpty())
		return NULL;

	USERDATA** aList;
	aList = malloc(sizeof(USERDATA*) * GetListCount());
	memset(aList, 0, sizeof(USERDATA*) * GetListCount());
	*pCnt = GetListCount();

	USERDATA* pTmp = g_HeadNode.pNext;
	for (int i = 0; pTmp != &g_TailNode; ++i)
	{
		aList[i] = pTmp;
		pTmp = pTmp->pNext;
	}

	for (unsigned int i = 0; i < GetListCount() - 1; ++i)
	{
		for (unsigned int j = i + 1; j < GetListCount(); ++j)
		{
			if (aList[i]->age > aList[j]->age)
			{
				USERDATA* pTmp = aList[i];
				aList[i] = aList[j];
				aList[j] = pTmp;
			}
		}
	}

	return aList;
}

void** SearchByIndexAgeRange(int min, int max, unsigned int* pCount)
{
	*pCount = 0;
	unsigned int cntTotal = 0;
	USERDATA** aList = (USERDATA**)MakeIndexAge(&cntTotal);

	int idxMin = -1, idxMax = 0;
	unsigned int i = 0;
	for (i = 0; i < cntTotal; ++i)
	{
		if (aList[i]->age >= min && aList[i]->age <= max)
		{
			idxMin = i;
			idxMax = i;
			break;
		}
	}

	if (idxMin >= 0)
	{
		for (; i < cntTotal; ++i)
		{
			if (aList[i]->age <= max)
				idxMax = i;
			else if (aList[i]->age > max)
				break;
		}

		int length = idxMax - idxMin + 1;
		USERDATA** aSelected = malloc(sizeof(void*) * length);
		memcpy(aSelected, aList + idxMin, sizeof(void*) * length);

		free(aList);

		*pCount = length;
		return aSelected;
	}

	free(aList);
	return NULL;
}

void** MakeIndexName(int* pCnt)
{
	*pCnt = 0;
	if (IsEmpty())
		return NULL;

	USERDATA** aList;
	// 갯수만큼 메모리 할당하고..
	aList = malloc(sizeof(USERDATA*) * GetListCount());
	memset(aList, 0, sizeof(USERDATA*) * GetListCount());
	*pCnt = GetListCount();

	USERDATA* pTmp = g_HeadNode.pNext;
	for (int i = 0; pTmp != &g_TailNode; ++i)
	{
		aList[i] = pTmp;
		pTmp = pTmp->pNext;
	}
	// 버블 정렬
	for (unsigned int i = 0; i < GetListCount() - 1; ++i)
	{
		for (unsigned int j = i + 1; j < GetListCount(); ++j)
		{
			if (strcmp(aList[i]->name, aList[j]->name) > 0)
			{
				USERDATA* pTmp = aList[i];
				aList[i] = aList[j];
				aList[j] = pTmp;
			}
		}
	}

	return aList;
}

void UpdateIndexAll(void)
{
	// 기존에 있는거 지움
	if (g_idxListAge != NULL)
	{
		free(g_idxListAge);
		g_idxListAge = NULL;
	}

	if (g_idxListName != NULL)
	{
		free(g_idxListName);
		g_idxListName = NULL;
	}

	int cnt = 0;
	g_idxListAge = (USERDATA**)MakeIndexAge(&cnt);
	g_idxListName = (USERDATA**)MakeIndexName(&cnt);
}