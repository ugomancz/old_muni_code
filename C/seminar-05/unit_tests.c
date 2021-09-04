#define CUT
#define CUT_MAIN
#include "cut.h"
#include "stringLibrary.h"

#define UNUSED(a) ((void)(a))

#define ASSERT_IN(a, s, c) ASSERT(stringCountStringInArray(_c(a), s) == c)

#define _c(a) ((const char **)(a))

// String length
TEST(stringLength)
{
    SUBTEST(singleWord)
    {
        CHECK(stringLength("Word") == 4);
    }

    SUBTEST(empty)
    {
        CHECK(stringLength("") == 0);
    }

    SUBTEST(null)
    {
        CHECK(stringLength(NULL) == 0);
    }

    SUBTEST(space)
    {
        CHECK(stringLength("Ahoj svet!") == 10);
    }

    SUBTEST(mutiWords)
    {
        CHECK(stringLength("Lorem\nIpsum\n Tabs Cols Rows\n") == 28);
    }
}

// String copy
TEST(stringCopy)
{
    SUBTEST(singleWord)
    {
        static char buffer[255];
        const char *pointer = stringCopy(buffer, "Word");
        CHECK(pointer != NULL);
        CHECK(strcmp(buffer, "Word") == 0);
    }

    SUBTEST(empty)
    {
        static char buffer[255];
        const char *pointer = stringCopy(buffer, "");
        CHECK(pointer != NULL);
        CHECK(strcmp(buffer, "") == 0);
    }

    SUBTEST(null)
    {
        static char buffer[255];
        const char *pointer = stringCopy(buffer, NULL);
        CHECK(pointer == NULL);
    }
}

// String char count
TEST(stringCountChar)
{
    SUBTEST(singleWord)
    {
        CHECK(stringCountChar("Ahoj", 'A') == 1);
    }

    SUBTEST(emptyWord)
    {
        CHECK(stringCountChar("", 'A') == 0);
    }

    SUBTEST(null)
    {
        CHECK(stringCountChar(NULL, 'A') == 0);
    }

    SUBTEST(sameChar)
    {
        CHECK(stringCountChar("AAAA", 'A') == 4);
    }

    SUBTEST(caseSensitive)
    {
        CHECK(stringCountChar("Ahoj", 'a') == 0);
    }

    SUBTEST(caseSensitive)
    {
        CHECK(stringCountChar("a aa aa bb ab bca", 'a') == 7);
    }
}

TEST(substringCount)
{
    SUBTEST(singleLetterInWord)
    {
        CHECK(stringCountSubstring("Ahoj", "A") == 1);
    }

    SUBTEST(sameChars)
    {
        CHECK(stringCountSubstring("aaa", "a") == 3);
    }

    SUBTEST(emptyWord)
    {
        CHECK(stringCountSubstring("", "a") == 0);
    }

    SUBTEST(nullWord)
    {
        CHECK(stringCountSubstring(NULL, "a") == 0);
    }

    SUBTEST(emptyPattern)
    {
        CHECK(stringCountSubstring("word", "") == 0);
    }

    SUBTEST(nullPattern)
    {
        CHECK(stringCountSubstring("word", NULL) == 0);
    }

    SUBTEST(sameCharPattern)
    {
        CHECK(stringCountSubstring("aaab", "aa") == 2);
    }

    SUBTEST(patternWithSpace)
    {
        CHECK(stringCountSubstring("abba baa ba b a", "a b") == 3);
    }
}

TEST(stringCountStringInArray)
{
    const char *const strings1[] = { "hello", "hi", 0 }; // all const

    SUBTEST(preparedArrayShouldContainOneHello)
    {
        ASSERT_IN(strings1, "hello", 1);
    }

    SUBTEST(prepadedArrayShouldContainOneHi)
    {
        ASSERT_IN(strings1, "hi", 1);
    }

    SUBTEST(nullArrayShouldContainNoneHi)
    {
        ASSERT_IN(NULL, "hi", 0);
    }

    SUBTEST(prepadedArrayShouldContainZeroNone)
    {
        ASSERT_IN(strings1, NULL, 0);
    }

    SUBTEST(emptyArrayShouldNotContainAnyting)
    {
        const char *const empty[] = { NULL }; // all const
        ASSERT_IN(empty, NULL, 0);
        ASSERT_IN(empty, "Ahoj", 0);
        ASSERT_IN(empty, "word", 0);
        ASSERT_IN(empty, "", 0);
    }
    SUBTEST(arrayWithFirstNullShouldBeEmpty)
    {
        const char *const empty2[] = { NULL, "hello", NULL }; // all const
        ASSERT_IN(empty2, "hello", 0);
        ASSERT_IN(empty2, "", 0);
        ASSERT_IN(empty2, NULL, 0);
    }
    SUBTEST(arrayWithMultipleOcurencesShouldRetunCorrectNumberOfOccurences)
    {
        const char *const multi[] = { "hello", "hi", "hello", NULL };
        ASSERT_IN(multi, "hello", 2);
    }
}

TEST(Split)
{
    SUBTEST(stringSplitBySemicolon)
    {
        const char *original = "Ahoj;svet;000;Query";
        char result[50][256];
        int size;
        char delim = ';';
        stringSplit(original, result, &size, delim);
        CHECK(size == 4);
        CHECK(strcmp(result[0], "Ahoj") == 0);
        CHECK(strcmp(result[1], "svet") == 0);
        CHECK(strcmp(result[2], "000") == 0);
        CHECK(strcmp(result[3], "Query") == 0);
    }

    SUBTEST(stringSplitBySpace)
    {
        const char *original = "Ahoj;svet;000;Query";
        char result[50][256];
        int size;
        char delim = ';';
        stringSplit(original, result, &size, delim);
        CHECK(size == 4);
        CHECK(strcmp(result[0], "Ahoj") == 0);
        CHECK(strcmp(result[1], "svet") == 0);
        CHECK(strcmp(result[2], "000") == 0);
        CHECK(strcmp(result[3], "Query") == 0);
    }

    SUBTEST(stringSplitEmpty)
    {
        const char *original = "";
        char result[50][256];
        int size;
        char delim = ';';
        stringSplit(original, result, &size, delim);
        CHECK(size == 0);
    }

    SUBTEST(stringSplitNull)
    {
        const char *original = NULL;
        char result[50][256];
        int size;
        char delim = ';';
        stringSplit(original, result, &size, delim);
        CHECK(size == 0);
    }

    SUBTEST(stringSplitDelims)
    {
        const char *original = ";;;";
        char result[50][256];
        int size;
        char delim = ';';
        stringSplit(original, result, &size, delim);
        CHECK(size == 4);
        CHECK(strcmp(result[0], "") == 0);
        CHECK(strcmp(result[1], "") == 0);
        CHECK(strcmp(result[2], "") == 0);
        CHECK(strcmp(result[3], "") == 0);
    }
}
