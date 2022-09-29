#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("Enter monthly salary in pence: ");
    int monthly_salary;
    scanf("%d", &monthly_salary);

    const int PERIODS_IN_YEAR = 12;
    const int PERSONAL_ALLOWANCE = 1257000;

    if (monthly_salary < 0)
    {
        printf("Please enter a valid monthly salary.\n");
        return 1;
    }

    double income_tax_band_allowances_rate = 0.0;
    double income_tax_band_basic_rate = 0.2;
    double income_tax_band_higher_rate = 0.4;
    double income_tax_band_above_rate = 0.5;

    int income_tax_band_allowances_ceiling = PERSONAL_ALLOWANCE/PERIODS_IN_YEAR;
    int income_tax_band_basic_ceiling = (5027000-PERSONAL_ALLOWANCE)/PERIODS_IN_YEAR;
    int income_tax_band_higher_ceiling = (15000000-50271)/PERIODS_IN_YEAR;
    int income_tax_band_above_ceiling = ()/PERIODS_IN_YEAR;
    return 0;
}
