#include<stdio.h>
#include<string.h>
int main()
{
    char s[100];
    int i,n;
    printf("Enter string: ");
    scanf("%s",s);
    n=strlen(s);
    if(n>=2 && s[0]=='0' && s[n-1]=='1')
    {
        for(i=1;i<n-1;i++)
        {
            if(s[i]!='0' && s[i]!='1')
                break;
        }
        if(i==n-1)
            printf("Accepted");
        else
            printf("Rejected");
    }
    else
        printf("Rejected");
    return 0;
}
