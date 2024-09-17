#include <stdio.h>

int main(void) 
{
    // declare variables
    char name[100];
    
    // get inputs
    printf("What's your name? ");
    scanf("%s", &name);
    
    printf("hello, %s\n", name);
}