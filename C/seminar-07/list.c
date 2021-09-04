#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

//-----------------------------------------------------------------------------
//  Convenience macros
//-----------------------------------------------------------------------------

// This is a common way to say that some parameter is not used.
#define UNUSED(VARIABLE)                                                    \
    ((void) (VARIABLE))

// This function prints an error message to standard error output
// that the function called is not implemented and returns some default value.
#ifdef DEBUG
#   define EXIT_TEST(VALUE)                                                 \
        return VALUE
#else
#   define EXIT_TEST(VALUE)                                                 \
        abort()
#endif

// If a macro consists of more than one statement, there must be some
// way to hold these statements together, otherwise a construct like this
//
//      if (CONDITION)
//          MACRO(...);
//
// would wreak havoc in the code. To make things worse, programmers naturally
// add ';' after the statements in C, so the macro should expand to something
// that allows a semicolon afterwards.
//
// A reasonable candidate is therefore do { ... } while (0), since it
// contains a block, executes exactly once and is friendly to following
// semicolon.

#define NOT_IMPLEMENTED(VALUE)                                              \
    do {                                                                    \
        fprintf(stderr, "Unimplemented function '%s' called.\n", __func__); \
        EXIT_TEST(VALUE);                                                   \
    } while (0)

//-----------------------------------------------------------------------------
//  Static functions
//-----------------------------------------------------------------------------

/*
 * Feel free to add custom functions here. However, to make them invisible
 * to other translation units (basically ‹.c› files) you should use «static»
 * keyword like this:
 *
 *      static void listHelper(struct list *list)
 *      {
 *          ...
 *      }
 */

//-----------------------------------------------------------------------------
//  Task 1: List initialization
//-----------------------------------------------------------------------------

void listInit(struct list *list, size_t elem_size)
{
    // you may add checks like this to the following functions as well
    assert(list != NULL);
    assert(elem_size > 0);

    // You might think that previous checks could be written as
    //
    //      assert(list != NULL && elem_size > 0);
    //
    // However, if another programmer passed an invalid value, they would
    // get an unhelpful error like:
    //
    //      program: list.c: Assertion `list != NULL && elem_size > 0' failed
    //
    // So better keep the assertions separate.

    // TODO: remove the following lines and implement the function
    list->head = NULL;
    list->tail = NULL;
    list->elem_size = elem_size;
}

//-----------------------------------------------------------------------------
//  Task 2: Adding elements to the end of the list
//-----------------------------------------------------------------------------

bool listPushBack(struct list *list, const void *data)
{
    assert(list != NULL);
    assert(data != NULL);
    struct node* newNode = malloc(sizeof (struct node));
    newNode->next = NULL;
    newNode->data = malloc(list->elem_size);
    if (newNode->data == NULL) {
        fprintf(stderr, "Couldn't allocate memory\n");
        return false;
    }
    memcpy(newNode->data, data, list->elem_size);
    if (list->tail == NULL && list->head == NULL) { // if list is empty
        list->tail = newNode;
        list->head = newNode;
        return true;
    }
    list->tail->next = newNode;
    list->tail = newNode;
    return true;
}

//-----------------------------------------------------------------------------
//  Task 3: Basic queries
//-----------------------------------------------------------------------------

size_t listSize(const struct list *list)
{
    assert(list != NULL);
    size_t counter = 1;
    if (list->head == NULL && list->tail == NULL) {
        return 0;
    }
    struct node* currNode = list->head;
    while (currNode->next != NULL) {
        ++counter;
        currNode = currNode->next;

    }
    return counter;
}

bool listIsEmpty(const struct list *list)
{
    if (list->head == NULL && list->tail == NULL) { // the list has no head and no tail
        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------
//  Task 4: Element retrieval
//-----------------------------------------------------------------------------

bool listPopFront(struct list *list, void *data)
{
    assert(list != NULL);
    if (listIsEmpty(list) == true) { // list is empty
        return false;
    }
    struct node* second = list->head->next;
    if (data != NULL) {
        memcpy(data, list->head->data, list->elem_size);
    }
    free(list->head->data);
    free(list->head);
    list->head = second;
    if (second == NULL) {
        list->tail = NULL;
    }
    return true;
}

//-----------------------------------------------------------------------------
//  Task 5: Destruction and mayhem
//-----------------------------------------------------------------------------

void listDestroy(struct list *list)
{
    assert(list != NULL);
    /*if (listIsEmpty(list)) {
        free(list);
        return;
    }
    struct node* currNode = list->head;
    struct node* nextNode = list->head->next;
    while (currNode != NULL) {
        free(currNode->data);
        free(currNode);
        currNode = nextNode;
        if (nextNode != NULL) {
            nextNode = nextNode->next;
        }
    }
    free(list);*/
    while (listPopFront(list, 0)) {
        // nothing happens
    }
}

//-----------------------------------------------------------------------------
//  Bonus 1: Operations at both ends
//-----------------------------------------------------------------------------

/**  NOTE  **
 *
 * You ‹MUST› uncomment the LLIST_ENABLE_ALL_ENDS macro at the beginning
 * of ‹list.h› to enable tests and implementation of these functions.
 */

#if defined(LLIST_ENABLE_ALL_ENDS)

bool listPushFront(struct list *list, const void *data)
{
    // TODO: remove the following lines and implement the function
    UNUSED(list);
    UNUSED(data);
    NOT_IMPLEMENTED(false);
}

bool listPopBack(struct list *list, void *data)
{
    // Note that without «LLIST_ENABLE_TWO_LINKS» this function can
    // only be implemented in ‹O(n)› time (unless other crazy optimizations
    // are in place).

    // TODO: remove the following lines and implement the function
    UNUSED(list);
    NOT_IMPLEMENTED(NULL);
}

#endif // LLIST_ENABLE_ALL_ENDS
