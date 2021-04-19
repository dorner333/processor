#include <stdio.h>

int main()
{
int vasia_kakaha = 1000;
int shiza = 0;
    printf("1000");
while(vasia_kakaha > 0)
    {
    printf(" next suka\n");
    scanf("%d", &shiza);
    if(shiza != vasia_kakaha - 7)
        {
            printf("ti cho debil bliat?\n");
            break;
        }
    else vasia_kakaha = vasia_kakaha - 7;
    }
return 0;
}