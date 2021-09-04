#include <assert.h>
#include <string.h>

#include "list.h"

void listInit(struct list *list, size_t element_size)
{
    assert(list != NULL);
    assert(element_size > 0);

    list->head = list->tail = NULL;
    list->elem_size = element_size;
}

void listDestroy(struct list *list)
{
    assert(list != NULL);

    // «listPopFront()» takes care of node removal
    while (listPopFront(list, NULL)) {
        /* nop */;
    }
}

size_t listSize(const struct list *list)
{
    assert(list != NULL);

    size_t counter = 0U;

    // for loop ftw
    for (const struct node *node = list->head; node != NULL; node = node->next)
        ++counter;

    return counter;
}

bool listIsEmpty(const struct list *list)
{
    assert(list != NULL);
    return list->head == NULL;
}

static
struct node *listNewNode(const struct list *list, const void *data)
{
    struct node *node = malloc(sizeof(struct node) + list->elem_size);

    if (node == NULL)
        return NULL;

    memcpy(node->data, data, list->elem_size);
    return node;
}

static
void listAttach(struct list *list, struct node *node, struct node *prev)
{
    node->prev = prev;

    if (prev != NULL) {
        // if previous node exists, insert «node» between «prev» and «prev->next»
        if (prev->next != NULL)
            prev->next->prev = node;

        node->next = prev->next;
        prev->next = node;
    } else {
        // otherwise add node before «list->head»
        if (list->head != NULL)
            list->head->prev = node;

        node->next = list->head;
    }

    // update «list->head» and «list->tail» accordingly
    if (node->prev == NULL)
        list->head = node;
    if (node->next == NULL)
        list->tail = node;
}

static
struct node *listDetach(struct list *list, struct node *node)
{
    // remove bindings between «node» and its siblings
    if (node->prev != NULL)
        node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;

    // update «list->head» and «list->tail» accordingly
    if (list->head == node)
        list->head = node->next;
    if (list->tail == node)
        list->tail = node->prev;

    return node;
}

bool listPushBack(struct list *list, const void *data)
{
    assert(list != NULL);
    assert(data != NULL);

    // get a new node
    struct node *node = listNewNode(list, data);

    if (node == NULL)
        return false;

    // attach the node after «list->tail»
    listAttach(list, node, list->tail);
    return true;
}

bool listPopBack(struct list *list, void *data)
{
    assert(list != NULL);

    if (listIsEmpty(list))
        return false;

    // detach «list->tail» node
    struct node *node = listDetach(list, list->tail);

    if (data != NULL)
        memcpy(data, node->data, list->elem_size);

    // the node is useless now
    free(node);
    return true;
}

bool listPushFront(struct list *list, const void *data)
{
    assert(list != NULL);
    assert(data != NULL);

    // this function works analogously to «listPush()»
    struct node *node = listNewNode(list, data);

    if (node == NULL)
        return false;

    // «prev» set to «NULL» means there is no previous node
    listAttach(list, node, NULL);
    return true;
}

bool listPopFront(struct list *list, void *data)
{
    assert(list != NULL);

    if (listIsEmpty(list))
        return false;

    // this function works analogously to «listPopBack()»
    struct node *node = listDetach(list, list->head);

    if (data != NULL)
        memcpy(data, node->data, list->elem_size);

    free(node);
    return true;
}
