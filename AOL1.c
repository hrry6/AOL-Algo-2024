#include <stdio.h>
#include <string.h>

int main()
{
    char character[100] = "Test";
    
    scanf("%[^\n]", character);
    
    for(int i = (strlen(character) - 1); i >=0 ; i--)
    {
        if(character[i] >= 65 && character[i] <= 90) printf("%c", character[i] + 32);            
        else if(character[i] >= 97 && character[i] <= 122) printf("%c", character[i] - 32);
        else printf("%c", character[i]);
    }
    printf("\n");

    return 0;
}