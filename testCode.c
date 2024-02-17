#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "list.h"
#include "ui.h"

void TestStackAndQueue(void) {
	USERDATA user = { 10,"Test01", };
	//Push(&user);
	Enqueue(&user);
	user.age = 11;
	strcpy_s(user.name, sizeof(user.name), "Test02");
	//Push(&user);
	Enqueue(&user);
	user.age = 12;
	strcpy_s(user.name, sizeof(user.name), "Test03");
	Enqueue(&user);
	//Push(&user);
	PrintList();

	for (int i = 0; i < 3; i++) {
		//USERDATA* pUser = Pop();
		USERDATA* pUser = Dequeue();
		printf("Pop : %d, %s\n", pUser->age, pUser->name);
		free(pUser);//pop한 노드 해체
	}
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

void InitDummyData(void) {
	//Input
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(13, "Jang", "010-3333-3333");
}