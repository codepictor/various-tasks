// 472 Mikhalev Artem 19.09.2015

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

const int MAXSIZE = 100000; // max size of the queue

struct Node
{
	int childCount;
	struct Node** child;
};

struct ListElem
{
	struct Node* nodePtr;
	struct ListElem* next;
};

struct List
{
	int length;
	struct ListElem* firstElem;
	struct ListElem* lastElem;
};


void         AddElem           (struct List* listPtr, struct Node* nodePtr);
void         RemoveElem        (struct List* listPtr);
struct List* ConstructList     ();
void         CreateChild       (struct Node* node);
struct Node* GetTree           ();
void         CreateProcessTree (struct Node* node);



int main ()
{
	struct Node* root = GetTree ();

	CreateProcessTree (root);

	printf ("pid = %d ppid = %d\n", getpid (), getppid ());

	return 0;
}



void AddElem (struct List* listPtr, struct Node* nodePtr)
{
	assert (listPtr);
	assert (listPtr->length >= 0 && listPtr->length <= MAXSIZE);
	assert (nodePtr);

	if (listPtr->length == 0)
	{
		listPtr->firstElem = (struct ListElem*) calloc (1, sizeof (struct ListElem));
		assert (listPtr->firstElem);
		listPtr->lastElem = listPtr->firstElem;
		listPtr->firstElem->nodePtr = nodePtr;
	}
	else
	{
		listPtr->lastElem->next = (struct ListElem*) calloc (1, sizeof (struct ListElem));
		assert (listPtr->lastElem->next);
		listPtr->lastElem = listPtr->lastElem->next;
		listPtr->lastElem->nodePtr = nodePtr;
	}

	listPtr->length++;
}


void RemoveElem (struct List* listPtr)
{
	assert (listPtr);
	assert (listPtr->length > 0 && listPtr->length <= MAXSIZE);

	struct ListElem* killPtr = listPtr->firstElem;
	listPtr->firstElem = listPtr->firstElem->next;
	free (killPtr);
	killPtr = NULL;
	listPtr->length--;
}


struct List* ConstructList ()
{
	struct List* listPtr = (struct List*) calloc (1, sizeof (struct List));
	assert (listPtr);

	listPtr->firstElem = NULL;
	listPtr->lastElem = NULL;
	listPtr->length = 0;

	return listPtr;
}


void CreateChild (struct Node* node)
{
	assert (node);
	assert (node->childCount >= 0);

	node->child = (struct Node**) calloc (node->childCount, sizeof (struct Node*));
	assert (node->child);

	int i = 0;
	for (i = 0; i < node->childCount; i++)
	{
		(node->child)[i] = (struct Node*) calloc (1, sizeof (struct Node));
		assert ((node->child)[i]);
	}
}


struct Node* GetTree ()
{
	struct List* listPtr = ConstructList ();
	assert (listPtr);
	struct Node* root = (struct Node*) calloc (1, sizeof (struct Node));
	assert (root);
	root->childCount = 1;
	AddElem (listPtr, root);

	int i = 0;
	struct ListElem* topElem = NULL;
	while (listPtr->length > 0)
	{
		topElem = listPtr->firstElem;
		scanf ("%d", &topElem->nodePtr->childCount);
		CreateChild (topElem->nodePtr);
		for (i = 0; i < topElem->nodePtr->childCount; i++)
		{
			AddElem (listPtr, topElem->nodePtr->child[i]);
		}
		RemoveElem (listPtr);
	}

	assert (listPtr->length == 0);
	free (listPtr);
	listPtr = NULL;

	return root;
}


void CreateProcessTree (struct Node* node)
{
	assert (node);
	assert (node->childCount >= 0);

	int i = 0;
	int forkRes = 1;
	for (i = 0; i < node->childCount; i++)
	{
		if (forkRes > 0)
		{
			forkRes = fork ();
			int status = 0;
			wait (&status);
			if (forkRes == 0)
			{
				CreateProcessTree ((node->child)[i]);
			}
		}
	}
}




