#include<stdio.h>
#include<string.h>
int main()
{
    char s[100];
    int n;
    printf("Enter string: ");
    scanf("%s",s);
    n=strlen(s);
    if(s[0]=='0' && s[n-1]=='1')
        printf("Accepted");
    else
        printf("Rejected");
    return 0;
}
