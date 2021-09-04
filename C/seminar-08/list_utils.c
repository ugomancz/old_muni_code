#include <assert.h>
#include <string.h>

#include "list.h"
#include "list_utils.h"

//-----------------------------------------------------------------------------
//  Helpers
//-----------------------------------------------------------------------------

// returns the node on a given index
static
struct node *listGetNode(const struct list *list, size_t index)
{
    struct node *node = list->head;
    while (index > 0U && node != NULL) {
        --index;
        node = node->next;
    }

    // either NULL or valid node if we reached 0
    return node;
}

// swaps values between two nodes
static
void swapNodeData(const struct list *list, struct node *a, struct node *b)
{
    assert(a != NULL);
    assert(b != NULL);

    char tmp;
    for (unsigned byte = 0; byte < list->elem_size; ++byte) {
        tmp = a->data[byte];
        a->data[byte] = b->data[byte];
        b->data[byte] = tmp;
    }
}

//-----------------------------------------------------------------------------
//  Implementation
//-----------------------------------------------------------------------------

bool listAny(const struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    bool any = false; // there is no element in an empty set that satisfies p
    // we can end as soon as we find a node that satisfies p
    for (struct node *nd = list->head; !any && nd != NULL; nd = nd->next)
        any = p(nd->data);

    return any;
}

bool listAll(const struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    bool all = true; // all elements of empty set satisfy p
    // we can end as soon as we find a node that does NOT satisfy p
    for (struct node *nd = list->head; all && nd != NULL; nd = nd->next)
        all = p(nd->data);

    return all;
}

bool listInsert(struct list *list, size_t index, void *data)
{
    assert(list != NULL);

    if (data == NULL)
        return false;

    // we have a function for the first element
    if (index == 0U)
        return listPushFront(list, data);

    // node that will go immediately before the new
    struct node *before = listGetNode(list, index - 1);

    // check that this node exists, otherwise the index is invalid
    if (before == NULL)
        return false;

    // we have a function for the last element
    if (before == list->tail)
        return listPushBack(list, data);

    // we now know that this node will be neither head nor tail
    // so we just insert node between 'before' and 'before->next'
    // neither of which are NULL
    struct node *node = malloc(sizeof(struct node) + list->elem_size);

    if (node == NULL)
        return false;

    memcpy(node->data, data, list->elem_size);

    node->next = before->next;
    node->prev = before;

    // entangle the node to the list
    if (before->next != NULL)
        before->next->prev = node;

    before->next = node;
    return true;
}

const void *listGet(const struct list *list, size_t index)
{
    assert(list != NULL);

    struct node *node = listGetNode(list, index);
    return node != NULL ? node->data : NULL;
}

int listGetIndex(const struct list *list, const void *data)
{
    assert(list != NULL);

    if (data == NULL)
        return -1;

    int index = 0;

    for (struct node *nd = list->head; nd != NULL; nd = nd->next, ++index) {
        if (memcmp(nd->data, data, list->elem_size) == 0)
            return index;
    }

    return -1;
}

bool listRemove(struct list *list, size_t index, void *data)
{
    assert(list != NULL);

    struct node *node = listGetNode(list, index);

    if (node == NULL)
        return NULL;

    if (data != NULL)
        memcpy(data, node->data, list->elem_size);

    // entangle list nodes
    if (node->prev != NULL)
        node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;

    // recover head and tail if necessary
    if (list->head == node)
        list->head = node->next;
    if (list->tail == node)
        list->tail = node->prev;

    // the node is useless now
    free(node);
    return data;
}

const void* listFindFirst(const struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    for (struct node *node = list->head; node != NULL; node = node->next) {
        if (p(node->data))
            return node->data;
    }

    return NULL;
}

const void* listFindLast(const struct list *list, predicate p)
{
    assert(list != NULL);
    assert(p != NULL);

    for (struct node *node = list->tail; node != NULL; node = node->prev) {
        if (p(node->data))
            return node->data;
    }

    return NULL;
}

void listForEach(struct list *list, action f)
{
    assert(list != NULL);
    assert(f != NULL);

    for (struct node *node = list->head; node != NULL; node = node->next)
        f(node->data);
}

void listForEachReverse(struct list *list, action f)
{
    assert(list != NULL);
    assert(f != NULL);

    for (struct node *node = list->tail; node != NULL; node = node->prev)
        f(node->data);
}

void listSort(struct list *list, comparator cmp)
{
    assert(list != NULL);
    assert(cmp != NULL);

    // this implementation uses improved bubblesort that counts swaps
    // in each iteration
    for (struct node *right = list->tail; right != NULL; right = right->prev) {
        unsigned swaps = 0U;

        for (struct node *swp = list->head; swp != right; swp = swp->next) {
            if (cmp(swp->data, swp->next->data) > 0) {
                swapNodeData(list, swp, swp->next);
                ++swaps;
            }
        }

        // if there were no swaps, the list is sorted and we may end
        if (swaps == 0U)
            return;
    }
}
