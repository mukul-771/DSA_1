#include "test.h"

#include <string.h> // for testing generate_splits()

// QUESTION 1: DONE BY SHAURY PATEL(22110241),MUKUL MEENA(22110159)
/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */

// void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data))
// {
//     b[0] = 2; b[1] = 1;
//     process_selection(b, 2, data);
//     b[0] = 2; b[1] = 6;
//     process_selection(b, 2, data);
//     b[0] = 2; b[1] = 5;
//     process_selection(b, 2, data);
//     b[0] = 1; b[1] = 6;
//     process_selection(b, 2, data);
//     b[0] = 1; b[1] = 5;
//     process_selection(b, 2, data);
//     b[0] = 6; b[1] = 5;
//     process_selection(b, 2, data);
// }

void selections(int a[], int b[], int start, int end, int index, int k, void *data, void (*process_selection)(int *b, int k, void *data))
{
    if (index==k)
    {
        process_selection(b,k,data);
        return;
    }
    for (int i=start; i<end && end - i + 1 >= k - index; ++i)
    {
        b[index] = a[i];
        selections(a,b,i + 1,end,index+1,k,data,process_selection);
    }
}

void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data))
{
    selections(a, b, 0, n, 0, k, data, process_selection);
}

// void process_selection(int *b, int k, void *data)    //for printing (example usage)
// {
//     for (int i = 0; i < k; i++)
//     {
//         printf("%d ", b[i]);
//     }
//     printf("\n");
// }
// int main()
// {
//     int a[] = {1, 2, 3, 4};
//     int n = sizeof(a) / sizeof(a[0]);
//     int k = 3;
//     int b[k];
//     generate_selections(a, n, k, b, NULL, process_selection);
//     return 0;
// }

// QUESTION 2: DONE BY SHAURY PATEL(22110241),MUKUL MEENA(22110159),KAILA UDAY(22110111)
/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 */
// void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void (*process_split)(char buf[], void *data))
// {
//     strcpy(buf, "art is toil");
//     process_split(buf, data);
//     strcpy(buf, "artist oil");
//     process_split(buf, data);
// }

void generate_splits_helper(const char *source, const char *dictionary[], int nwords, char buf[], int sourceIndex, int bufIndex, void *data, void (*process_split)(char buf[], void *data))
{
    if (sourceIndex == strlen(source)) {
        buf[bufIndex] = '\0';
        process_split(buf, data);
        return;
    }

    char word[100]; 
    int wordIndex = 0; 
    while (sourceIndex < strlen(source)) {
        word[wordIndex] = source[sourceIndex];
        wordIndex++;
        sourceIndex++;
        word[wordIndex] = '\0';
        for (int i = 0; i < nwords; i++) {
            if (strcmp(word,dictionary[i]) == 0) {
                strcpy(buf + bufIndex, word);
                bufIndex += strlen(word);
                if (sourceIndex< strlen(source)) {
                    buf[bufIndex] = ' ';
                    bufIndex++;
                }
                generate_splits_helper(source, dictionary, nwords, buf, sourceIndex, bufIndex, data, process_split);
                bufIndex -= strlen(word);
                if (sourceIndex < strlen(source)) {
                    bufIndex--;
                }
            }
        }
    }
}

void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void (*process_split)(char buf[], void *data))
{
    int sourceIndex = 0;
    int bufIndex = 0;
    generate_splits_helper(source, dictionary, nwords, buf, sourceIndex, bufIndex, data, process_split);
}

void process_split(char buf[], void *data) {    //for printing
    printf("%s\n", buf);
}

// int main() {        
//     const char *dictionary[] = { "ART", "IS", "TOIL", "OIL", "ARTIST" ,"AR","TIST"};
//     // const char *dictionary[]={"ARTISTOIL"};
//     int nwords = sizeof(dictionary) / sizeof(dictionary[0]);
//     const char *source = "ARTISTOIL";
//     void *data = NULL;
//     char buf[100];
//     generate_splits(source, dictionary, nwords, buf, data, process_split);
//     return 0;
// }

//QUESTION 3: DONE BY KAILA UDAY(22110111)
/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */
// void previous_permutation(int a[], int n)
// {
//     a[0] = 1;
//     a[1] = 5;
//     a[2] = 4;
//     a[3] = 6;
//     a[4] = 3;
//     a[5] = 2;
// }

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int a[], int start, int end) {
    while (start < end) {
        swap(&a[start], &a[end]);
        start++;
        end--;
    }
}

void previous_permutation(int a[], int n) {
    int i=n-2;
    while (i >= 0 && a[i] <= a[i + 1]) {
        i--;
    }
    if (i < 0) {
        return;
    }
    int j=n - 1;
    while (a[j]>=a[i]) {
        j--;
    }
    swap(&a[i],&a[j]);
    reverse(a,i+1,n-1);
}

// int main() {                            //FOR PRINTING PREVIOUS PERMUTATION
//     int arr[] = {2,3,5,4,6};
//     int n = sizeof(arr) / sizeof(arr[0]);
//     printf("Original array: ");
//     for (int i = 0; i < n; i++) {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");
//     previous_permutation(arr, n);
//     printf("Previous permutation: ");
//     for (int i = 0; i < n; i++) {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");
//     return 0;
// }

/* Write your tests here. Use the previous assignment for reference. */

typedef struct {
    int index;
    int err;
    int first;
} state_t;

static void test_selections_2165(int b[], int k, void *data)
{
    state_t *s = (state_t *)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if ((b[0] != 2) || (b[1] != 1)) {
            s->err = 1;
        }
        break;
    case 1:
        if ((b[0] != 2) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 2:
        if ((b[0] != 2) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 3:
        if ((b[0] != 1) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 4:
        if ((b[0] != 1) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 5:
        if ((b[0] != 6) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}

void count_selections(int b[], int k, void *data)
{
    int *d = (int*)data;
    ++*d;
}

typedef struct {
    int b[100];
} selection_t;

void last_selection(int b[], int k, void *data)
{
    selection_t *s = (selection_t*)data;
    for (int i = 0; i < k; ++i) {
        s->b[i] = b[i];
    }
}

BEGIN_TEST(generate_selections) {
    int a[] = { 2, 1, 6, 5 };
    int b[10];
    state_t s2165 = { .index = 0, .err = 1, .first = 1 };
    generate_selections(a, 4, 2, b, &s2165, test_selections_2165);
    ASSERT(!s2165.err, "Failed on 2 1 6 5.");
    int c = 0;
    int aa[] = { 1, 5, 3, 0, 1, 12, 4, 3, 6, 6 };
    generate_selections(aa, 10, 5, b, &c, count_selections);
    ASSERT_EQ(c, 252, "Failed on 10C5.");

    selection_t s;
    generate_selections(aa, 10, 5, b, &s, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s.b, 5, "Failed on last of 10C5.", 12, 4, 3, 6, 6);
} END_TEST

void test_splits_art(char buf[], void *data)
{
    state_t *s = (state_t*)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if (strcmp(buf, "art is toil")) {
            s->err = 1;
        }
        break;
    case 1:
        if (strcmp(buf, "artist oil")) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}

BEGIN_TEST(generate_splits) {
    const char *a = "artistoil";
    const char *dict[] = {
        "art",
        "artist",
        "is",
        "oil",
        "toil"
    };
    int nwords = 5;
    state_t s = { .index = 0, .err = 1, .first = 1 };
    char buf[256];
    generate_splits(a, dict, nwords, buf, &s, test_splits_art);
    ASSERT(!s.err, "Failed on 'artistoil'.");
} END_TEST

BEGIN_TEST(previous_permutation) {
    int a[] = { 1, 5, 6, 2, 3, 4 };
    previous_permutation(a, 6);
    ASSERT_ARRAY_VALUES_EQ(a, 6, "Failed on 1 5 6 2 3 4.", 1, 5, 4, 6, 3, 2);
    int aa[] = { 1, 2, 3, 5, 4, 6 };
    previous_permutation(aa, 3); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(aa, 3, "Failed on 1 2 3.", 1, 2, 3);
} END_TEST

int main()
{
    run_tests((test_t[]) {
            TEST(generate_selections),
            TEST(generate_splits),
            TEST(previous_permutation),
            0
        });
    return 0;
}