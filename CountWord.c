// Protechsoft.c : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>

#define MIN_WORD_LENGTH 2
#define compare(x, y) (x>y?1:(x<y?-1:0))

typedef struct Node
{
	struct Node *next;
	char word[141];
	int count;
} Node;

Node *head = NULL;

int store(char[]);
int insert(char[], Node *);
int printList();
int freeMem();

int main()
{
	//Count the number of occurences of each word

	char tweet[142], word[141];
	//char delims[] = { ' ', '.'}; //TODO: Add custom delimiter support
	int i, length;

	//Get the word and remove the trailing new line
	printf("Enter the tweet: ");
	fgets(tweet, 142, stdin);
	for (i = 0; tweet[i] != '\n'; ++i);
	tweet[i] = '\0';
	length = i;

	//Parse the tweet, recognise words, check if they meet requirements, deal with them accordingly
	for (i = 0; i < length; ++i)
	{
		char current = tweet[i];
		//if current character is a letter. TODO: Add support for custom word beginnings
		if (((current >= 'A') && (current <= 'Z')) || ((current >= 'a') && (current <= 'z'))) 
		{
			int j = 0;
			for (; (i < length) && (tweet[i]!=' ' && tweet[i] != '.'  && tweet[i] != ','); ++i, ++j)	//delimiter support needed
			{
				word[j] = tweet[i];
			}
			//If word meets minimum length requirements
			if (j >= MIN_WORD_LENGTH)
			{
				word[j] = '\0';
				store(word);
			}
		}
	}

	printf("\nThe word list with frequency:\n");
	printList();	//TODO: implement this function
	freeMem();		//TODO: implement this function
	return 0;
}

int store(char word[])
{
	if (head == NULL)	//If the list is empty
	{
		insert(word, NULL);	//insert at the first position
		return 1;
	}
	Node *next = head;
	Node *current = NULL;
	while (next != NULL)
	{
		//compare current word to next word in the list
		int i;
		int result = -2;
		int tempResult = -2;	//flag to be used when the first non-alphabetical pair is encountered. refer to point 2c of readme
		
		for (i = 0; (next->word[i] != '\0') && (word[i] != '\0'); ++i)
		{
			result=-2;
			char c1 = word[i], c2 = next->word[i];
			if (c1 >= 'A' && c1 <= 'Z')
			{
				if (c2 >= 'A' && c2 <= 'Z')
				{
					result = compare(c1, c2);
				}
				else if (c2 >= 'a' && c2 <= 'z')
				{
					result = compare(c1 + 32, c2);	//converting to lower case and comparing
				}
				else
				{
					result = -1;
				}
			}
			else if (c1 >= 'a' && c1 <= 'z')
			{
				if (c2 >= 'a' && c2 <= 'z')
				{
					result = compare(c1, c2);
				}
				else if (c2 >= 'A' && c2 <= 'Z')
				{
					result = compare(c1, c2+32);	//converting to lower case and comparing
				}
				else
				{
					result = -1;
				}
			}
			else
			{
				tempResult = compare(c1, c2);
			}
			if (result)
			{
				break;
			}
		}
		
		//if the words are of unequal length (If one of them is finished but not both)
		if (!(word[i]=='\0') != !(next->word[i]=='\0'))
		{
			if (next->word[i] == '\0')	//if next word is shorter, it is lexicographically lesser than word
			{
				current = next;
				next = next->next;
				continue;
			}
			else	//if word is shorter than next word, it is lexicographically lesser than the next word
			{
				if (next == head)	//if it is the beginning of the list
				{
					return insert(word, NULL);
				}
				else
				{
					return insert(word, current);
				}
			}
		}
		if (result == -2)	//if nothing was compared
		{
			return 0;	//something is VERY wrong
		}

		//if current word matches exactly with next word. If there were symbols, then they match too
		if (result == 0 && (tempResult==-2 || tempResult==0) )
		{
			return next->count += 1;
		}

		//if the word is lexicographically lesser. If the letters match then the symbols don't
		else if (result==-1 || (result == 0 && tempResult == -1 ))
		{
			if (next == head)	//If it is the beginning of the list
			{
				return insert(word, NULL);
			}
			else
			{
				return insert(word, current);
			}
		}

		//if the word is lexicographically greater. If the letters match, then the symbols don't
		else if (result == 1 || (result == 0 && tempResult == 1))
		{
			current = next;
			next = next->next;
			continue;
		}
	}
	insert(word, current);	//if we reached the end of the list
	return 1;	
}

int insert(char data[], Node *current)
{
	int i;

	Node *tempNewNode = (Node *)malloc(sizeof(Node));
	tempNewNode->count = 1;
	for (i = 0; data[i] != '\0'; ++i)
	{
		tempNewNode->word[i] = data[i];
	}
	tempNewNode->word[i] = '\0';
	
	if (current)	//Insertion at any position except beginning
	{
		Node *tempNode = current->next;
		current->next = tempNewNode;
		tempNewNode->next = tempNode;
	}
	else  //Insertion at the beginning
	{
		tempNewNode->next = head;
		head = tempNewNode;
	}
	return 1;
}

int printList()
{
	if (head == NULL)
	{
		return 0;
	}
	Node *current = head;
	printf("\n\nThe words and their frequencies:\n");
	while (current != NULL)
	{
		printf("%s %d\n", current->word, current->count);
		current = current->next;
	}
	return 0;
}

int freeMem()
{
	if (head == NULL)
	{
		return 0;
	}
	Node *tempNode;
	while (head != NULL)
	{
		tempNode = head;
		head = head->next;
		free(tempNode);
	}
	return 0;
}
