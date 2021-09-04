#define CUT

#ifndef DEBUG
#  define CUT_FORK_MODE
#endif

#include "cut.h"

#include "test_utils.h"

#include <stdio.h>

void terminate(const char *str)
{
    fprintf(stderr, "%s\n", str);
    abort();
}

void listCheckIntegrity(struct list *list)
{
    CHECK(list != NULL);

    // the head is NULL if and only if the tail is NULL
    CHECK(list->head == NULL || list->tail != NULL);
    CHECK(list->tail == NULL || list->head != NULL);

    // empty list is trivially correct
    if (list->head == NULL)
        return;

    // check head->prev and tail->next
#if defined(LLIST_ENABLE_TWO_LINKS)
    CHECK(list->head->prev == NULL);
#endif
    CHECK(list->tail->next == NULL);

    // the list may only contain one node
    if (list->head == list->tail)
        return;

    // the list now contains at least two nodes, Gotta test'em all!
    for (struct node *node = list->head; node != NULL; node = node->next) {
        // null values are not allowed
        CHECK(node->data != NULL);

        // identities
#if defined(LLIST_ENABLE_TWO_LINKS)
        if (node != list->head) {
            CHECK(node->prev != NULL);
            CHECK(node->prev->next == node);
        }
#endif

        if (node != list->tail) {
            CHECK(node->next != NULL);
#if defined(LLIST_ENABLE_TWO_LINKS)
            CHECK(node->next->prev == node);
#endif
        }
    }

    // ok, we are done
}

void listCheckContents(struct list *list, size_t size, int *data)
{
    struct node *node = list->head;

    if (size == 0U) {
        // the list should be empty
        CHECK(node == NULL);
        return;
    }

    for (size_t i = 0U; i < size; ++i) {
        CHECK(node != NULL);
        CHECK(node->data != NULL);

        // check i-th value
        int value = *(int*)(node->data);
        CHECK(value == data[i]);

        node = node->next;
    }

    // if this node is not NULL, there are more values
    // in the list, not cool
    CHECK(node == NULL);
}

void freeNodes(struct node *head)
{
    while (head != NULL) {
        struct node *next = head->next;

#if !defined(LLIST_ENABLE_FAM)
        free(head->data);
#endif

        free(head);
        head = next;
    }
}
