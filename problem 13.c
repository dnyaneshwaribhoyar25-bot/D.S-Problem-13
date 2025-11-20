#include <stdio.h>
#include <stdlib.h>

struct DNode {
    int data;
    struct DNode *prev, *next;
};
struct DNode* createNode(int data) {
    struct DNode *n = (struct DNode*)malloc(sizeof(struct DNode));
    n->data = data;
    n->prev = n->next = NULL;
    return n;
}
void insertEnd(struct DNode **head, int data) {
    struct DNode *newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct DNode *temp = *head;
    while (temp->next)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}
void insertBegin(struct DNode **head, int data) {
    struct DNode *newNode = createNode(data);

    newNode->next = *head;
    if (*head)
        (*head)->prev = newNode;

    *head = newNode;
}
void deleteValue(struct DNode **head, int value) {
    struct DNode *temp = *head;

    while (temp && temp->data != value)
        temp = temp->next;

    if (!temp) {
        printf("Value not found!\n");
        return;
    }

    if (temp->prev)
        temp->prev->next = temp->next;
    else
        *head = temp->next;

    if (temp->next)
        temp->next->prev = temp->prev;

    free(temp);
}
void reverseDLL(struct DNode **head) {
    struct DNode *current = *head, *temp = NULL;

    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp)
        *head = temp->prev;
}
struct DNode* mergeDLL(struct DNode *h1, struct DNode *h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    struct DNode *temp = h1;
    while (temp->next)
        temp = temp->next;

    temp->next = h2;
    h2->prev = temp;

    return h1;
}
void findMiddle(struct DNode *head) {
    struct DNode *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (slow)
        printf("Middle element: %d\n", slow->data);
}
void sortDLL(struct DNode **head) {
    if (*head == NULL) return;

    struct DNode *i, *j;
    for (i = *head; i->next; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (i->data > j->data) {
                int t = i->data;
                i->data = j->data;
                j->data = t;
            }
        }
    }
}
int detectLoop(struct DNode *head) {
    struct DNode *slow = head, *fast = head;

    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return 1;
    }
    return 0;
}

/* Sum of all nodes */
int sumDLL(struct DNode *head) {
    int sum = 0;
    while (head) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}
void printOddEven(struct DNode *head) {
    struct DNode *temp = head;

    printf("Odd elements: ");
    while (temp) {
        if (temp->data % 2 != 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\nEven elements: ");
    temp = head;
    while (temp) {
        if (temp->data % 2 == 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void printDLL(struct DNode *head) {
    printf("DLL: ");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct DNode *dll1 = NULL, *dll2 = NULL;

    insertEnd(&dll1, 10);
    insertEnd(&dll1, 30);
    insertBegin(&dll1, 5);
    insertEnd(&dll1, 20);

    printf("Original DLL:\n");
    printDLL(dll1);

    deleteValue(&dll1, 30);
    printf("\nAfter deletion:\n");
    printDLL(dll1);

    reverseDLL(&dll1);
    printf("\nReversed DLL:\n");
    printDLL(dll1);

    printf("\n");
    findMiddle(dll1);

    printf("Sum of DLL1: %d\n", sumDLL(dll1));

    insertEnd(&dll2, 7);
    insertEnd(&dll2, 2);
    insertEnd(&dll2, 9);

    dll1 = mergeDLL(dll1, dll2);

    printf("\nMerged DLL:\n");
    printDLL(dll1);

    sortDLL(&dll1);
    printf("\nSorted DLL:\n");
    printDLL(dll1);

    printf("\nOdd & Even values:\n");
    printOddEven(dll1);

    printf("\nLoop present? %s\n", detectLoop(dll1) ? "YES" : "NO");

    return 0;
}

