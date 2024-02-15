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
USERDATA* g_pHeadNode = NULL;

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
	if (g_pHeadNode == NULL) {
		g_pHeadNode = pNewNode;
	}
	else {
		/* (M2)tail�ʿ� ���ο� Node�߰� */
		USERDATA* pTail = g_pHeadNode;
		//������ ����??
		while (pTail->pNext != NULL) {
			pTail = pTail->pNext;
		}
		//pNewNode�� �߰����ش�
		pTail-> pNext = pNewNode;
		/* (M1)Head�ڿ� ���ο� Node�� �߰�*/
		//pNewNode->pNext = g_pHeadNode;
		////header�� ���ο� Node�� update
		//g_pHeadNode = pNewNode;
	}
}

void ReleaseList(void) {
	USERDATA* pTmp = g_pHeadNode;
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
	g_pHeadNode = NULL; //���� Header�� NULL�̹Ƿ�.
}

void InitDummyData(void) {
	//Input
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(13, "Jang", "010-3333-3333");
}

//����ڿ��� name���� �˻��ϰ�, ã�� Node�� �ּҹ�ȯ
USERDATA* SearchByName(const char* pszName) {
	USERDATA* pTmp = g_pHeadNode;
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

USERDATA* SearchToRemove(USERDATA** ppPrev,const char* pszName) {
	//������ Node ���� Node�ּ�(ppPrev)�� �޾� �Լ������� pPrev���� ������ �־�
	USERDATA* pCurrent = g_pHeadNode;
	USERDATA* pPrev = NULL;
	while (pCurrent != NULL) {
		if (strcmp(pCurrent->name, pszName) == 0) {
			*ppPrev = pPrev;//��Node�� �����ͺ��� �������
			return pCurrent;
		}
		//pPrev : ������ ��� ���� Node
		pPrev = pCurrent;
		pCurrent = pCurrent->pNext;
	}
	//��ã���� NULL�����ϰ� ����
	return NULL;
}

void RemoveNode(USERDATA* pPrev) {
	//USERDATA* pRemove = pPrev.pNext�ϹǷ� �Ű����� ����
	USERDATA* pRemove = NULL;
	if (pPrev == NULL) {
		//�����尡 Head Node�ϰ�� pPrev�� NULL
		if (g_pHeadNode == NULL) {
			//��尡 �������� �ʴ� ���
			return;
		}
		else {
			//��尡 �����ϴ� ���
			pRemove = g_pHeadNode;
			g_pHeadNode = pRemove->pNext;
			printf("RemoveNode() : %s\n", pRemove->name);
			free(pRemove);
		}
		return;
	}
	//if�� Ż��, pPrev���� ���� = ������ Node�� Head�� �ƴ�
	pRemove = pPrev->pNext;//pRemove = ������ ���
	pPrev->pNext = pRemove->pNext;
	printf("RemoveNode() : %s\n", pRemove->name);
	free(pRemove);

}

void PrintList(void) {
	USERDATA* pTmp = g_pHeadNode;
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
	USERDATA* pPrev = NULL;
	if (SearchToRemove(&pPrev, "Choi") != NULL) {
		//ã������ �����
		RemoveNode(pPrev);
	}
	PrintList();
	ReleaseList();
	putchar('\n');
}

int main(void) {
	TestStep01();
	return 0;
}