#include "inv.h"

int search_db(mainnode_t *arr[])
{
    char word[WORD_SIZE];
    printf("Enter the word to search: ");
    scanf("%s",word);
    int index;
    if(word[0]>='a'&&word[0]<='z'){
        index=word[0]-'a';
    }else if(word[0]>='A'&&word[0]<='Z'){
        index=word[0]-'A';
    }else{
        index=26;
    }
    if(arr[index]==NULL){
        printf("ERROR: Word '%s' is not present in the database.\n",word);
        return 1;
    }
    mainnode_t *m_temp=arr[index];
    while(m_temp!=NULL){
        if(strcmp(m_temp->word,word)==0){
            printf("Word %s is present in %d file(s)\n",m_temp->word,m_temp->file_count);
            subnode_t *s_temp=m_temp->sublink;
            while(s_temp!=NULL){
                printf("In %s -> %d time(s)\n",s_temp->filename,s_temp->word_count);
                s_temp=s_temp->link;
            }
            return 0;
        }
        m_temp=m_temp->link;
    }
    printf("ERROR: Word '%s' is not present in the database.\n",word);
    return 1;
}