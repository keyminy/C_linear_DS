#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

USERDATA g_HeadNode = { 0,"__Dummy Head__" };
USERDATA g_TailNode = { 0,"__Dummy Tail__" };

USERDATA** g_idxListAge = NULL;
USERDATA** g_idxListName = NULL;

void AddNewNode(int age, const char* pszName, const char* pszPhone) {
	//const 포인터 : 값을 읽기만하지, 쓰는것은 아니므로
	//추가
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	//pNewNode값 입력
	pNewNode->age = age;
	//pNewNode->name = pszName; //불가
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	/*Dummy Tail앞에 넣으면 뒤에 추가하는 구조로 이용할 수 있음*/
	USERDATA* pPrevNode = g_TailNode.pPrev; //dummy head
	//1,2과정
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = &g_TailNode;
	//3,4과정
	pPrevNode->pNext = pNewNode;
	g_TailNode.pPrev = pNewNode;
}

void InitList(void) {
	//HEAD와 TAIL의 prev,next셋팅
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
}


void ReleaseList(void) {
	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pDelete;//지워질 포인터노드
	//1.날려버리기전, pNext값을 백업해야한다.
	while (pTmp != NULL && pTmp != &g_TailNode) {
		//dummy head와 dummy tail은 동적할당한 것이 아니다.
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		printf("Deleted!! [%p] %d\t%s\t%s [%p]\n"
			, pDelete
			, pDelete->age
			, pDelete->name
			, pDelete->phone
			, pDelete->pNext
		);
		free(pDelete);
	}
	InitList();
}


void Push(USERDATA* pUser) {
	//추가
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	//매개변수로 넘어오는 pUser값을 memcpy하기
	memcpy(pNewNode, pUser, sizeof(USERDATA));
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	//HEAD노드쪽에서만 데이터 추가
	USERDATA* pNextNode = g_HeadNode.pNext;
	pNewNode->pPrev = &g_HeadNode;
	pNewNode->pNext = pNextNode;

	pNextNode->pPrev = pNewNode;
	g_HeadNode.pNext = pNewNode;
}

int IsEmpty(void) {
	if (g_HeadNode.pNext == &g_TailNode) {
		//데이터가 하나도 없음
		return 1;
	}
	return 0;
}

USERDATA* Pop() {
	if (IsEmpty()) {
		puts("Error: Stack Underflow.");
		return NULL;
	}
	//HEAD쪽에서만 remove하면됨
	USERDATA* pPop = g_HeadNode.pNext; //반환할 노드(맨위에꺼)
	//pop되는 부분의 교통정리
	g_HeadNode.pNext = pPop->pNext;
	pPop->pNext->pPrev = pPop->pPrev;
	return pPop;
}

/* Queue는 이미 구현이 되어 있따.. */
USERDATA* Dequeue(void) {
	return Pop();
}

void Enqueue(USERDATA* pUser) {
	AddNewNode(pUser->age, pUser->name, pUser->phone);
}


//사용자에게 name으로 검색하고, 찾은 Node의 주소반환
USERDATA* SearchByName(const char* pszName) {
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != NULL) {
		if (strcmp(pTmp->name, pszName) == 0) {
			printf("\"%s\" : Found!!\n", pszName);
			return pTmp;
		}
		pTmp = pTmp->pNext;
	}
	printf("\"%s\" : Not Found!!\n", pszName);
	//못찾으면 NULL리턴하고 끝냄
	return NULL;
}

USERDATA* SearchToRemove(const char* pszName) {
	USERDATA* pRemove = g_HeadNode.pNext; //dummy node 다음 주소
	while (pRemove != NULL) {
		if (strcmp(pRemove->name, pszName) == 0) {
			printf("\"%s\" : Remove Found!!\n", pszName);
			return pRemove;
		}
		pRemove = pRemove->pNext;
	}
	printf("\"%s\" : Remove Not Found!!\n", pszName);
	//못찾으면 NULL리턴하고 끝냄
	return NULL;
}

void RemoveNode(USERDATA* pRemove) {
	USERDATA* pPrev = pRemove->pPrev;
	USERDATA* pNext = pRemove->pNext;

	pPrev->pNext = pRemove->pNext;
	pNext->pPrev = pRemove->pPrev;

	printf("RemoveNode() : %s\n", pRemove->name);
	free(pRemove);
}


void UpdateIndexAll(void)
{

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

int LoadListFromFile(void)
{
	ReleaseList();
	FILE* fp = NULL;
	fopen_s(&fp, "listData.dat", "rb");
	if (fp == NULL)
		return 0;

	USERDATA user = { 0 };
	while (fread(&user, sizeof(USERDATA), 1, fp) > 0)
	{
		AddNewNode(user.age, user.name, user.phone, 0);
		memset(&user, 0, sizeof(USERDATA));
	}

	//data를 다 loading후 index재계산하여 정렬
	UpdateIndexAll();

	fclose(fp);
	return 1;
}

int SaveListToFile(void)
{
	FILE* fp = NULL;
	fopen_s(&fp, "listData.dat", "wb");
	if (fp == NULL)
		return 0;

	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != NULL && pTmp != &g_TailNode)
	{
		//list를 통채로 파일에 저장한다.
		fwrite(pTmp, sizeof(USERDATA), 1, fp);
		pTmp = pTmp->pNext;
	}

	fclose(fp);
	return 1;
}