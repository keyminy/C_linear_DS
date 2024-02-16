#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pPrev;
	struct USERDATA* pNext;
} USERDATA;

//Head Node�� �ʿ��ϴ�
//USERDATA* g_pHeadNode = NULL;
/*���� ��带 ���� 2�� ���� ����Ʈ�� ��ȯ*/
USERDATA g_HeadNode = {0,"__Dummy Head__"};
USERDATA g_TailNode = {0,"__Dummy Tail__"};

void AddNewNode(int age,const char* pszName,const char* pszPhone) {
	//const ������ : ���� �б⸸����, ���°��� �ƴϹǷ�
	//�߰�
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	//pNewNode�� �Է�
	pNewNode->age = age;
	//pNewNode->name = pszName; //�Ұ�
	strcpy_s(pNewNode->name,sizeof(pNewNode->name),pszName);
	strcpy_s(pNewNode->phone,sizeof(pNewNode->phone),pszPhone);
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

void InitDummyData(void) {
	//Input
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(13, "Jang", "010-3333-3333");
}

//����ڿ��� name���� �˻��ϰ�, ã�� Node�� �ּҹ�ȯ
USERDATA* SearchByName(const char* pszName) {
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != NULL) {
		if (strcmp(pTmp->name, pszName) == 0) {
			printf("\"%s\" : Found!!\n",pszName);
			return pTmp;
		}
		pTmp = pTmp->pNext;
	}
	printf("\"%s\" : Not Found!!\n",pszName);
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

void PrintList(void) {
	USERDATA* pTmp = &g_HeadNode;
	while (pTmp != NULL) {
		printf("[%p] %d\t%s\t%s [%p]\n"
			, pTmp
			, pTmp->age
			, pTmp->name
			, pTmp->phone
			, pTmp->pNext
		);
		pTmp = pTmp->pNext;
	}
	putchar('\n');
}

void PrintListReverse(void) {
	//pTmp���� TailNode���� ����
	USERDATA* pTmp = g_TailNode.pPrev;
	while (pTmp != NULL) {
		printf("[%p] %d\t%s\t%s [%p]\n"
			, pTmp
			, pTmp->age
			, pTmp->name
			, pTmp->phone
			, pTmp->pNext
		);
		pTmp = pTmp->pPrev;
	}
	putchar('\n');
}

void TestStep01(void) {
	puts("TestStep01()--------------------");
	AddNewNode(10, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(13, "Jang", "010-3333-3333");

	PrintList();

	/*�����ϱ�*/
	USERDATA* pPrev = SearchToRemove("Choi");
	if (pPrev != NULL) {
		//ã������ �����
		RemoveNode(pPrev);
	}
	//PrintList();
	PrintListReverse();
	ReleaseList();
	putchar('\n');
}

void TestStep02(void) {
	puts("TestStep02()--------------------");
	AddNewNode(10, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(13, "Jang", "010-3333-3333");

	PrintList();

	/*�����ϱ�*/
	USERDATA* pPrev = SearchToRemove("Hoon");
	if (pPrev != NULL) {
		//ã������ �����
		RemoveNode(pPrev);
	}
	PrintList();
	ReleaseList();
	putchar('\n');
}

void TestStep03(void) {
	puts("TestStep03()--------------------");
	AddNewNode(10, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(13, "Jang", "010-3333-3333");

	PrintList();

	/*�����ϱ�*/
	USERDATA* pPrev = SearchToRemove("Jang");
	if (pPrev != NULL) {
		//ã������ �����
		RemoveNode(pPrev);
	}
	PrintList();
	ReleaseList();
	putchar('\n');
}

int main(void) {
	InitList();
	TestStep01();
	TestStep02();
	TestStep03();
	return 0;
}