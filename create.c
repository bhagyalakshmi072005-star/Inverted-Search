#include "inv.h"

int create_db(S_list *head,mainnode_t *arr[])
{
    S_list *temp=head;
    char word[WORD_SIZE];
    while(temp!=NULL){
        FILE *fp=fopen(temp->filename,"r");
        if(fp==NULL){
            temp=temp->link;
            continue;
        }
        while(fscanf(fp,"%s",word)!=EOF){
            int index;
            if(word[0]>='a'&&word[0]<='z'){
                index=word[0]-'a';
            }else if(word[0]>='A'&&word[0]<='Z'){
                index=word[0]-'A';
            }else{
                index=26;
            }

            if(arr[index]==NULL){
                mainnode_t *mnew=malloc(sizeof(mainnode_t));
                subnode_t *snew=malloc(sizeof(subnode_t));
                if(mnew==NULL||snew==NULL){
                    return 1;
                }
                strcpy(mnew->word,word);
                mnew->file_count=1;
                mnew->link=NULL;
                strcpy(snew->filename,temp->filename);
                snew->word_count=1;
                snew->link=NULL;
                mnew->sublink=snew;
                arr[index]=mnew;
            }else{
                mainnode_t *mtemp=arr[index];
                mainnode_t *mprev=NULL;
                int word_found=0;
                while(mtemp!=NULL){
                    if(strcmp(mtemp->word,word)==0){
                        word_found=1;
                        subnode_t *stemp=mtemp->sublink;
                        subnode_t *sprev=NULL;
                        int file_found=0;
                        while(stemp!=NULL){
                            if(strcmp(stemp->filename,temp->filename)==0){
                                stemp->word_count++;
                                file_found=1;
                                break;
                            }
                            sprev=stemp;
                            stemp=stemp->link;
                        }
                        if(file_found==0){
                            subnode_t *snew=malloc(sizeof(subnode_t));
                            if(snew==NULL){
                                return 1;
                            }
                            strcpy(snew->filename,temp->filename);
                            snew->word_count=1;
                            snew->link=NULL;
                            sprev->link=snew;
                            mtemp->file_count++;
                        }
                        break;
                    }
                    mprev=mtemp;
                    mtemp=mtemp->link;
                }
                if(word_found==0){
                    mainnode_t *mnew=malloc(sizeof(mainnode_t));
                    subnode_t *snew=malloc(sizeof(subnode_t));
                    if(mnew==NULL||snew==NULL){
                        return 1;
                    }
                    strcpy(mnew->word,word);
                    mnew->file_count=1;
                    mnew->link=NULL;
                    strcpy(snew->filename,temp->filename);
                    snew->word_count=1;
                    snew->link=NULL;
                    mnew->sublink=snew;
                    mprev->link=mnew;
                }
            }

        }
        fclose(fp);
        temp=temp->link;
    }
    return 0;
}