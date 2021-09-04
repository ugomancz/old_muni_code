#include <assert.h>
#include <stdio.h>

#include "list.h"
#include "list_utils.h"

//--  REMOVE THE FOLLOWING MACROS WHEN DONE  ----------------------------------

// This is a common way to say that some parameter is not used.
#define UNUSED(VAR) ((void) VAR)

// This function prints an error message to standard error output
// that the function called is not implemented and returns some default value.
#ifdef DEBUG
#   define EXIT_TEST(VALUE)                                                 \
        return VALUE
#else
#   define EXIT_TEST(VALUE)                                                 \
        abort()
#endif

#define NOT_IMPLEMENTED(VALUE)                                              \
    do {                                                                    \
        fprintf(stderr, "Unimplemented function '%s' called.\n", __func__); \
        EXIT_TEST(VALUE);                                                   \
    } while (0)

bool listAny(const struct list *list, predicate p)
{
    UNUSED(list);
    UNUSED(p);
    NOT_IMPLEMENTED(false);
}

bool listAll(const struct list *list, predicate p)
{
    UNUSED(list);
    UNUSED(p);
    NOT_IMPLEMENTED(false);
}

bool listInsert(struct list *list, size_t index, void *data)
{
    UNUSED(list);
    UNUSED(index);
    UNUSED(data);
    NOT_IMPLEMENTED(false);
}

const void *listGet(const struct list *list, size_t index)
{
    UNUSED(list);
    UNUSED(index);
    NOT_IMPLEMENTED(NULL);
}

int listGetIndex(const struct list *list, const void *data)
{
    UNUSED(list);
    UNUSED(data);
    NOT_IMPLEMENTED(0);
}

bool listRemove(struct list *list, size_t index, void *data)
{
    UNUSED(list);
    UNUSED(index);
    UNUSED(data);
    NOT_IMPLEMENTED(false);
}

const void* listFindFirst(const struct list *list, predicate p)
{
    UNUSED(list);
    UNUSED(p);
    NOT_IMPLEMENTED(NULL);
}

const void* listFindLast(const struct list *list, predicate p)
{
    UNUSED(list);
    UNUSED(p);
    NOT_IMPLEMENTED(NULL);
}

void listForEach(struct list *list, action f)
{
    UNUSED(list);
    UNUSED(f);
    NOT_IMPLEMENTED();
}

void listForEachReverse(struct list *list, action f)
{
    UNUSED(list);
    UNUSED(f);
    NOT_IMPLEMENTED();
}

void listSort(struct list *list, comparator cmp)
{
    UNUSED(list);
    UNUSED(cmp);
    NOT_IMPLEMENTED();
}
