/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (head == NULL || head->next == NULL || k == 0)
        return head;

    // Find length and tail
    int n = 1;
    struct ListNode* tail = head;

    while (tail->next != NULL) {
        tail = tail->next;
        n++;
    }

    // Avoid unnecessary rotations
    k = k % n;

    if (k == 0)
        return head;

    // Make the list circular
    tail->next = head;

    // Find the new tail
    int steps = n - k;
    struct ListNode* newTail = head;

    for (int i = 1; i < steps; i++)
        newTail = newTail->next;

    // New head is after new tail
    struct ListNode* newHead = newTail->next;

    // Break the circle
    newTail->next = NULL;

    return newHead;
}