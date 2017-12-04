#ifndef LISTNODE_H
#define LISTNODE_H

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

#endif // LISTNODE_H
