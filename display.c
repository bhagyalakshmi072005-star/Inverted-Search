#include "inv.h"

int display_db(mainnode_t *arr[])
{
    printf("[Index]\t[Word]\t[File Count]\t[Filename]\t[Word Count]\n");
    for(int i=0;i<27;i++){
        if(arr[i]!=NULL){
            mainnode_t *m_temp=arr[i];
            while(m_temp!=NULL){
                printf("[%d]\t%s\t%d file(s)",i,m_temp->word,m_temp->file_count);
                subnode_t *s_temp=m_temp->sublink;
                while(s_temp!=NULL){
                    printf("\t\t%s\t\t%d",s_temp->filename,s_temp->word_count);
                    s_temp=s_temp->link;
                }
                printf("\n");
                m_temp=m_temp->link;
            }
        }
    }
    return 0;
}