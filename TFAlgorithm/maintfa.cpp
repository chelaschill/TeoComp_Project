//
// Created by Jorge on 6/25/2020.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int **TransitionMap;
int **newTransitionMap;
int EstadoInicial;
long int Alcanzable;
long int Estados;
long int EstadosFinales;
long int no_EstadosFinales;
long int *P;

void dfs(int ini)
{
    Alcanzable |= (1 << ini);

    for(int i=0; i<26; i++)
        if((TransitionMap[ini][i] != -1) && ((Alcanzable & (1 << TransitionMap[ini][i])) == 0))
        {
            dfs(TransitionMap[ini][i]);
        }
}


int main(){

    printf("%s\n", "Ingresa el ADF:");

    EstadosFinales = 0;
    Estados = 0;

    TransitionMap = (int**)malloc(64*sizeof(int*));
    for (int i = 0; i < 64; i++){
        TransitionMap[i] = (int*) malloc(26*sizeof(int));
        for (int j = 0; j < 26; j++){
            TransitionMap[i][j] = -1;
        }
    }

    newTransitionMap = (int**)malloc(64*sizeof(int*));
    for (int i = 0; i < 64; i++){
        newTransitionMap[i] = (int*) malloc(26*sizeof(int));
        for (int j = 0; j < 26; j++){
            newTransitionMap[i][j] = -1;
        }
    }

    char buff[125];
    fgets(buff, sizeof(buff), stdin);
    char *p = strtok(buff, " ");
    EstadoInicial = atoi(p);

    fgets(buff, sizeof(buff), stdin);
    p = strtok(buff, " ");
    while (p != NULL)
    {
        int state = atoi(p);
        EstadosFinales |= 1 << (state);
        p = strtok(NULL, " ");
    }

    int from;
    char symbol;
    int to;
    while (fscanf(stdin, "%d %c %d", &from, &symbol, &to) != EOF) {
        TransitionMap[from][symbol] = to;

        Estados |= (1 << from);
        Estados |= (1 << to);
    }

    Alcanzable = 0;
    dfs(EstadoInicial);

    Estados &= Alcanzable;
    EstadosFinales &= Alcanzable;

    P =  (long int*) malloc(64*sizeof(long int));
    for (int i = 0; i < 64 ; i++){
        P[i] = 0;
    }

    no_EstadosFinales = Estados & ~EstadosFinales;
    P[0] = EstadosFinales;
    P[1] = no_EstadosFinales;

    printf("\n%s\n", "<-- AFD Minimizado -->");

    int startPartition = 0;
    for (int i = 0; i < ; i ++){
        if ((P[i] & (1 << EstadoInicial)) != 0 ){
            startPartition = i;
            break;
        }
    }

    printf("%d \n", startPartition);

    for (int i = 0; i < ; i++){
        if ((P[i] & EstadosFinales) != 0){
            printf("%d ", i);
        }
    }
    printf("\n");

    for (int i = 0; i < ; i++){
        for (int j = 0; j <; j++) {
            if (newTransitionMap[i][j] != -1){
                for (int k = 0; k < ; k++){
                    if ((P[k] & (1 << newTransitionMap[i][j])) != 0){
                        printf("%d %c %d\n", i, j, k);
                    }
                }
            }
        }
    }

    return 0;

}
