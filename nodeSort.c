#include "nodeSort.h"
#include <stdio.h>



void SortListByName(void) {
	if (IsEmpty())
		return;
	// pTmp = 정렬이 진행될 데이터
	USERDATA* pTmp = g_HeadNode.pNext;
	//pSelected = 현재 정렬 중, 가장 작은 이름 가진 노드(minIdx)
	USERDATA* pSelected = NULL;
	// pCmp는 pTmp이후부터순회(j=i+1, pTmp와 비교할 용도)
	USERDATA* pCmp = NULL;
	while (pTmp != NULL && pTmp != g_TailNode.pPrev) {
		pSelected = pTmp; // minIdx
		pCmp = pTmp->pNext;
		// pCMp와 pSelected비교
		while (pCmp != NULL && pCmp != &g_TailNode) {
			if (strcmp(pSelected->name,pCmp->name) > 0)
				pSelected = pCmp; // update minIdx
			pCmp = pCmp->pNext;
		}
		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);
		pSelected = NULL;
		pTmp = pTmp->pNext;
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

void TestSortList02(void)
{
	puts("TestSortList02");
	AddNewNode(5, "Hoon", "010-1234-2222");
	AddNewNode(6, "Hong", "010-1234-1111");
	PrintList(0);
	SortListByName();
	PrintList(0);
	ReleaseList();
	puts("---------------------------------");
}

void TestSortList03(void)
{
	puts("TestSortList03");
	AddNewNode(6, "Hong01", "010-1234-1111");
	AddNewNode(5, "Hong", "010-1234-1111");
	PrintList(0);
	SortListByName();
	PrintList(0);
	ReleaseList();
	puts("---------------------------------");
}

void TestSortList04(void)
{
	puts("TestSortList04");
	AddNewNode(5, "Kim", "010-1234-1111");
	AddNewNode(6, "Hoon", "010-1234-2222");
	AddNewNode(7, "Choi", "010-1234-3333");
	AddNewNode(8, "Jang", "010-1234-4444");
	PrintList(0);
	SortListByName();
	PrintList(0);
	ReleaseList();
	puts("---------------------------------");
}
