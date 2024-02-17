#pragma once
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
USERDATA g_HeadNode;
USERDATA g_TailNode;

/*header���� �Լ� ���� ����*/
void AddNewNode(int age, const char* pszName, const char* pszPhone);
void InitList(void);
void ReleaseList(void);
USERDATA* Dequeue(void);
void Enqueue(USERDATA* pUser);
USERDATA* Pop();
void Push(USERDATA* pUser);
USERDATA* SearchByName(const char* pszName);
USERDATA* SearchToRemove(const char* pszName);
void RemoveNode(USERDATA* pRemove);