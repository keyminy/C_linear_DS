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
}

int main(void) {
	InitDummyData();

	//�˻��ϱ�
	SearchByName("Hoon");
	SearchByName("Choi");
	SearchByName("Jang");
	SearchByName("Kim");

	//Print list
	//PrintList();

	ReleaseList();
	return 0;
}