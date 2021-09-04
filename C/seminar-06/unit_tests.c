#define CUT
#define CUT_MAIN
#include "cut.h"

#include <stdlib.h>
#include <string.h>
#include "dynamicLib.h"

TEST(dynStringCopy)
{
    const char *orig = "Ahoj svet !";

    SUBTEST(checkSimpleString)
    {
        char *copy = dynamicStringCopy(orig);
        CHECK(copy != NULL);
        CHECK(strcmp(orig, copy) == 0);
        free(copy);
    }

    SUBTEST(checkNULL)
    {
        CHECK(dynamicStringCopy(NULL) == NULL);
    }
}

TEST(DynamicStringJoin)
{
    const char *ahoj = "Ahoj ";
    const char *svet = "svet!";

    SUBTEST(TwoWords)
    {
        char *result = dynamicStringJoin(ahoj, svet);
        CHECK(result != NULL);
        CHECK(strcmp(result, "Ahoj svet!") == 0);
        free(result);
    }

    SUBTEST(BothEmpty)
    {
        char *result = dynamicStringJoin("", "");
        CHECK(result != NULL);
        CHECK(strcmp(result, "") == 0);
        free(result);
    }

    SUBTEST(BothNull)
    {
        CHECK(dynamicStringJoin(NULL, NULL) == NULL);
    }

    SUBTEST(FirstNull)
    {
        CHECK(dynamicStringJoin(NULL, ahoj) == NULL);
    }

    SUBTEST(SecondNull)
    {
        CHECK(dynamicStringJoin(ahoj, NULL) == NULL);
    }
}

TEST(allocate2D)
{
    SUBTEST(ThreeRowsIncCols)
    {
        size_t cols[] = { 1, 2, 3 };
        char **matrix = (char **)dynamic2DAlloc(3, cols);
        CHECK(matrix != NULL);

        for (int i = 0; i < 3; i++) {
            CHECK(matrix[i] != NULL);
            free(matrix[i]);
        }
        free(matrix);
    }

    SUBTEST(TowRowsWithZero)
    {
        size_t cols[] = { 0, 1 };
        char **matrix = (char **)dynamic2DAlloc(2, cols);
        CHECK(matrix != NULL);

        CHECK(matrix[0] == NULL);

        CHECK(matrix[1] != NULL);
        free(matrix[1]);

        free(matrix);
    }

    SUBTEST(ZeroRows)
    {
        size_t cols[] = { 0, 1 };
        CHECK(dynamic2DAlloc(0, cols) == NULL);
    }

    SUBTEST(NullCols)
    {
        CHECK(dynamic2DAlloc(5, NULL) == NULL);
    }
}

TEST(free2D)
{
    SUBTEST(Free3Rows)
    {
        int **matrix = malloc(sizeof(int *) * 3);

        for (int i = 0; i < 3; i++) {
            matrix[i] = malloc(sizeof(int) * (i + 1));
        }

        CHECK(dynamic2DFree((void **)matrix, 2) == 0);
    }

    SUBTEST(NullMemory)
    {
        CHECK(dynamic2DFree(NULL, 2) == 1);
    }
}

TEST(Split)
{
    SUBTEST(CheckFiveWords)
    {
        const char *orig = "carrot, bannana, orange, kebab, mouse";
        const char expected[10][20] = { "carrot", "bannana", "orange", "kebab", "mouse" };
        size_t size;
        char **split = dynamicStringSplitSub(orig, ", ", &size);
        CHECK(size == 5);

        for (int i = 0; i < 5; i++) {
            CHECK(strcmp(expected[i], split[i]) == 0);
        }

        for (size_t i = 0; i < size; i++) {
            free(split[i]);
        }

        free(split);
    }

    SUBTEST(CheckNullSize)
    {
        CHECK(dynamicStringSplitSub("ahoj, svet", ", ", NULL) == NULL);
    }

    SUBTEST(CheckNullInput)
    {
        size_t size = 0;
        CHECK(dynamicStringSplitSub(NULL, ", ", &size) == NULL);
    }

    SUBTEST(CheckNullSubstrint)
    {
        size_t size = 0;
        CHECK(dynamicStringSplitSub("ahoj, svet", NULL, &size) == NULL);
    }
}
