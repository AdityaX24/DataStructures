//Code by Aditya Poddar
//SRN PES2UG21CS036
//for any help, contact: poddar.aditya2014@gmail.com

#include<stdio.h>
#include<stdlib.h>
#define MAX 100     //can be changed according to user needs
//The program takes 0 as the first node.

void init(int adj_mat[MAX][MAX],int vertices)   //to initialize the adjacentcy matrix representing the graph
{
    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            adj_mat[i][j]=0;
        }
    }
}

void create_graph(int a[MAX][MAX],int n)       //to take graph input
{
    int i,j;
    while(1)
    {
        printf("\n Enter two connected vertices. Enter -1 -1 to exit: \n");     //take vertices as input till the user inputs -1 -1
        scanf("%d %d",&i,&j);
        if(i==-1 && j==-1)
        {
            return;
        }
        else if(i>= n || j>=n)
        {
            printf("\n Incorrect vertex input. Please try again!.. \n");
        }
        else
        {
            a[i][j]=1;                  //the graph is undirected unwighted graph
            a[j][i]=1;
        }
    }
}

void print_adj_mat(int a[MAX][MAX],int n)       //to print the matrix representation of the graph
{
    if(n==0)                                    //if the graph has not been initialized yet
    {
        printf("\n Initialize the graph and try again! \n");
        return;
    }
    else                                        //if the graph has been initialized, printing the matrix representation
    {
        for(int i=0;i<n;i++)                    
        {
            for(int j=0;j<n;j++)
            {
                printf("%d ",a[i][j]);
            }
            printf("\n");
        }
    }    
}

void init_visited(int *v,int n)             //initializing the visited array with all values as 0
{   
    for(int i=0;i<n;i++)
    {
        v[i]=0;
    }
}


//Depth First Search explores a graph by visiting nodes and following edges until it reaches a dead end,
//and then backtracking to explore other branches of the graph. It can be done in both recursive and non-recursive(using stack) way.
void dfs(int a[MAX][MAX],int *v,int n,int s)        //Depth First Traversal in a recursive way
{
    printf("%d ",s);    //print the source element
    v[s]=1;             //mark the last node as visited in the visited array
    for(int i=0;i<n;i++)    //traverse through all the nodes
    {
        if(a[s][i]==1 && v[i]==0)   //check for all the nodes having an edge from the source and if that node has previously been visited
        {
            dfs(a,v,n,i);       //if the new node has not been visited yet, call dfs recursively with the new node as the source node
        }
    }
}


//Breadth First Search explores a graph by visiting all the vertices of a given graph in breadth-first order, 
//meaning it explores all the vertices at the same level before moving to the next level.
void bfs(int a[MAX][MAX],int *v,int n,int s)    //Breath First Search
{
    int x;
    v[s]=1;                             //mark the source node as visited
    printf("%d ",s);                    //print the source node
    int qu[100];                        //using queue 
    int f=0,r=-1;
    qu[++r]=s;                          //enque source node
    while(f<=r)                         //repeat untill the queue is empty
    {
        x=qu[f++];                      //dequeue element from the queue
        for(int i=0;i<n;i++)            //loop throough all the nodes and find all nodes on the same level(connected to last dequeued node)
        {
            if(a[x][i]==1 && v[i]==0)   //find nodes having an edge from last dequeued node and check of its not visited
            {
                v[i]=1;                 //if its not visited then visit it
                printf("%d ",i);        //print the node
                qu[++r]=i;              //add the node to the queue to take out in order, next time
            }
        }
    }
}

void dfs_connected(int a[MAX][MAX],int *v,int n,int s)      //similar to dfs without the print statement. Helper function for connected_check and count_connected_grpah
{
    v[s]=1;                                 //mark source node as visited
    for(int i=0;i<n;i++)
    {
        if(a[s][i]==1 && v[i]==0)
        {
            dfs_connected(a,v,n,i);         //visit the nodes connected to source node in dfs recursive manner
        }
    }
}

int connected_check(int a[MAX][MAX],int *v,int n)       //checks if a grpah is connected or not
{
    if(n==0)                                            //if the graph is not initialized
    {
        printf("\n Initialize the graph first!.. \n");
        return -2;
    }
    int source=0;                       //taking the default source node as 0. Can be changed.
    v[source]=1;
    dfs_connected(a,v,n,source);        //perform dfs with 0 as source and get the relative visited array
    for(int i=0;i<n;i++)                //iterate through the visited array
    {
        if(v[i]==0)                     //if any node is not vivited
        {
            return -1;                  //return not connected
        }
    }
    return 1;                           //if all nodes as visited, then return connected
}

int count_unconnected_graph(int a[MAX][MAX],int *v,int n)       //counts the number of unconnected graphs
{
    if(n==0)                                                    //if the graph is not initialized
    {
        printf("\n Initialize the graph first!.. \n");
        return -2;
    }
    int count=1;                                                //as minimun there will be 1 graph,i.e. 1 connected graph
    dfs_connected(a,v,n,0);                                     //traverse the graph by dfs to update the visited array
    for(int i=0;i<n;i++)                                        //iterate through the visited array
    {
        if(v[i]==0)                                             //if any node is not visited
        {
            count++;                                            //increase the number of unconnected graph
            dfs_connected(a,v,n,i);                             //again iterate through the next disconencted graph using dfs(can be done using BFS also)
        }
    }
    return count;
}

void find_all_paths(int a[MAX][MAX],int *v,int n,int s,int d,int *qu,int *c,int *r)     //finds all paths from source to destination in a given graph
{
    qu[(*r)++]=s;       //enque the source node
    v[s]=1;             //mark the node as visited
    if(s==d)            //if the source in the particular call is the destination, then print the nodes in the queue, which is the path
    {
        (*c)++;
        for(int i=0;i<(*r)-1;i++)                   //loop till rear-1 to print all nodes on the path
        {
            printf("%d --> ",qu[i]); 
        }
        printf("%d\n",qu[((*r)-1)]);
    }
    else                                            //if destination is not reached
    {
        for(int i=0;i<n;i++)                        //iterate throught the nodes connected to the source node(similar to dfs)
        {
            if(a[s][i]==1 && v[i]==0)               //visit the connected node in a recursive way
            {   
                find_all_paths(a,v,n,i,d,qu,c,r);
            }
        }
    }
    v[s]=0;                                         //make the source node in the particular iteration as non viisted ( to find other paths via the same node)
    (*r)--;                                         //remove the node from the queue of nodes
}

int main()          //main program to use all functions
{
    int count=0,x;
    int source=0;
    int choice,vertices=0;
    int visited[MAX];
    int adj_mat[MAX][MAX];
    do
    {
        printf("\n Enter : 1.Input new graph 2.Print graph Adjacentcy Matrix 3.DFS Traversal 4.BFS Traversal \n");
        printf("5.Connected check 6.Count unconnected graphs 7.Find all paths 8.Exit :: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("\n Enter number of vertices: ");
                scanf("%d",&vertices);
                init(adj_mat,vertices);
                create_graph(adj_mat,vertices);
                break;

            case 2:print_adj_mat(adj_mat,vertices);
                break;

            case 3:init_visited(visited,vertices);
                printf("\n Enter source node: ");
                scanf("%d",&source);
                if(source>=vertices)
                {
                    printf("\n Source node not present in graph! Try agian..\n ");
                }
                else
                {
                    printf("\n The DFS traversal of the graph is: ");
                    dfs(adj_mat,visited,vertices,source);
                }
                break;

            case 4:init_visited(visited,vertices);
                printf("\n Enter source node: ");
                scanf("%d",&source);
                if(source>=vertices)
                {
                    printf("\n Source node not present in graph! Try agian..\n");
                }
                else
                {
                    printf("\n The BFS traversal of the graph is: ");
                    bfs(adj_mat,visited,vertices,source);
                }
                break;

            case 5:init_visited(visited,vertices);
                x=connected_check(adj_mat,visited,vertices);
                if(x==-1)
                {
                    printf("\n The graph is not connected! \n");
                }
                else if(x==1)
                {
                    printf("\n The graph is connected! \n");
                }
                break;

            case 6:init_visited(visited,vertices);
                count=count_unconnected_graph(adj_mat,visited,vertices);
                if(count==1)
                {
                    printf("\n Only 1 connectd graphg is present! \n");
                }
                else
                {
                    printf("\n %d unconnected graphs are present! \n",count);
                }
                break;

            case 7:if(vertices==0)
                {
                    printf("\n Initialize the graph first!..\n");
                    break;
                }
                else
                {
                    init_visited(visited,vertices);
                    int s,d;
                    printf("\n Enter source and destination: \n");
                    scanf("%d %d",&s,&d);
                    int qu[100];
                    int c=0,r=0;
                    find_all_paths(adj_mat,visited,vertices,s,d,qu,&c,&r);
                    printf("\n There are total %d paths from source to destination!.. \n ",c);
                    break;
                }

                case 8:printf("\n EXITING... \n");
                break;

            default: printf("\n Wrong input.Please try again!.. \n");
                break;
        }
    }while(choice!=8);

    return 1;
}