#include <string.h>  // strpbrk
#include <stdio.h>   // printf

char    *ft_strpbrk(const char *s1, const char *s2)
{
    int    i;

    while (*s1)
    {
        i = 0;
        while (s2[i])
        {
            if (*s1 == s2[i])
                return ((char *)s1);
            i++;
        }
        s1++;
    }
    return (NULL);
}

int    main(void)
{
    char *result;

    result = ft_strpbrk("42", "21");
    printf("%s\t   VS\t    %s\n", result ? result : "NULL", strpbrk("42", "21"));
    result = ft_strpbrk("42", "7");
    printf("%s\t   VS\t    %s\n", result ? result : "NULL", strpbrk("42", "7") ? strpbrk("42", "7") : "NULL");
    result = ft_strpbrk("Hello w", "wo");
    printf("%s\t   VS\t    %s\n", result ? result : "NULL", strpbrk("Hello w", "wo"));
    return (0);
}
