#define CUT
#define CUT_MAIN

//#ifndef DEBUG
//#  define CUT_FORK_MODE
//#endif

#include "cut.h"

#include <stdio.h>
#include <string.h>

#include "list.h"

#include "test_utils.h"

//-----------------------------------------------------------------------------
//  Callbacks
//-----------------------------------------------------------------------------

#define UNUSED(VARIABLE)                                                    \
    ((void) (VARIABLE))

#define NODE_SET_INT(NODE, VALUE)                                           \
    do {                                                                    \
        int _value = (VALUE);                                               \
        memcpy((NODE)->data, &_value, sizeof(int));                         \
    } while (0)

static
struct node **listFakeNodes(struct list *list, size_t size)
{
    struct node **result = malloc((size + 1) * sizeof(struct node *));

    if (result == NULL)
        cut_FatalExit("dummyNodes: Cannot allocate memory for nodes");

    for (unsigned i = 0; i < size; ++i) {
        result[i] = malloc(sizeof(struct node)
#if defined(LLIST_ENABLE_FAM)
                        + list->elem_size
#endif
                    );

        if (result[i] == NULL)
            cut_FatalExit("dummyNodes: Cannot allocate memory for node");

#if !defined(LLIST_ENABLE_FAM)
        result[i]->data = malloc(list->elem_size);
        if (result[i]->data == NULL)
            cut_FatalExit("dummyNodes: Cannot allocate memory for data");
#endif
    }

    for (unsigned i = 0; i < size; ++i) {
        result[i]->next = (i + 1 == size) ? NULL : result[i + 1];
#if defined(LLIST_ENABLE_TWO_LINKS)
        result[i]->prev = (i == 0) ? NULL : result[i - 1];
#endif
    }

    list->head = result[0];
    list->tail = result[size - 1];

    result[size] = NULL;
    return result;
}

static
void listUnfakeNodes(struct node **nodes)
{
    if (nodes == NULL)
        return;

    for (unsigned i = 0; nodes[i] != NULL; ++i) {
#if !defined(LLIST_ENABLE_FAM)
        free(nodes[i]->data);
#endif

        free(nodes[i]);
    }

    free(nodes);
}

//-----------------------------------------------------------------------------
//  Tests
//-----------------------------------------------------------------------------

//--  listInitialize  ---------------------------------------------------------

TEST(listInit)
{
    // this test makes sure that listInitialize initializes
    // head and tail to NULL
    struct list list;
    LIST_INITIALIZE(list, (struct node*)(42), (struct node*)(666), 90210);

    listInit(&list, sizeof(void*));

    CHECK(list.head == NULL);
    CHECK(list.tail == NULL);
    CHECK(list.elem_size == sizeof(void*));
}

//--  listDestroy  ------------------------------------------------------------

TEST(listDestroy)
{
    struct list list;
    struct node **nodes = NULL;
    LIST_INITIALIZE(list, NULL, NULL, sizeof(int));

    SUBTEST(empty) {
        (void) nodes;

        // this should just end without SIGSEGV nor other bad stuff
        listDestroy(&list);
    }

    SUBTEST(not_empty) {
        // create 3 nodes
        nodes = listFakeNodes(&list, 3);

        for (int i = 0; i < 1; ++i)
            NODE_SET_INT(nodes[i], i);

        listDestroy(&list);

        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 0, NULL);
    }

    free(nodes);
}

//--  listSize  ---------------------------------------------------------------

TEST(listSize)
{
    struct list list;
    struct node **nodes = NULL;
    LIST_INITIALIZE(list, NULL, NULL, sizeof(int));

    SUBTEST(empty) {
        (void) nodes;
        CHECK(listSize(&list) == 0U);
    }

    SUBTEST(single_value) {
        nodes = listFakeNodes(&list, 1);
        NODE_SET_INT(nodes[0], 67);

        CHECK(listSize(&list) == 1U);
    }

    SUBTEST(two_values) {
        nodes = listFakeNodes(&list, 2);
        NODE_SET_INT(nodes[0], 67);
        NODE_SET_INT(nodes[1], 76);

        CHECK(listSize(&list) == 2U);
    }

    SUBTEST(five_values) {
        nodes = listFakeNodes(&list, 5);
        for (unsigned i = 0; i < 5; ++i)
            NODE_SET_INT(nodes[i], i);

        CHECK(listSize(&list) == 5U);
    }

    listUnfakeNodes(nodes);
}

//--  listIsEmpty  ------------------------------------------------------------

TEST(listIsEmpty)
{
    struct list list;
    struct node **nodes = NULL;
    LIST_INITIALIZE(list, NULL, NULL, sizeof(int));

    SUBTEST(when_it_is_indeed_empty) {
        UNUSED(nodes);
        CHECK(listIsEmpty(&list));
    }

    SUBTEST(when_it_is_in_fact_not_empty) {
        nodes = listFakeNodes(&list, 1);
        NODE_SET_INT(nodes[0], 42);

        CHECK(!listIsEmpty(&list));
    }

    SUBTEST(when_it_is_in_fact_not_empty_at_all) {
        nodes = listFakeNodes(&list, 3);
        for (unsigned i = 0; i < 3; ++i)
            NODE_SET_INT(nodes[i], 42);

        CHECK(!listIsEmpty(&list));
    }

    SUBTEST(make_sure_that_list_size_is_not_used) {
        // this test makes sure listIsEmpty does not use
        // listSize (if it's correctly implemented)
        struct node h, s, t;

        // make head and tail point to a single node s
        // where s behaves like a 'sink' (it points to itself)
#if defined(LLIST_ENABLE_TWO_LINKS)
        h.prev =
#endif
            t.next = NULL;

#if defined(LLIST_ENABLE_TWO_LINKS)
        t.prev = s.prev =
#endif
            h.next = s.next = &s;

        // the test will fail if listSize is called on this abomination
        list.head = &h;
        list.tail = &t;
        // .. well, OK, it will not fail, it will not end at all

        // BUT you can solve halting problem in your free time and
        // uncomment the following line:
        //CHECK(willHalt(&listIsEmpty, &list));

        CHECK(!listIsEmpty(&list));
    }

    listUnfakeNodes(nodes);
}

//--  listPushBack  -----------------------------------------------------------

TEST(listPushBack)
{
    struct list list;
    LIST_INITIALIZE(list, NULL, NULL, sizeof(int));

    int numbers[5];
    for (unsigned i = 0; i < 5; ++i)
        numbers[i] = i;

    SUBTEST(single_value_to_empty_list) {
        CHECK(listPushBack(&list, &numbers[0]));

        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 1, numbers);
    }

    SUBTEST(single_value_to_list_with_one_element) {
        struct node **nodes = listFakeNodes(&list, 1);
        NODE_SET_INT(nodes[0], numbers[0]);
        CHECK(listPushBack(&list, &numbers[1]));

        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 2, numbers);

        // actual nodes will be «free()»d in «freeNodes()»
        free(nodes);
    }

    SUBTEST(single_value_to_list_with_two_elements) {
        struct node **nodes = listFakeNodes(&list, 2);
        NODE_SET_INT(nodes[0], numbers[0]);
        NODE_SET_INT(nodes[1], numbers[1]);
        CHECK(listPushBack(&list, &numbers[2]));

        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 3, numbers);

        // actual nodes will be «free()»d in «freeNodes()»
        free(nodes);
    }

    SUBTEST(more_elements) {
        for (unsigned i = 0; i < 5; ++i)
            CHECK(listPushBack(&list, &numbers[i]));

        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 5, numbers);
    }

    freeNodes(list.head);
}

//--  listPopFront  -----------------------------------------------------------

TEST(listPopFront)
{
    struct list list;
    struct node **nodes = NULL;
    LIST_INITIALIZE(list, NULL, NULL, sizeof(int));

    SUBTEST(empty_list) {
        UNUSED(nodes);

        int dummy;
        CHECK(!listPopFront(&list, &dummy));
        LIST_CHECK_INTEGRITY(&list);
    }

    SUBTEST(single_value) {
        nodes = listFakeNodes(&list, 1);
        NODE_SET_INT(nodes[0], 42);

        int popped;
        CHECK(listPopFront(&list, &popped));
        CHECK(popped == 42);

        nodes[0] = NULL;
        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 0, NULL);
    }

    SUBTEST(two_values) {
        nodes = listFakeNodes(&list, 2);

        int numbers[2];
        for (unsigned i = 0; i < 2; ++i)
            NODE_SET_INT(nodes[i], numbers[i] = i);

        for (int expected = 1; expected >= 0; --expected) {
            int popped;

            CHECK(listPopFront(&list, &popped));
            CHECK(popped == (1 - expected));

            nodes[expected] = NULL;
            LIST_CHECK_INTEGRITY(&list);
            LIST_CHECK_CONTENTS(&list, expected, numbers + (2 - expected));
        }
    }

    SUBTEST(five_values) {
        nodes = listFakeNodes(&list, 5);

        int numbers[5];
        for (unsigned i = 0; i < 5; ++i)
            NODE_SET_INT(nodes[i], numbers[i] = i);

        for (int expected = 4; expected >= 0; --expected) {
            int popped;

            CHECK(listPopFront(&list, &popped));
            CHECK(popped == (4 - expected));

            nodes[expected] = NULL;
            LIST_CHECK_INTEGRITY(&list);
            LIST_CHECK_CONTENTS(&list, expected, numbers + (5 - expected));
        }
    }

    SUBTEST(five_values_with_NULL_target) {
        nodes = listFakeNodes(&list, 5);

        int numbers[5];
        for (unsigned i = 0; i < 5; ++i)
            NODE_SET_INT(nodes[i], numbers[i] = i);

        for (int expected = 4; expected >= 0; --expected) {
            CHECK(listPopFront(&list, NULL));

            nodes[expected] = NULL;
            LIST_CHECK_INTEGRITY(&list);
            LIST_CHECK_CONTENTS(&list, expected, numbers + (5 - expected));
        }
    }

    listUnfakeNodes(nodes);
}
#if defined(LLIST_ENABLE_ALL_ENDS)

//--  listPopBack  ------------------------------------------------------------

TEST(listPopBack)
{
    struct list list;
    struct node **nodes = NULL;
    LIST_INITIALIZE(list, NULL, NULL, sizeof(int));

    SUBTEST(empty_list) {
        UNUSED(nodes);

        int dummy;
        CHECK(!listPopBack(&list, &dummy));
        LIST_CHECK_INTEGRITY(&list);
    }

    SUBTEST(single_value) {
        nodes = listFakeNodes(&list, 1);
        NODE_SET_INT(nodes[0], 42);

        int popped;
        CHECK(listPopBack(&list, &popped));
        CHECK(popped == 42);

        nodes[0] = NULL;
        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 0, NULL);
    }

    SUBTEST(two_values) {
        nodes = listFakeNodes(&list, 2);

        int numbers[2];
        for (unsigned i = 0; i < 2; ++i)
            NODE_SET_INT(nodes[i], numbers[i] = i);

        for (int expected = 1; expected >= 0; --expected) {
            int popped;

            CHECK(listPopBack(&list, &popped));
            CHECK(popped == expected);

            nodes[expected] = NULL;
            LIST_CHECK_INTEGRITY(&list);
            LIST_CHECK_CONTENTS(&list, expected, numbers);
        }
    }

    SUBTEST(five_values) {
        nodes = listFakeNodes(&list, 5);

        int numbers[5];
        for (unsigned i = 0; i < 5; ++i)
            NODE_SET_INT(nodes[i], numbers[i] = i);

        for (int expected = 4; expected >= 0; --expected) {
            int popped;

            CHECK(listPopBack(&list, &popped));
            CHECK(popped == expected);

            nodes[expected] = NULL;
            LIST_CHECK_INTEGRITY(&list);
            LIST_CHECK_CONTENTS(&list, expected, numbers);
        }
    }

    SUBTEST(five_values_with_NULL_target) {
        nodes = listFakeNodes(&list, 5);

        int numbers[5];
        for (unsigned i = 0; i < 5; ++i)
            NODE_SET_INT(nodes[i], numbers[i] = i);

        for (int expected = 4; expected >= 0; --expected) {
            CHECK(listPopBack(&list, NULL));

            nodes[expected] = NULL;
            LIST_CHECK_INTEGRITY(&list);
            LIST_CHECK_CONTENTS(&list, expected, numbers);
        }
    }

    listUnfakeNodes(nodes);
}

//--  listPushFront  ----------------------------------------------------------

TEST(listPushFront)
{
    struct list list;
    LIST_INITIALIZE(list, NULL, NULL, sizeof(int));

    int numbers[5];
    for (unsigned i = 0; i < 5; ++i)
        numbers[i] = i;

    SUBTEST(single_value_to_empty_list) {
        CHECK(listPushFront(&list, &numbers[0]));

        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 1, numbers);
    }

    SUBTEST(single_value_to_list_with_one_element) {
        struct node **nodes = listFakeNodes(&list, 1);
        NODE_SET_INT(nodes[0], numbers[1]);
        CHECK(listPushFront(&list, &numbers[0]));

        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 2, numbers);

        // actual nodes will be «free()»d in «freeNodes()»
        free(nodes);
    }

    SUBTEST(single_value_to_list_with_two_elements) {
        struct node **nodes = listFakeNodes(&list, 2);
        NODE_SET_INT(nodes[0], numbers[1]);
        NODE_SET_INT(nodes[1], numbers[2]);
        CHECK(listPushFront(&list, &numbers[0]));

        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 3, numbers);

        // actual nodes will be «free()»d in «freeNodes()»
        free(nodes);
    }

    SUBTEST(more_elements) {
        for (unsigned i = 0; i < 5; ++i)
            CHECK(listPushFront(&list, &numbers[4 - i]));

        LIST_CHECK_INTEGRITY(&list);
        LIST_CHECK_CONTENTS(&list, 5, numbers);
    }

    freeNodes(list.head);
}
#endif // LLIST_ENABLE_ALL_ENDS
