#include<stdio.h>
#include<stdlib.h>

struct block
{
    int os;
    int rs;
    struct block *next;
};

void worsefit(struct block *head,int nb,int file[],int nf)
{
    struct block *temp =NULL,*worst = NULL;
    for(int i =0;i<nf;i++)
    {
        while(temp!=NULL)
        {
            if(temp->rs>=file[i])
            {
                if(worst==NULL || temp->rs > worst->rs)
                {
                    worst=temp;
                }
                
            }
            temp=temp->next;
        }
        if(worst!=NULL)
        {
            printf("File %d of size %d is allocated to block of size %d\n",i+1,file[i],worst->rs);
            worst->rs -= file[i];
            worst = NULL;
        }
        else
        {
            printf("File %d of size %d cannot be allocated\n",i+1,file[i]);
        }   
    }
}


void display(struct block *head,int nb)
{
    struct block *temp = head;
    printf("Block\tSize\tRemaining\n");
    for(int i=0;i<nb;i++)
    {
        printf("%d\t%d\t%d\n",i+1,temp->os,temp->rs);
        temp=temp->next;
    }
}
int main()
{
    int i,nf,nb;
    struct block *head = NULL,*temp =NULL;
    printf("Enter the number of blocks:");
    scanf("%d",&nb);
    for(i=0;i<nb;i++)
    {
        struct block* new = (struct block*)malloc(sizeof(struct block));
        printf("Enter the size of block %d:",i+1);
        scanf("%d",&new->os);
        new->rs = new->os;
        new->next = NULL;
        
        if (head == NULL)
        {
            head = new;
        }
        else
        {
            temp->next = new;
        }
        temp = new;
    }

    printf("Enter the number of files:");
    scanf("%d",&nf);
    int file[nf];
    for(i=0;i<nf;i++)
    {
        printf("Enter the size of file %d:",i+1);
        scanf("%d",&file[i]);

    }
    
    worsefit(head,nb,file,nf);
    display(head,nb);
    return 0;

}