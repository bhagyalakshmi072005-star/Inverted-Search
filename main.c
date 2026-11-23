#include "inv.h"

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        printf("INFO: Insufficient arguments.\n");
        printf("Usage: ./inv <file1.txt> <file2.txt> ...\n");
        return 1;
    }
    S_list *head = NULL;
    file_validation(argv, &head);
    mainnode_t *arr[27] = {NULL};
    int choice, created = 0, updated = 0;

    while (1) {
        printf("\n1. Create\n2. Display\n3. Search\n4. Save\n5. Update\n6. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1:
                if (created == 0) {
                    if (create_db(head, arr) == 0)
                        created = 1;
                } else {
                    printf("ERROR: Database is already created.\n");
                }
                break;
            case 2:
                display_db(arr);
                break;
            case 3:
                search_db(arr);
                break;
            case 4:
                save_db(arr);
                break;
            case 5:
                if (created == 0 && updated == 0) {
                    if (update_db(&head, arr) == 0)
                        updated = 1;
                } else {
                    printf("ERROR: Update database is not allowed now.\n");
                }
                break;
            case 6:
                return 0;
            default:
                printf("ERROR: Invalid choice.\n");
        }
    }
    return 0;
}