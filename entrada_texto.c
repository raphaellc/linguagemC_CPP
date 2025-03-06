#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{
    const int MAX_LEN = 100;
    char ch;
    char s[100];
    char sen[MAX_LEN];
    
    scanf("%c", &ch);
    scanf("%s", &s);
    scanf("\n");
    scanf("%[^\n]%*c", &sen);
    
    printf("%c \n", ch);
    printf("%s \n", s);
    printf("%s \n", sen);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}