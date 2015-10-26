#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node
{
    int val;
    struct node *next;
};

struct node *head = NULL;
struct node *curr = NULL;

struct node* create_list(int val)
{
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->val = val;
    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}

struct node* add(int val){
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->val = val;
    ptr->next = NULL;

    curr->next = ptr;
    curr = ptr;
    return ptr;
}




void deleteHead(){
    struct node *del = NULL;
    del = head;
    head = del->next;
    free(del);
    del = NULL;
    return;
}

int firstVal(){
	return head->val;
}


