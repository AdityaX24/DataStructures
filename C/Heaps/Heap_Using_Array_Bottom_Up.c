//Code by Aditya Poddar
//SRN PES2UG21CS036
//for any help, contact: poddar.aditya2014@gmail.com

#include<stdio.h>
#include<stdlib.h>
#define MAX 100     //maximun elements in the heap. Can be changed according to user need


void init(int *heap)    //To initialize first position of heap to 0
{
    heap[0]=0;
}

void create_array(int *array,int n)     //To take input of array from the user
{
    int data;
    for(int i=1;i<n+1;i++)
    {
        printf("\nEnter element %d: ",i);
        scanf("%d",&data);
        array[i]=data;
    }
}

void heapify(int *heap,int n)           //To heapify the array containig the elements
{
    int heaped,k,j,v;       //heaped is a counter to check if the subtree at pos k is already a heap
    for(int i=n/2;i>0;i--)      //To heapify all subtress starting from first parent(i.e n/2) to root(i.e 1)
    {
        k=i;                //parent node
        heaped=0;   
        v=heap[k];          //value at parent node
        while(!heaped && 2*k<=n)        //while the subtree is not completely heapifed or we reach leaf node
        {
            j=2*k;          //j is the left child of the parent k
            if(j<n)         //if there exists a right child 
            {
                if(heap[j+1]>heap[j])   //check if right child node has greater value
                {
                    j=j+1;              //if right child has greater value, then make it as child
                }   
            }
            if(v>heap[j])           //if the parent has higher value (parental dominance property) then subtree is heapified
            {   
                heaped=1;           //make heap counter is 1(heapified)
            }
            else        //if subtree is not heapified
            {
                heap[k]=heap[j];        //copy the child element data to parent node
                k=j;                    //make child as the new parent node and repeat the loop
            }
        }
        heap[k]=v;      
    }
}

void display(int *heap,int n)
{
    if(n==0)        //if no elements are in the array
    {
        printf("\n Please enter the elemets first!\n");
        return;
    }
    printf("\n");
    for(int i=1;i<n+1;i++)          //Display all elements of the heap in order
    {
        printf("%d ",heap[i]);
    }
    printf("\n");
}

int main()
{
    int heap_array[MAX];
    int n=0,choice,data;
    do
    {
        printf("\n Enter\n 1.Add Elements to array\n 2.Display Heap\n 3.Exit : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:init(heap_array);
                   printf("\n Enter number of element to be inserted into heap: ");
                   scanf("%d",&n);
                   create_array(heap_array,n);
                   heapify(heap_array,n);
                   break;

            case 2:display(heap_array,n);
                   break;

            case 3:printf("\n THANK YOU. EXITING..\n");
                   break;

            default:printf("\n Invalid choice. Please try again! \n");
                    break;
        }

    } while(choice!=3);
}