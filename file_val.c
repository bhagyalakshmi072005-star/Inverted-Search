#include "inv.h"

int file_validation(char *argv[],S_list **head)
{
    int i=1;
    while(argv[i]!=NULL){
        char *ext=strrchr(argv[i],'.');
        if(ext==NULL||strcmp(ext,".txt")!=0){
            printf("INFO: %s is not a .txt file.\n",argv[i]);
            i++;
            continue;
        }
        FILE *fp=fopen(argv[i],"r");
        if(fp==NULL){
            printf("INFO: %s file does not exist.\n",argv[i]);
            i++;
            continue;
        }
        fseek(fp,0,SEEK_END);
        if(ftell(fp)==0){
            printf("INFO: %s file is empty.\n",argv[i]);
            fclose(fp);
            i++;
            continue;
        }
        fclose(fp);

        S_list *temp=*head;
        S_list *prev=NULL;
        int dup=0;
        while(temp!=NULL){
            if(strcmp(temp->filename,argv[i])==0){
                printf("INFO: %s is a duplicate file.\n",argv[i]);
                dup=1;
                break;
            }
            prev=temp;
            temp=temp->link;
        }
        if(dup==1){
            i++;
            continue;
        }
        S_list *new=malloc(sizeof(S_list));
        if(new==NULL){
            return 1;
        }
        strcpy(new->filename,argv[i]);
        new->link=NULL;
        if(*head==NULL){
            *head=new;
        }else{
            prev->link=new;
        }

        i++;
    }
    return 0;
}