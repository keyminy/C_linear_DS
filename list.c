#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

USERDATA g_HeadNode = { 0,"__Dummy Head__" };
USERDATA g_TailNode = { 0,"__Dummy Tail__" };

USERDATA** g_idxListAge = NULL;
USERDATA** g_idxListName = NULL;

void AddNewNode(int age, const char* pszName, const char* pszPhone) {
	//const ������ : ���� �б⸸����, ���°��� �ƴϹǷ�
	//�߰�
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	//pNewNode�� �Է�
	pNewNode->age = age;
	//pNewNode->name = pszName; //�Ұ�
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	/*Dummy Tail�տ� ������ �ڿ� �߰��ϴ� ������ �̿��� �� ����*/
	USERDATA* pPrevNode = g_TailNode.pPrev; //dummy head
	//1,2����
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = &g_TailNode;
	//3,4����
	pPrevNode->pNext = pNewNode;
	g_TailNode.pPrev = pNewNode;
}

void InitList(void) {
	//HEAD�� TAIL�� prev,next����
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
}


void ReleaseList(void) {
	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pDelete;//������ �����ͳ��
	//1.������������, pNext���� ����ؾ��Ѵ�.
	while (pTmp != NULL && pTmp != &g_TailNode) {
		//dummy head�� dummy tail�� �����Ҵ��� ���� �ƴϴ�.
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
	//�߰�
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	//�Ű������� �Ѿ���� pUser���� memcpy�ϱ�
	memcpy(pNewNode, pUser, sizeof(USERDATA));
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	//HEAD����ʿ����� ������ �߰�
	USERDATA* pNextNode = g_HeadNode.pNext;
	pNewNode->pPrev = &g_HeadNode;
	pNewNode->pNext = pNextNode;

	pNextNode->pPrev = pNewNode;
	g_HeadNode.pNext = pNewNode;
}

int IsEmpty(void) {
	if (g_HeadNode.pNext == &g_TailNode) {
		//�����Ͱ� �ϳ��� ����
		return 1;
	}
	return 0;
}

USERDATA* Pop() {
	if (IsEmpty()) {
		puts("Error: Stack Underflow.");
		return NULL;
	}
	//HEAD�ʿ����� remove�ϸ��
	USERDATA* pPop = g_HeadNode.pNext; //��ȯ�� ���(��������)
	//pop�Ǵ� �κ��� ��������
	g_HeadNode.pNext = pPop->pNext;
	pPop->pNext->pPrev = pPop->pPrev;
	return pPop;
}

/* Queue�� �̹� ������ �Ǿ� �ֵ�.. */
USERDATA* Dequeue(void) {
	return Pop();
}

void Enqueue(USERDATA* pUser) {
	AddNewNode(pUser->age, pUser->name, pUser->phone);
}


//����ڿ��� name���� �˻��ϰ�, ã�� Node�� �ּҹ�ȯ
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
	//��ã���� NULL�����ϰ� ����
	return NULL;
}

USERDATA* SearchToRemove(const char* pszName) {
	USERDATA* pRemove = g_HeadNode.pNext; //dummy node ���� �ּ�
	while (pRemove != NULL) {
		if (strcmp(pRemove->name, pszName) == 0) {
			printf("\"%s\" : Remove Found!!\n", pszName);
			return pRemove;
		}
		pRemove = pRemove->pNext;
	}
	printf("\"%s\" : Remove Not Found!!\n", pszName);
	//��ã���� NULL�����ϰ� ����
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

	//data�� �� loading�� index�����Ͽ� ����
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
		//list�� ��ä�� ���Ͽ� �����Ѵ�.
		fwrite(pTmp, sizeof(USERDATA), 1, fp);
		pTmp = pTmp->pNext;
	}

	fclose(fp);
	return 1;
}