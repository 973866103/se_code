#include <stdio.h>
#include <stdlib.h>
#include "linktable.h"

int Help();
int Quit();

#define CMD_MAX_LEN 128
#define DESC_LEN 1024
#define CMD_NUM 10

typedef struct DataNode
{
    tLinkTableNode *pNext;
    char * cmd;
    char * desc;
    int (*handler)();
}tDataNode;

tLinkTable *head = NULL;

tDataNode *FindCmd(tLinkTable *head, char *cmd)
{
    tDataNode * pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
	if(strcmp(pNode->cmd,cmd) == 0)
	{
	    return pNode;
	}
	pNode = (tDataNode*)GetNextLinkTableNode(head, (tLinkTableNode*)pNode);
    }
    return NULL;
}

int ShowAllCmd(tLinkTable * head)
{
    tDataNode *pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
	printf("%s - %s\n", pNode->cmd, pNode->desc);
	pNode = (tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode*)pNode);
    }
    return 0;
}

int InitMenuData(tLinkTable **ppLinktable)
{
    *ppLinktable = CreateLinkTable();

    tDataNode *pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "help";
    pNode->desc = "This is help command.";
    pNode->handler = Help;
    AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "quit";
    pNode->desc = "quit the command line.";
    pNode->handler = Quit;
    AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);
    return 0;
}

/* menu program */

int main()
{
    /* cmd line begins */
    InitMenuData(&head);
    while(1)
    {
	char cmd[CMD_MAX_LEN];
	printf("Input a cmd number > ");
	scanf("%s",cmd);
	tDataNode *p = FindCmd((tLinkTable*)head, cmd);
	if(p == NULL)
	{
	    printf("This is a wrong cmd!\n");
	    continue;
	}
	printf("%s - %s\n", p->cmd, p->desc);
	if(p->handler != NULL)
	{
	    p->handler();
	}

    }
}

int Help()
{
    printf("Menu List:\n"); 
    ShowAllCmd((tLinkTable*)head);
    return 0;
}

int Quit()
{
    exit(0);
    return 0;
}
