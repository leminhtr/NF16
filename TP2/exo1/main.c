#include <stdio.h>
#include <stdlib.h>
#define NMAX 4

//1.1
int factIter(int n)
{
    int fact=1;
    while (n>1)
    {
            fact=fact*n;
            n--;
    }
    return fact;
}
//1.2
int factRecur(int n)
{
    if(n==0||n==1)
        return 1;
    return(n*factRecur(n-1));
}

//1.3

int extraire(int **tab, int taille, int ligne)
{
    int a,b,i;
    int **sous_mat=malloc(sizeof(int*)*(taille-2));
    for(i=0;i<taille;i++)
        sous_mat[i]=malloc(sizeof(int)*(taille-2));
    for(a=0;a<taille;a++)
    {
        for(b=1;b<taille-1;b++)
        {
            if(a!=ligne)
                sous_mat[a][b]=tab[a][b];
        }
    }
    return sous_mat;
}

int deter(int **mat, int n)
{
    int det=0,i=0;
    for(i=0;i<n;i++)
    {
        if (n==1)
            return mat[0][0];
        else if(i%2==0)
        {
            det=det+mat[i][0]*deter((extraire(mat,n,i)),n-1);
        }
        else
        {
            det=det-mat[i][0]*deter((extraire(mat,n,i)),n-1);
        }
    }
    return det;
}

int main()
{
    int i,j,det;

    int **matrice=malloc(sizeof(int*)*(NMAX-1));
    for(i=0;i<NMAX;i++)
        matrice[i]=malloc(sizeof(int)*(NMAX-1));
    for(i=0;i<NMAX;i++)
    {
        for(j=0;j<NMAX;j++)
            scanf("%d",&matrice[i][j]);
    }
    det=deter(matrice,NMAX);
    printf("%d",det);
    return 0;
}
