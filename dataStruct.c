#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
} USERDATA;

//Head Node�� �ʿ��ϴ�
//USERDATA* g_pHeadNode = NULL;
/*���� ��带 ���� ����Ʈ�� ��ȯ*/
USERDATA g_HeadNode = {0,"__Dummy Node__"};

void AddNewNode(int age,const char* pszName,const char* pszPhone) {
	//const ������ : ���� �б⸸����, ���°��� �ƴϹǷ�
	//�߰�
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	//pNewNode�� �Է�
	pNewNode->age = age;
	//pNewNode->name = pszName; //�Ұ�
	strcpy_s(pNewNode->name,sizeof(pNewNode->name),pszName);
	strcpy_s(pNewNode->phone,sizeof(pNewNode->phone),pszPhone);
	pNewNode->pNext = NULL;

	/* (M2)tail�ʿ� ���ο� Node�߰� */
	USERDATA* pTail = &g_HeadNode;
	//������ ����??
	while (pTail->pNext != NULL) {
		pTail = pTail->pNext;
	}
	//pNewNode�� �߰����ش�
	pTail-> pNext = pNewNode;
	/* (M1)Head�ڿ� ���ο� Node�� �߰�(Stack���)*/
	//pNewNode->pNext = g_pHeadNode;
	////header�� ���ο� Node�� update
	//g_pHeadNode = pNewNode;
}

void ReleaseList(void) {
	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pDelete;//������ �����ͳ��
	//1.������������, pNext���� ����ؾ��Ѵ�.
	while (pTmp != NULL) {
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

	//2.�����������, ����� ��� Node free
	g_HeadNode.pNext = NULL; //���� Header�� NULL�̹Ƿ�.
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
	USERDATA* pPrev = &g_HeadNode; //dummy node�� �ּ�
	while (pPrev->pNext != NULL) {
		if (strcmp(pPrev->pNext->name, pszName) == 0) {
			return pPrev;
		}
		pPrev = pPrev->pNext;
	}
	//��ã���� NULL�����ϰ� ����
	return NULL;
}

void RemoveNode(USERDATA* pPrev) {
	//USERDATA* pRemove = pPrev.pNext�ϹǷ� �Ű����� ����
	USERDATA* pRemove = NULL;

	//if (pPrev == NULL)�� Ż��, pPrev���� ���� = ������ Node�� Head�� �ƴ�
	pRemove = pPrev->pNext;//pRemove = ������ ���
	pPrev->pNext = pRemove->pNext;
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
	PrintList();
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
	TestStep01();
	TestStep02();
	TestStep03();
	return 0;
}