#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singleList.h"


USERDATA g_HeadNode = { 0, "_DummyHead_" };
USERDATA g_TailNode = { 0, "_DummyTail_" };


void InitList(void)
{
	ReleaseList();
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
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
	USERDATA* pMin = NULL; // 최솟값 가리킬 포인터
	USERDATA* pMax = NULL; // 최댓값 가리킬 포인터
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (pTmp->age >= min)
		{ // 찾으면 while탈출
			// min,max = 6,6으로 같게 입력할 수도 있으므로
			// pMin,pMax = pTmp로 pMax에도 대입해준 것.
			pMin = pTmp;
			pMax = pTmp;
			break;
		}
		// 내가 입력한 최솟값 min 나올때까지 pTmp움직여
		pTmp = pTmp->pNext;
	} 

	if (pMin != NULL)
		pTmp = pMin->pNext;
	else
		pTmp = g_HeadNode.pNext; // 다시 처음값으로 돌아간다.(head의 next,KIM)
	while (pTmp != &g_TailNode)
	{
		if (pTmp->age >= min && pTmp->age <= max)
			// min : 9 ,max : 2같은 이상한것 방지
			pMax = pTmp;
		else if (pTmp->age > max)
			// 값 찾으면 break(pTmp->age=7 > max=6)이면 break
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
		// 여기서, pTmp = pMax
		*pCount = cnt;
		void** pNodePtrList = malloc(sizeof(void*) * cnt);

		pTmp = pMin;
		int i = 0;
		for (; pTmp != pMax; ++i)
		{
			pNodePtrList[i] = pTmp;
			pTmp = pTmp->pNext;
		}
		pNodePtrList[i] = pMax; // pMax = pTmp

		return pNodePtrList;
	}

	return NULL;
}
