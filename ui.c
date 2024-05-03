#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "list.h"
#include "ui.h"

void EventLoopRun(void) {
	MY_MENU menu = 0;

	while ((menu = PrintMenu()) != 0) {
		switch (menu) {
		case NEW:
			AddNewNode(99, "KaKa", "010-2222-2222");
			break;
		case SEARCH:
			Search();
			break;
		case PRINT:
			PrintList();
			break;
		case REMOVE:
			break;
		default:
			break;
		}
	}
	puts("Bye~!");
}


MY_MENU PrintMenu(void) {
	MY_MENU input = 0;
	system("cls");//consoleȭ�� �ʱ�ȭ
	printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[0]Exit\n");
	scanf_s("%d%*c", &input);
	return input;
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
	puts("[End of list]");
	_getch(); //�Է��̵Ǹ� �ƹ�Ű�� ������ �������� �Ѿ����
}

void PrintListReverse(void) {
	//pTmp���� TailNode���� ����
	USERDATA* pTmp = &g_TailNode;
	printf("=======ReversePrint!!==========\n");
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

void Search(void) {
	//����ڰ� �̸� �Է��� �Է� UI�� �������
	char name[32] = { 0 };
	gets_s(name,sizeof(name));

	//�Է¹��� name���� �˻�
	USERDATA* pResult = SearchByName(name);
	if (pResult != NULL) {
		printf("%d, %s, %s\n"
			, pResult->age
			, pResult->name
			, pResult->phone);
	}
	else {
		puts("Not Found!");
	}
	_getch();
}


void EditUserData(USERDATA* pUser)
{
	printf("New phone number: ");
	char szBuffer[32] = { 0 };
	gets_s(szBuffer, sizeof(szBuffer));
	if (strlen(szBuffer) > 0)
	{
		// ������ ������ memory�󿡼� overwrite
		memcpy(pUser->phone, szBuffer, sizeof(pUser->phone));

		printf("Do you want to save now?(y/n)");
		char ch = _getch();
		if (ch == 'y' || ch == 'Y')
			SaveListToFile();
	}
}
USERDATA* SearchListByName(USERDATA* pUser, char* pszName)
{
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (strcmp(pTmp->name, pszName) == 0)
		{
			memcpy(pUser, pTmp, sizeof(USERDATA));
			return pTmp;
		}

		pTmp = pTmp->pNext;
	}

	return NULL;
}

void _SearchByName(void)
{
	char name[32] = { 0 };

	printf("name: ");
	gets_s(name, sizeof(name));

	USERDATA user = { 0 };
	USERDATA* pUser = SearchListByName(&user, name);
	if (pUser != NULL)
	{
		printf("Found: %d, %s, %s\n",
			user.age, user.name, user.phone);

		printf("Do you want to edit? (y/n)\n");
		char ch = _getch();
		if (ch == 'y' || ch == 'Y')
			EditUserData(pUser);
	}
	else
		puts("Not found");

	_getch();
}