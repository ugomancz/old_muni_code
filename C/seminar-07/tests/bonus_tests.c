#define _POSIX_C_SOURCE 1

#define CUT
#define CUT_MAIN
#include "cut.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "list_utils.h"

#include "test_utils.h"

//=============================================================================
//  Callbacks
//=============================================================================

static
bool isEven(const void *number)
{
    return *((const int*) number) % 2 == 0;
}

static
bool isOdd(const void *number)
{
    return *((const int*) number) % 2 != 0;
}

static
bool isZero(const void *number)
{
    return *((const int*) number) == 0;
}

/* if called multiple times, saves all arguments in a single value
 * as a polynomial
 *
 * example:
 *     a = 1; r = 0;
 *     poly(1); poly(2); poly(3)
 *
 *     r == 123
 */
static int a;
static int r;

static
void poly(void *n)
{
    r += (a * *((int*) n));
    a *= 10;
}

// integral comparator for listSort
static
int cmpnum(const void *a, const void *b)
{
    int *na = (int*) a;
    int *nb = (int*) b;

    return (*na) - (*nb);
}

//=============================================================================
//  Tests
//=============================================================================

#define listInitInt(LIST)                                               \
    listInit((LIST), sizeof(int))

//--  listAny  ----------------------------------------------------------------

TEST(listAny)
{
    struct list list;
    listInitInt(&list);

    SUBTEST(empty) {
        CHECK(!listAny(&list, &isZero));
    }

    SUBTEST(odd_value_true) {
        int numbers[] = { 0, 0, 0, 0, 1, 0 };
        for (int i = 0; i < 6; ++i)
            listPushBack(&list, numbers + i);

        CHECK(listAny(&list, &isOdd));
    }

    SUBTEST(even_value_false) {
        int numbers[] = { 1, 3, 5, 7, 9 };
        for (int i = 0; i < 5; ++i)
            listPushBack(&list, numbers + i);

        CHECK(!listAny(&list, &isEven));
    }

    listDestroy(&list);
}

//--  listAll  ----------------------------------------------------------------

TEST(listAll)
{
    struct list list;
    listInitInt(&list);

    SUBTEST(empty) {
        CHECK(listAll(&list, &isZero));
    }

    SUBTEST(zero_values_true) {
        int numbers[] = { 0, 0, 0, 0, };
        for (int i = 0; i < 4; ++i)
            listPushBack(&list, numbers + i);

        CHECK(listAll(&list, &isZero));
    }

    SUBTEST(odd_values_false) {
        int numbers[] = { 1, 3, 5, 7, 9, 11 };
        for (int i = 0; i < 6; ++i)
            listPushBack(&list, numbers + i);

        CHECK(listAll(&list, &isOdd));
    }

    listDestroy(&list);

}

//--  listInsert  -------------------------------------------------------------

TEST(listInsert)
{
    struct list list;
    listInitInt(&list);

    SUBTEST(begin) {
        int numbers[] = { 0, 1, 2, 3 };
        for (int i = 1; i < 4; ++i)
            listPushBack(&list, &numbers[i]);

        CHECK(listInsert(&list, 0, numbers));
        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 4, numbers);
    }

    SUBTEST(end) {
        int numbers[] = { 0, 1, 2, 3 };
        for (int i = 0; i < 3; ++i)
            listPushBack(&list, numbers + i);

        CHECK(listInsert(&list, 3, numbers + 3));
        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 4, numbers);
    }

    SUBTEST(middle) {
        int numbers[] = { -2, -1, 0, 1, 2 };
        for (int i = 0; i < 5; ++i) {
            if (i != 2)
                listPushBack(&list, numbers + i);
        }

        CHECK(listInsert(&list, 2, numbers + 2));
        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 5, numbers);
    }

    listDestroy(&list);
}

//--  listGet  ----------------------------------------------------------------

TEST(listGet)
{
    struct list list;
    listInitInt(&list);

    int numbers[] = { 0, 1, 2, 3, 4 };
    for (int i = 0; i < 5; ++i)
        listPushBack(&list, numbers + i);

    SUBTEST(non_existent) {
        const void *ptr = listGet(&list, 8);

        CHECK(ptr == NULL);
    }

    SUBTEST(members) {
        for (int i = 0; i < 5; ++i) {
            void *expected = &numbers[i];
            const void *got = listGet(&list, i);

            CHECK(memcmp(got, expected, sizeof(int)) == 0);
        }
    }

    listDestroy(&list);
}

//--  listGetIndex  -----------------------------------------------------------

TEST(listGetIndex)
{
    struct list list;
    listInitInt(&list);

    int numbers[] = { 0, 1, 2, 3, 4 };
    for (int i = 0; i < 5; ++i)
        listPushBack(&list, &numbers[i]);

    SUBTEST(non_existent) {
        int i = 8;
        int index = listGetIndex(&list, &i);

        CHECK(index == -1);
    }

    SUBTEST(members) {
        for (int i = 0; i < 5; ++i) {
            int val = numbers[i];
            int index = listGetIndex(&list, &val);

            CHECK(index == i);
        }
    }

    listDestroy(&list);
}

//--  listRemove  -------------------------------------------------------------

TEST(listRemove)
{
    struct list list;
    listInitInt(&list);

    int numbers[] = { 0, 1, 2, 3 };

    for (int i = 0; i < 4; ++i) {
        listPushBack(&list, &numbers[i]);
    }

    SUBTEST(begin) {
        int removed;

        CHECK(listRemove(&list, 0, &removed));
        LIST_CHECK_INTEGRITY(&list);
        CHECK(removed == 0);

        LIST_CHECK_CONTENTS(&list, 3, &numbers[1]);
    }

    SUBTEST(end) {
        int removed;

        CHECK(listRemove(&list, 3, &removed));
        LIST_CHECK_INTEGRITY(&list);
        CHECK(removed == 3);

        LIST_CHECK_CONTENTS(&list, 3, &numbers[0]);
    }

    SUBTEST(middle) {
        int removed;

        CHECK(listRemove(&list, 1, &removed));
        LIST_CHECK_INTEGRITY(&list);
        CHECK(removed == 1);

        CHECK(listRemove(&list, 1, &removed));
        LIST_CHECK_INTEGRITY(&list);
        CHECK(removed == 2);

        numbers[1] = 3;
        LIST_CHECK_CONTENTS(&list, 2, numbers);
    }

    listDestroy(&list);
}

//--  listFindFirst  ----------------------------------------------------------

TEST(listFindFirst)
{
    struct list list;
    listInitInt(&list);

    SUBTEST(no_match) {
        int numbers[] = { 1, 2, 3 };

        for (int i = 0; i < 3; ++i)
            listPushBack(&list, numbers + i);

        CHECK(listFindFirst(&list, &isZero) == NULL);
    }

    SUBTEST(match) {
        int numbers[] = { 1, 0, 2, 0, 3 };

        for (int i = 0; i < 5; ++i)
            listPushBack(&list, numbers + i);

        CHECK(listFindFirst(&list, &isZero) == list.head->next->data);
    }

    listDestroy(&list);
}

//--  listFindLast  -----------------------------------------------------------

TEST(listFindLast)
{
    struct list list;
    listInitInt(&list);

    SUBTEST(no_match) {
        int numbers[] = { 1, 2, 3 };

        for (int i = 0; i < 3; ++i)
            listPushBack(&list, numbers + i);

        CHECK(listFindLast(&list, &isZero) == NULL);
    }

    SUBTEST(match) {
        int numbers[] = { 1, 0, 2, 0, 3 };

        for (int i = 0; i < 5; ++i)
            listPushBack(&list, numbers + i);

        struct node *pre_tail = list.head;
        while (pre_tail != NULL && pre_tail->next != list.tail)
            pre_tail = pre_tail->next;

        CHECK(listFindLast(&list, &isZero) == pre_tail->data);
    }

    listDestroy(&list);
}

//--  listForEach  ------------------------------------------------------------

TEST(listForEach)
{
    a = 1;
    r = 0;

    struct list list;
    listInitInt(&list);

    int numbers[] = { 3, 7, 2, 1 };

    for (int i = 0; i < 4; ++i)
        listPushBack(&list, numbers + i);

    listForEach(&list, &poly);
    CHECK(r == 1273);

    listDestroy(&list);
}

//--  listForEachReverse  -----------------------------------------------------

TEST(listForEachReverse)
{
    a = 1;
    r = 0;

    struct list list;
    listInitInt(&list);

    int numbers[] = { 1, 3, 0, 4, 9 };

    for (int i = 0; i < 5; ++i)
        listPushBack(&list, numbers + i);

    listForEachReverse(&list, &poly);
    CHECK(r == 13049);

    listDestroy(&list);
}

//--  listSort  ---------------------------------------------------------------

TEST(listSort)
{
    struct list list;
    listInitInt(&list);

    int numbers[] = { 6, 7, 2, 3, 8, 1, 9, 4, 0, 5 };
    int ordered[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int i = 0; i < 10; ++i)
        listPushBack(&list, &numbers[i]);

    listSort(&list, &cmpnum);

    LIST_CHECK_INTEGRITY(&list);
    LIST_CHECK_CONTENTS(&list, 10, ordered);

    listDestroy(&list);
}
