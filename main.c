#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("Enter monthly salary in pence: ");
    int monthly_salary;
    scanf("%d", &monthly_salary);

    if (monthly_salary < 0)
    {
        printf("Please enter a valid monthly salary.\n");
        return 1;
    }
    return 0;
}
