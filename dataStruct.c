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

//Head Node가 필요하다
//USERDATA* g_pHeadNode = NULL;
/*더미 헤드를 갖는 리스트로 변환*/
USERDATA g_HeadNode = {0,"__Dummy Node__"};

void AddNewNode(int age,const char* pszName,const char* pszPhone) {
	//const 포인터 : 값을 읽기만하지, 쓰는것은 아니므로
	//추가
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	//pNewNode값 입력
	pNewNode->age = age;
	//pNewNode->name = pszName; //불가
	strcpy_s(pNewNode->name,sizeof(pNewNode->name),pszName);
	strcpy_s(pNewNode->phone,sizeof(pNewNode->phone),pszPhone);
	pNewNode->pNext = NULL;

	/* (M2)tail쪽에 새로운 Node추가 */
	USERDATA* pTail = &g_HeadNode;
	//마지막 노드야??
	while (pTail->pNext != NULL) {
		pTail = pTail->pNext;
	}
	//pNewNode를 추가해준다
	pTail-> pNext = pNewNode;
	/* (M1)Head뒤에 새로운 Node를 추가(Stack방식)*/
	//pNewNode->pNext = g_pHeadNode;
	////header를 새로운 Node로 update
	//g_pHeadNode = pNewNode;
}

void ReleaseList(void) {
	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pDelete;//지워질 포인터노드
	//1.날려버리기전, pNext값을 백업해야한다.
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

	//2.백업을했으면, 백업한 대상 Node free
	g_HeadNode.pNext = NULL; //최초 Header는 NULL이므로.
}

void InitDummyData(void) {
	//Input
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(13, "Jang", "010-3333-3333");
}

//사용자에게 name으로 검색하고, 찾은 Node의 주소반환
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
	//못찾으면 NULL리턴하고 끝냄
	return NULL;
}

USERDATA* SearchToRemove(const char* pszName) {
	USERDATA* pPrev = &g_HeadNode; //dummy node의 주소
	while (pPrev->pNext != NULL) {
		if (strcmp(pPrev->pNext->name, pszName) == 0) {
			return pPrev;
		}
		pPrev = pPrev->pNext;
	}
	//못찾으면 NULL리턴하고 끝냄
	return NULL;
}

void RemoveNode(USERDATA* pPrev) {
	//USERDATA* pRemove = pPrev.pNext하므로 매개변수 생략
	USERDATA* pRemove = NULL;

	//if (pPrev == NULL)문 탈출, pPrev값이 존재 = 삭제할 Node가 Head가 아님
	pRemove = pPrev->pNext;//pRemove = 삭제될 노드
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

	/*삭제하기*/
	USERDATA* pPrev = SearchToRemove("Choi");
	if (pPrev != NULL) {
		//찾았으면 지우기
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

	/*삭제하기*/
	USERDATA* pPrev = SearchToRemove("Hoon");
	if (pPrev != NULL) {
		//찾았으면 지우기
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

	/*삭제하기*/
	USERDATA* pPrev = SearchToRemove("Jang");
	if (pPrev != NULL) {
		//찾았으면 지우기
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