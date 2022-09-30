#include <stdio.h>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

double calculate_tax(double bands[][3], double monthly_salary)
{
    double running_pay = monthly_salary;
    double running_tax = 0.0;

    for (int i = 0; i < 4; i++)
    {
        if (bands[i][0] >= 0.0)
        {
            bands[i][2] = min(running_pay, bands[i][0]);
        }
        else
        {
            bands[i][2] = running_pay;
        }
        running_pay -= bands[i][2];
        running_tax += bands[i][1] * bands[i][2];
    }

    return running_tax;
}

int main(int argc, char const *argv[])
{
    printf("Enter monthly salary: £");
    double monthly_salary;
    scanf("%lf", &monthly_salary);

    if (monthly_salary < 0)
    {
        printf("Please enter a valid monthly salary.\n");
        return 1;
    }

    double income_tax_bands[4][3] =
    {
        {12570.0 / 12,              0.00, 0.00},    // allowances
        {(50270.0 - 12570.0) / 12,  0.20, 0.00},    // basic
        {(150000.0 - 50270.0) / 12, 0.40, 0.00},    // higher
        {-1.0,                      0.45, 0.00}     // above
    };

    double national_insurance_bands[4][3] =
    {
        {1048,  0.00, 0.00},            // primary threshold
        {4189 - 1048,  0.1325, 0.00},   // upper earnings limit
        {-1.0,  0.0325, 0.00}           // above
    };

    double income_tax = calculate_tax(income_tax_bands, monthly_salary);
    double national_insurance_tax = calculate_tax(national_insurance_bands, monthly_salary);
    double total_tax = income_tax + national_insurance_tax;

    printf("Income Tax: £%lf\n", income_tax);
    printf("National Insurance Tax: £%lf\n", national_insurance_tax);
    printf("Total: £%lf\n", total_tax);

    return 0;
}
