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
    int monthly_salary;
    scanf("%d", &monthly_salary);

    const int PERIODS_IN_YEAR = 12;
    const int PERSONAL_ALLOWANCE = 1257000;

    if (monthly_salary < 0)
    {
        printf("Please enter a valid monthly salary.\n");
        return 1;
    }

    // Income Tax Band

    double income_tax_band_allowances_rate = 0.0;
    double income_tax_band_basic_rate = 0.2;
    double income_tax_band_higher_rate = 0.4;
    double income_tax_band_above_rate = 0.5;

    int income_tax_band_allowances_ceiling = PERSONAL_ALLOWANCE / PERIODS_IN_YEAR;
    int income_tax_band_basic_ceiling = (5027000-PERSONAL_ALLOWANCE) / PERIODS_IN_YEAR;
    int income_tax_band_higher_ceiling = (15000000 - 5027100) / PERIODS_IN_YEAR;

    int income_tax_band_allowances_subject_to_tax_in_band = min(income_tax_band_allowances_ceiling, monthly_salary);
    int income_tax_band_basic_subject_to_tax_in_band = min(income_tax_band_basic_ceiling, (monthly_salary - income_tax_band_allowances_subject_to_tax_in_band));
    int income_tax_band_higher_subject_to_tax_in_band = min(income_tax_band_higher_ceiling, (monthly_salary - income_tax_band_allowances_subject_to_tax_in_band - income_tax_band_basic_subject_to_tax_in_band));
    int income_tax_band_above_subject_to_tax_in_band = max(0, monthly_salary - income_tax_band_allowances_subject_to_tax_in_band - income_tax_band_basic_subject_to_tax_in_band - income_tax_band_higher_subject_to_tax_in_band);

    int income_tax_band_allowances_tax_payable_in_band = income_tax_band_allowances_rate * income_tax_band_allowances_subject_to_tax_in_band;
    int income_tax_band_basic_tax_payable_in_band = income_tax_band_basic_rate * income_tax_band_basic_subject_to_tax_in_band;
    int income_tax_band_higher_tax_payable_in_band = income_tax_band_higher_rate * income_tax_band_higher_subject_to_tax_in_band;
    int income_tax_band_above_tax_payable_in_band = income_tax_band_above_rate * income_tax_band_above_subject_to_tax_in_band;

    int income_tax_band_total_payable = income_tax_band_allowances_tax_payable_in_band + income_tax_band_basic_tax_payable_in_band + income_tax_band_higher_tax_payable_in_band + income_tax_band_above_tax_payable_in_band;

    // National Insurance Tax Band

    double national_insurance_tax_band_primary_threshold_rate = 0.0;
    double national_insurance_tax_band_upper_earnings_limit_rate = 0.1325;
    double national_insurance_tax_band_above_rate = 0.0325;

    int national_insurance_tax_band_primary_threshold_width = 104800;
    int national_insurance_tax_band_upper_earnings_limit_width = 418900;

    int national_insurance_tax_band_primary_threshold_subject_to_tax_in_band = min(national_insurance_tax_band_primary_threshold_width, monthly_salary);
    int national_insurance_tax_band_upper_earnings_limit_subject_to_tax_in_band = min(national_insurance_tax_band_upper_earnings_limit_width, (monthly_salary - national_insurance_tax_band_primary_threshold_subject_to_tax_in_band));
    int national_insurance_tax_band_above_subject_to_tax_in_band = monthly_salary - national_insurance_tax_band_primary_threshold_subject_to_tax_in_band - national_insurance_tax_band_upper_earnings_limit_subject_to_tax_in_band;

    int national_insurance_tax_band_primary_threshold_tax_payable_in_band = national_insurance_tax_band_primary_threshold_rate * national_insurance_tax_band_primary_threshold_subject_to_tax_in_band;
    int national_insurance_tax_band_upper_earnings_limit_tax_payable_in_band = national_insurance_tax_band_upper_earnings_limit_rate * national_insurance_tax_band_upper_earnings_limit_subject_to_tax_in_band;
    int national_insurance_tax_band_above_tax_payable_in_band = national_insurance_tax_band_above_rate * national_insurance_tax_band_above_subject_to_tax_in_band;

    int national_insurance_tax_band_total_payable = national_insurance_tax_band_primary_threshold_tax_payable_in_band + national_insurance_tax_band_upper_earnings_limit_tax_payable_in_band + national_insurance_tax_band_above_tax_payable_in_band;

    // Grand Total

    int grand_total_payable_pence = income_tax_band_total_payable + national_insurance_tax_band_total_payable;
    int grand_total_payable_pounds = grand_total_payable_pence / 100;

    printf("Income Tax: %dp\n", income_tax_band_total_payable);
    printf("National Insurance Tax: %dp\n", national_insurance_tax_band_total_payable);
    printf("Total: £%d\n", grand_total_payable_pounds);

    return 0;
}
