#include <stdio.h>

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main(int argc, char const *argv[])
{
    printf("Enter monthly salary in pence: ");
    double monthly_salary;
    scanf("%f", &monthly_salary);

    const int PERIODS_IN_YEAR = 12;
    const int PERSONAL_ALLOWANCE = 12570;

    if (monthly_salary < 0)
    {
        printf("Please enter a valid monthly salary.\n");
        return 1;
    }

    // Income Tax Band

    double bands[4][3] =
    {
        {12570.0 / 12,              0.00, 0.00}, // allowances
        {(50270.0 - 12570.0) / 12,  0.20, 0.00}, // basic
        {(150000.0 - 50270.0) / 12, 0.40, 0.00}, // higher
        {-1.0,                      0.45, 0.00} // above
    };

    double running_pay = monthly_salary;
    double running_income_tax = 0.0;

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
        running_income_tax += bands[i][1] * bands[i][2];
    }






    double income_allowances_rate = 0.0;
    double income_basic_rate = 0.2;
    double income_higher_rate = 0.4;
    double income_above_rate = 0.5;

    double income_allowances_ceiling = PERSONAL_ALLOWANCE / PERIODS_IN_YEAR;
    double income_basic_ceiling = (50270-PERSONAL_ALLOWANCE) / PERIODS_IN_YEAR;
    double income_higher_ceiling = (150000 - 50271) / PERIODS_IN_YEAR;

    double income_allowances_subject_to_tax = min(income_allowances_ceiling, monthly_salary);
    double income_basic_subject_to_tax = min(income_basic_ceiling, (monthly_salary - income_allowances_subject_to_tax));
    double income_higher_subject_to_tax = min(income_higher_ceiling, (monthly_salary - income_allowances_subject_to_tax - income_basic_subject_to_tax));
    double income_above_subject_to_tax = max(0, monthly_salary - income_allowances_subject_to_tax - income_basic_subject_to_tax - income_higher_subject_to_tax);

    double income_allowances_tax_payable = income_allowances_rate * income_allowances_subject_to_tax;
    double income_basic_tax_payable = income_basic_rate * income_basic_subject_to_tax;
    double income_higher_tax_payable = income_higher_rate * income_higher_subject_to_tax;
    double income_above_tax_payable = income_above_rate * income_above_subject_to_tax;

    double income_total_payable = income_allowances_tax_payable + income_basic_tax_payable + income_higher_tax_payable + income_above_tax_payable;

    // National Insurance Tax Band

    double national_insurance_primary_threshold_rate = 0.0;
    double national_insurance_upper_earnings_limit_rate = 0.1325;
    double national_insurance_above_rate = 0.0325;

    double national_insurance_primary_threshold_width = 1048;
    double national_insurance_upper_earnings_limit_width = 4189;

    double national_insurance_primary_threshold_subject_to_tax = min(national_insurance_primary_threshold_width, monthly_salary);
    double national_insurance_upper_earnings_limit_subject_to_tax = min(national_insurance_upper_earnings_limit_width, (monthly_salary - national_insurance_primary_threshold_subject_to_tax));
    double national_insurance_above_subject_to_tax = monthly_salary - national_insurance_primary_threshold_subject_to_tax - national_insurance_upper_earnings_limit_subject_to_tax;

    double national_insurance_primary_threshold_tax_payable = national_insurance_primary_threshold_rate * national_insurance_primary_threshold_subject_to_tax;
    double national_insurance_upper_earnings_limit_tax_payable = national_insurance_upper_earnings_limit_rate * national_insurance_upper_earnings_limit_subject_to_tax;
    double national_insurance_above_tax_payable = national_insurance_above_rate * national_insurance_above_subject_to_tax;

    double national_insurance_total_payable = national_insurance_primary_threshold_tax_payable + national_insurance_upper_earnings_limit_tax_payable + national_insurance_above_tax_payable;

    // Grand Total

    double grand_total_payable = income_total_payable + national_insurance_total_payable;

    printf("Income Tax: %fp\n", income_total_payable);
    printf("National Insurance Tax: %fp\n", national_insurance_total_payable);
    printf("Total: £%f\n", grand_total_payable);

    return 0;
}
