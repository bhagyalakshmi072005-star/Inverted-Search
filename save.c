#include "inv.h"

int save_db(mainnode_t *arr[])
{
    char fname[FNAME_SIZE];
    printf("Enter the filename to save database: ");
    scanf("%s",fname);
    char *ext=strrchr(fname,'.');
    if(ext==NULL||strcmp(ext,".txt")!=0){
        printf("ERROR: %s is not a .txt file.\n",fname);
        return 1;
    }
    FILE *fp=fopen(fname,"w");
    if(fp==NULL){
        printf("ERROR: Unable to open %s.\n",fname);
        return 1;
    }
    for(int i=0;i<27;i++){
        if(arr[i]!=NULL){
            mainnode_t *m_temp=arr[i];
            while(m_temp!=NULL){
                fprintf(fp,"#%d;%s;%d;",i,m_temp->word,m_temp->file_count);
                subnode_t *s_temp=m_temp->sublink;
                while(s_temp!=NULL){
                    fprintf(fp,"%s;%d;",s_temp->filename,s_temp->word_count);
                    s_temp=s_temp->link;
                }
                fprintf(fp,"#\n");
                m_temp=m_temp->link;
            }
        }
    }
    fclose(fp);
    printf("INFO: Database successfully saved to %s.\n",fname);
    return 0;
}