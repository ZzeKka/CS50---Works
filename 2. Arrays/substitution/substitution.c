#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_valid_characters(string s);
int check_repeats(string s);
string convert_key_to_lower(string s);
string encrypt(string s, string key);

int main(int argc, string argv[])
{
    // Check if Key is valid
    if (argc != 2)
    {
        printf("Usage: ./substution key\n");
        return 1;
    }
    // Key has right number of args
    string key = argv[1];
    key = convert_key_to_lower(key);
    int length = strlen(key);
    {
        if (length != 26)
        {
            printf("Error 1: Key should contain 26 alphabetic characters\n");
            return 1;
        }
        else if (check_valid_characters(key) == 0)
        {
            printf("Error 2:Key should only contain alphabetic characters\n");
            return 1;
        }
        else if (check_repeats(key) == 0)
        {
            printf("Error 3: Repeated characters in Key\n");
            return 1;
        }
    }
    // Key is valid
    // Substitution
    string message = get_string("plaintext:  ");
    message = encrypt(message, key);
    printf("ciphertext: %s\n", message);
    return 0;
}

// Check for any inavalid characters in Key
int check_valid_characters(string s)
{
    for (int i = 0, length = strlen(s); i < length; ++i)
    {
        if (!isalpha(s[i]))
        {
            return 0;
        }
    }
    return 1;
}

int check_repeats(string s)
{
    for (int i = 0, length = strlen(s); i < length - 1; ++i)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (s[i] == s[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

string convert_key_to_lower(string s)
{
    for (int i = 0, length = strlen(s); i < length; ++i)
    {
        if (isupper(s[i]))
        {
            s[i] = tolower(s[i]);
        }
    }
    return s;
}

string encrypt(string m, string k)
{
    for (int i = 0, length = strlen(m); i < length; ++i)
    {
        if (m[i] >= 'a' && m[i] <= 'z')
        {
            m[i] = tolower(k[m[i] - 'a']);
        }
        else if (m[i] >= 'A' && m[i] <= 'Z')
        {
            m[i] = toupper(k[m[i] - 'A']);
        }
    }
    return m;
}
