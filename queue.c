#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    assert(head != NULL && "Memory allocation failed");
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head) {}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    assert(head != NULL && "Memory allocation failed");
    element_t *node = malloc(sizeof(element_t));
    assert(node != NULL && "Memory allocation failed");
    node->value = strdup(s);
    assert(node->value == NULL && "node->value failed");
    node->list.next = head->next;
    node->list.prev = head;
    head->next->prev = &node->list;
    head->next = &node->list;

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{   
    assert(head != NULL && "Memory allocation failed");
    element_t *node = malloc(sizeof(element_t));
    assert(node != NULL && "Memory allocation failed");
    node->value = strdup(s);
    node->list.next = head;
    node->list.prev = head->prev;
    head->prev->next = &node->list;
    head->prev = &node->list;
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || list_empty(head)) {
        return NULL;
    }
    element_t *node = list_entry(head->next, element_t, list);
    list_del(head->next);
    if (sp != NULL) {
        strncpy(sp, node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || list_empty(head)) {
        return NULL;
    }
    element_t *node = list_entry(head->prev, element_t, list);
    list_del(head->prev);
    if (sp != NULL) {
        strncpy(sp, node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return node;}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{   
    if (head == NULL || list_empty(head)) {
        return 0;
    }
    int count = 0;
    struct list_head *temp = head->next;
    while (temp != head)
    {
        temp = temp->next;
        count++;
    }
    
    return count;
}

/* Delete the middle node in queue */
// https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/ 
bool q_delete_mid(struct list_head *head)
{
    if (head == NULL || list_empty(head)) {
        return false;
    }
    struct list_head *forward = head->next;
    struct list_head *back = head->prev;
    while (back != forward && back->prev != forward) {
        forward = forward->next;
        back = back->prev;
        back = back->prev;
    }
    list_del(forward);
    element_t *node = list_entry(forward, element_t, list);
    q_release_element(node);
    return true;
}

/* Delete all nodes that have duplicate string */
// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/  
bool q_delete_dup(struct list_head *head)
{
    if (head == NULL || list_empty(head)) {
        return false;
    }
    bool dup = false;
    element_t *temp, *next;
    list_for_each_entry_safe(temp, next, head, list) {
        if (temp->list.next != head && 
            strcmp(next->value, temp->value) == 0) {
                list_del(&temp->list);
                q_release_element(temp);
                dup = true;
        } else if (dup) {
            list_del(&temp->list);
            q_release_element(temp);
            dup = false;
        }
    }
    return true;

}

/* Swap every two adjacent nodes */
// https://leetcode.com/problems/swap-nodes-in-pairs/

void q_swap(struct list_head *head)
{
    if (head == NULL || list_empty(head)) {
        return;
    }
    struct list_head *cur = head->next;
    while (cur->next != head && cur != head) {
        struct list_head *temp = cur->next;
        list_move(cur, temp);
        cur = cur->next;
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {
    if (head == NULL || list_empty(head)) {
        return ;
    }
    struct list_head *forward = head->next;
    struct list_head *back = head->prev;
    while (forward != back) {
        struct list_head *temp = forward->next;
        list_del(forward);
        list_add(forward, back);
        list_del(back);
        list_add(back, temp);
        if (back->next == forward)
            break;
        temp = back->next;
        back = forward->prev;
        forward = temp;
    }
}

/* Reverse the nodes of the list k at a time */
// https://leetcode.com/problems/reverse-nodes-in-k-group/

void q_reverseK(struct list_head *head, int k)
{
    if (head == NULL || list_empty(head) || k < 2) {
        return;
    }
    int list_size = q_size(head);
    for (struct list_head *now = head->next; now != head && now->next != head; now = now->next) {
        struct list_head **cur = &now->next, *temp = now->prev;
        for (int i = 1; i < k; i++) {
            if (list_size >= k) {
                list_move(*cur, temp);
            }
        }
    }
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
