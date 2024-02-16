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

//Head Node가 필요하다
//USERDATA* g_pHeadNode = NULL;
/*더미 헤드를 갖는 2중 연결 리스트로 변환*/
USERDATA g_HeadNode = {0,"__Dummy Head__"};
USERDATA g_TailNode = {0,"__Dummy Tail__"};

void AddNewNode(int age,const char* pszName,const char* pszPhone) {
	//const 포인터 : 값을 읽기만하지, 쓰는것은 아니므로
	//추가
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	//pNewNode값 입력
	pNewNode->age = age;
	//pNewNode->name = pszName; //불가
	strcpy_s(pNewNode->name,sizeof(pNewNode->name),pszName);
	strcpy_s(pNewNode->phone,sizeof(pNewNode->phone),pszPhone);
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
	//pTmp값이 TailNode부터 시작
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

	/*삭제하기*/
	USERDATA* pPrev = SearchToRemove("Choi");
	if (pPrev != NULL) {
		//찾았으면 지우기
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
	InitList();
	TestStep01();
	TestStep02();
	TestStep03();
	return 0;
}