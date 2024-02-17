#pragma once
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
USERDATA g_HeadNode;
USERDATA g_TailNode;

/*header에는 함수 원형 선언*/
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