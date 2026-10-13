#include<stdio.h>
#include<string.h>
int main()
{
    char s[100];
    int i,n;
    printf("Enter string: ");
    scanf("%s",s);
    n=strlen(s);
    for(i=0;i<n/2;i++)
    {
        if(s[i]!='0' || s[n-i-1]!='0')
            break;
    }
    for(i=n/2;i<n;i++)
    {
        if(s[i]!='1')
            break;
    }
    if(i==n)
        printf("Accepted");
    else
        printf("Rejected");
    return 0;
}
