#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string s = get_string("Hey human, what's your name?");
    printf("hello, %s\n", s);
}
