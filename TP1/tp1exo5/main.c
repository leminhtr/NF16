#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int question5_1(char* sous_chaine, char* chaine)
{
    int i, j, nombre=0, position[nombre], present=0;

    for(i=0;i<strlen(*chaine);i++)
    {
        for(j=i;strlen(*sous_chaine);j++)
        {
            if (sous_chaine[j]==chaine[j])
                present=1;
            else
                present=0;
        }
        if(present==1)
            {
                nombre++;
                *position=j-strlen(sous_chaine);
            }
        i=j;
    }

}

char question5_2(char chaine[])
{
    int i;
    for(i=0;i<strlen(chaine);i++)
    {
        chaine[i]=chaine[i]-'a'+'A';
        printf("%c", chaine[i]);
    }

    return *chaine;
}

int main()
{
    printf("Hello world!\n");
    char ch[]="bonj";
    question5_2(ch);
    return 0;
}
