#include<stdio.h>
#include<limits.h>

struct Node{
    int distance[20];
    int pathNode[20];
}nodes[20];

int n;


void getLinks(){
    int l,s,d,c;
    printf("Enter no. of links: ");
    scanf("%d",&l);
    for(int i = 0; i < l ; i++){
        printf("Enter source, destination, cost #%d\n ,(0-%d)",i+1,n-1);
        scanf("%d",&s);
        scanf("%d",&d);
        scanf("%d",&c);
        nodes[s].distance[d] = c;
        nodes[s].pathNode[d] = d;
        nodes[d].distance[s] = c;
        nodes[d].pathNode[s] = s;
    }
}

void calcDVR(){
    int change;
    while(1){
        change = 0;
        for(int i = 0; i < n ; i++){
            for(int j = 0; j < n ; j++){
                if(i == j){
                    nodes[i].distance[j] = 0;
                    nodes[i].pathNode[j] = i;
                    continue;
                }
                for(int k = 0; k < n ; k++){
                    if(nodes[i].distance[j] > nodes[i].distance[k] + nodes[k].distance[j]){
                        change = 1;
                        nodes[i].distance[j] = nodes[i].distance[k] + nodes[k].distance[j];
                        nodes[i].pathNode[j] = k;
                    }
                }
            }
        }
        if (change == 0){
            printf("All distances found");
            break;
        }
    }
}

void displayPaths(){
    for(int i = 0; i < n; i++){
        for(int j = 0;j < n; j++){
            printf("%d to %d, cost: %d through %d\n",i,j,nodes[i].distance[j],nodes[i].pathNode[j]);
        }
    }
}

int main(){
    printf("Enter no. of nodes: ");
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        for(int j = 0;j < n; j++){
            nodes[i].distance[j] = 9999999;
        }
    }
    getLinks();
    calcDVR();
    displayPaths();
    return 0;
}