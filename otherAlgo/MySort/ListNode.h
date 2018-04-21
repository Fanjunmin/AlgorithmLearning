#ifndef LISTNODE_H
#define LISTNODE_H
#include <stack>
#include <vector>
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
/*
//��������
unsigned int ListNodeLength(ListNode *head){
    unsigned int nodeLength = 0;
    ListNode *temp = head;
    while(temp != NULL){
        ++nodeLength;
        temp = temp->next;
    }
    return nodeLength;
}

//β��ͷ��ӡ������
void PrintListNode(ListNode *head){
    //�ݹ�
    if(head == NULL)
        return;
    PrintListNode(head->next);
    std::cout << head->val << std::ends;
}
void PrintListNode2(ListNode *head){
    //����ջ
    stack<ListNode *> ln;
    while(head != NULL){
        ln.push(head);
        head = head->next;
    }
    while(!ln.empty()){
        ListNode *temp = ln.top();
        std::cout << temp->val << std::ends;
        ln.pop();
    }
}
//������ת
ListNode *reverseListNode(ListNode *head){
    if(head == NULL || head->next == NULL)
        return head;
    ListNode *pHead = head;   //��ת���������ͷ
    ListNode *pNext = head->next;
    head->next = NULL;
    while(pNext != NULL){
        pHead->next = pHead;
    }
}

//���ҵ������еĵ�����K�����
ListNode *getKNode(ListNode *head, unsigned int k){
    if(k == 0 || head == NULL)
        return head;
    ListNode *temp = head;
    while(k > 1 && temp != NULL){
        temp = temp->next;
        --k;
    }
}

//��������һ�����м�ڵ�
void findMid(ListNode *head, ListNode *mid){
    ListNode *temp = head;
    mid = temp;
    while(head->next != NULL && head->next->next != NULL){
        head = head->next->next;
        temp = temp->next;
        mid = temp;
    }
}
*/
#endif // LISTNODE_H
