#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"
#define MAX_LEN 100

int main() {
    int choice;
    int index;
    char word[MAX_LEN];
    char searchWord[MAX_LEN];
    StrList* list = StrList_alloc();

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Insert strings into the list\n");
        printf("2. Insert a string at a specific index\n");
        printf("3. Print the list\n");
        printf("4. Print the length of the list\n");
        printf("5. Print string at specific index\n");
        printf("6. Print total number of characters in the list\n");
        printf("7. Count occurrences of a string\n");
        printf("8. Remove all occurrences of a string\n");
        printf("9. Remove element at specific index\n");
        printf("10. Reverse the list\n");
        printf("11. Delete entire list\n");
        printf("12. Sort the list lexicographically\n");
        printf("13. Check if the list is sorted lexicographically\n");
        printf("0. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Exiting program.\n");
                StrList_free(list);
                exit(0);
            case 1:
                printf("Enter words to insert separated by spaces: ");
                scanf(" %[^\n]s", word);
                char* token = strtok(word, " ");
                while (token != NULL) {
                    StrList_insertLast(list, token);
                    token = strtok(NULL, " ");
                }
                break;
            case 2:
                printf("Enter index to insert at: ");
                scanf("%d", &index);
                printf("Enter word to insert: ");
                scanf(" %[^\n]s", word);
                StrList_insertAt(list, word, index);
                break;
            case 3:
                printf("List: ");
                StrList_print(list);
                break;
            case 4:
                printf("Length of the list: %zu\n", StrList_size(list));
                break;
            case 5:
                printf("Enter index to print: ");
                scanf("%d", &index);
                printf("String at index %d: %s\n", index, StrList_firstData(list));
                break;
            case 6:
                printf("Total number of characters: %d\n", StrList_printLen(list));
                break;
            case 7:
                printf("Enter word to count: ");
                scanf(" %[^\n]s", searchWord);
                printf("Occurrences of '%s': %d\n", searchWord, StrList_count(list, searchWord));
                break;
            case 8:
                printf("Enter word to remove: ");
                scanf(" %[^\n]s", searchWord);
                StrList_remove(list, searchWord);
                break;
            case 9:
                printf("Enter index to remove: ");
                scanf("%d", &index);
                StrList_removeAt(list, index);
                break;
            case 10:
                StrList_reverse(list);
                printf("List reversed.\n");
                break;
            case 11:
                StrList_free(list);
                list = StrList_alloc();
                printf("List deleted.\n");
                break;
            case 12:
                StrList_sort(list);
                printf("List sorted lexicographically.\n");
                break;
            case 13:
                if (StrList_isSorted(list)) {
                    printf("List is sorted lexicographically.\n");
                } else {
                    printf("List is not sorted lexicographically.\n");
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
