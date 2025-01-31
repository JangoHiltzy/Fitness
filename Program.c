#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// GENDER ENUM DEFINITION
typedef enum
{
    Male,
    Female
} Gender;

// BODYMETRICS STRUCT DEFINITION
// This struct stores user physical data, including height, weight, waist, and optional hip circumference for females.
typedef struct
{
    double heightCm; // Height in centimeters
    double weightKg; // Weight in kilograms
    double waistCm;  // Waist circumference in centimeters
    double neckCm;   // Neck circumference in centimeters
    double *hipCm;   // Optional hip circumference for females, nullable if not applicable
    Gender gender;   // Gender (male or female)
    int age;         // Age of the user
} BodyMetrics;

// BMI CALCULATION FUNCTION
// Given weight (kg) and height (cm), return the BMI value.
double calculate_bmi(double weightKg, double heightCm)
{
    double heightM = heightCm / 100.0;     // Convert height to meters
    return weightKg / (heightM * heightM); // Return BMI
}

// BODY FAT CALCULATION FUNCTION
// Given waist, neck, height, gender, and optional hip, return body fat percentage.
double calculate_body_fat_percentage(double waistCm, double neckCm, double heightCm, Gender gender, double *hipCm)
{
    double bodyFatPercentage;
    if (gender == Male)
    {
        bodyFatPercentage = 495 / (1.0324 - 0.19077 * log10(waistCm - neckCm) + 0.15456 * log10(heightCm)) - 450;
    }
    else
    {
        double hipMinusNeck = hipCm ? *hipCm - neckCm : 0;
        bodyFatPercentage = 495 / (1.29579 - 0.35004 * log10(waistCm + hipMinusNeck) + 0.22100 * log10(heightCm)) - 450;
    }
    return bodyFatPercentage;
}

// BMI CATEGORY FUNCTION
// Return category based on BMI.
const char *get_bmi_category(double bmi)
{
    if (bmi < 18.5)
        return "Underweight";
    else if (bmi < 24.9)
        return "Normal";
    else if (bmi < 29.9)
        return "Overweight";
    else if (bmi < 34.9)
        return "Obese";
    else
        return "Very Obese";
}

// BODY FAT CATEGORY FUNCTION
// Return category based on body fat percentage.
const char *get_body_fat_category(double bodyFatPercentage)
{
    if (bodyFatPercentage < 5)
        return "Essential fat";
    else if (bodyFatPercentage < 14)
        return "Athletes";
    else if (bodyFatPercentage < 20)
        return "Fitness";
    else if (bodyFatPercentage < 24)
        return "Average";
    else if (bodyFatPercentage < 31)
        return "Obese";
    else
        return "Very Obese";
}

// DIET RECOMMENDATION BASED ON BMI
// Return diet recommendation based on BMI.
const char *get_diet_recommendation(double bmi)
{
    if (bmi < 18.5)
    {
        return "Increase carbs and protein, aim for 45-65% calories from carbs, 10-35% from protein, and 20-35% from fat.";
    }
    else if (bmi < 24.9)
    {
        return "Maintain balanced diet with 45-65% carbs, 10-35% protein, and 20-35% fat.";
    }
    else if (bmi < 29.9)
    {
        return "Consider LCHF or keto diet, higher protein, lower carbs.";
    }
    else if (bmi < 35)
    {
        return "For obesity, LCHF or keto diet may help.";
    }
    else
    {
        return "For severe obesity, consult a healthcare professional and consider LCHF or keto.";
    }
}

// INPUT VALIDATION FUNCTION
// Validate user input for positive double values.
int validate_positive_double(double *input, const char *prompt)
{
    int valid = 0;
    while (!valid)
    {
        printf("%s", prompt);
        if (scanf("%lf", input) != 1 || *input <= 0)
        {
            printf("Invalid input. Please enter a positive number.\n");
            while (getchar() != '\n')
                ;
        }
        else
        {
            valid = 1;
        }
    }
    return 1;
}

int main()
{
    int continueProgram = 1;
    char tryAgain[2];
    char genderInput;

    while (continueProgram)
    {
        BodyMetrics model = {170.0, 70.0, 80.0, 40.0, NULL, Male, 30};

        printf("Enter your gender (m for Male, f for Female): ");
        while (scanf(" %c", &genderInput) != 1 || (genderInput != 'm' && genderInput != 'f'))
        {
            printf("Invalid input. Please enter 'm' for Male or 'f' for Female.\n");
            while (getchar() != '\n')
                ;
        }
        model.gender = (genderInput == 'm') ? Male : Female;

        validate_positive_double(&model.heightCm, "Enter height (cm): ");
        validate_positive_double(&model.weightKg, "Enter weight (kg): ");
        validate_positive_double(&model.waistCm, "Enter waist measurement (cm): ");
        validate_positive_double(&model.neckCm, "Enter neck measurement (cm): ");

        if (model.gender == Female)
        {
            model.hipCm = (double *)malloc(sizeof(double));
            validate_positive_double(model.hipCm, "Enter hip measurement (cm): ");
        }

        double bmi = calculate_bmi(model.weightKg, model.heightCm);
        printf("BMI: %.2f\n", bmi);
        printf("BMI Category: %s\n", get_bmi_category(bmi));

        double bodyFatPercentage = calculate_body_fat_percentage(model.waistCm, model.neckCm, model.heightCm, model.gender, model.hipCm);
        printf("Body Fat Percentage: %.2f\n", bodyFatPercentage);
        printf("Body Fat Category: %s\n", get_body_fat_category(bodyFatPercentage));

        printf("Diet Recommendation: %s\n", get_diet_recommendation(bmi));

        if (model.hipCm != NULL)
        {
            free(model.hipCm);
        }

        printf("\nDo you want to try again? (y for Yes, n for No): ");
        while (1)
        {
            if (scanf("%1s", tryAgain) == 1 && (tryAgain[0] == 'y' || tryAgain[0] == 'Y' || tryAgain[0] == 'n' || tryAgain[0] == 'N'))
            {
                break;
            }
            else
            {
                printf("Invalid input. Please enter 'y' for Yes or 'n' for No: ");
                while (getchar() != '\n')
                    ;
            }
        }

        if (tryAgain[0] == 'n' || tryAgain[0] == 'N')
        {
            continueProgram = 0;
            printf("Exiting program\n");
        }
        else if (tryAgain[0] == 'y' || tryAgain[0] == 'Y')
        {
            continueProgram = 1;
        }
    }

    return 0;
}
