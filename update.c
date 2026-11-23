#include "inv.h"

static void remove_file_from_list(S_list **head, const char *fname)
{
    S_list *curr = *head, *prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->filename, fname) == 0) {
            if (prev == NULL)
                *head = curr->link;
            else
                prev->link = curr->link;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->link;
    }
}

int update_db(S_list **head, mainnode_t *arr[])
{
    char bname[FNAME_SIZE];
    printf("Enter the backup filename: ");
    scanf("%s", bname);

    char *ext = strrchr(bname, '.');
    if (ext == NULL || strcmp(ext, ".txt") != 0) {
        printf("ERROR: %s is not a .txt file.\n", bname);
        return 1;
    }

    FILE *fp = fopen(bname, "r");
    if (fp == NULL) {
        printf("ERROR: %s does not exist or cannot be opened.\n", bname);
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    if (fsize < 2) {
        printf("ERROR: %s is empty or invalid backup file.\n", bname);
        fclose(fp);
        return 1;
    }

    rewind(fp);
    int first_ch = fgetc(fp);
    fseek(fp, -1, SEEK_END);
    int last_ch = fgetc(fp);
    while (last_ch == '\n' || last_ch == '\r') {
        if (ftell(fp) <= 1) break;
        fseek(fp, -2, SEEK_CUR);
        last_ch = fgetc(fp);
    }

    if (first_ch != '#' || last_ch != '#') {
        printf("ERROR: %s is not a valid backup file (missing '#' delimiters).\n", bname);
        fclose(fp);
        return 1;
    }

    rewind(fp);
    int index, file_count;
    char word[WORD_SIZE];

    while (fscanf(fp, "#%d;%[^;];%d;", &index, word, &file_count) == 3) {
        if (index < 0 || index >= 27) {
            fclose(fp);
            return 1;
        }

        mainnode_t *mnew = malloc(sizeof(mainnode_t));
        if (mnew == NULL) {
            fclose(fp);
            return 1;
        }
        strcpy(mnew->word, word);
        mnew->file_count = file_count;
        mnew->sublink = NULL;
        mnew->link = NULL;

        subnode_t *s_head = NULL, *s_tail = NULL;
        for (int i = 0; i < file_count; i++) {
            char fname[FNAME_SIZE];
            int w_count;
            if (fscanf(fp, "%[^;];%d;", fname, &w_count) != 2) {
                fclose(fp);
                return 1;
            }
            subnode_t *snew = malloc(sizeof(subnode_t));
            if (snew == NULL) {
                fclose(fp);
                return 1;
            }
            strcpy(snew->filename, fname);
            snew->word_count = w_count;
            snew->link = NULL;

            if (s_head == NULL)
                s_head = s_tail = snew;
            else {
                s_tail->link = snew;
                s_tail = snew;
            }
            remove_file_from_list(head, fname);
        }

        mnew->sublink = s_head;
        fscanf(fp, "#\n");

        if (arr[index] == NULL) {
            arr[index] = mnew;
        } else {
            mainnode_t *mtemp = arr[index];
            while (mtemp->link != NULL)
                mtemp = mtemp->link;
            mtemp->link = mnew;
        }
    }

    fclose(fp);
    printf("INFO: Database updated from %s successfully.\n", bname);
    return 0;
}