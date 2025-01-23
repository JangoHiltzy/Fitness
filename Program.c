#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// DEFINING THE GENDER ENUM
typedef enum
{
    Male,
    Female
} Gender;

// DEFINING THE BODYMETRICS STRUCT
typedef struct
{
    double heightCm; // HEIGHT IN CENTIMETERS
    double weightKg; // WEIGHT IN KILOGRAMS
    double waistCm;  // WAIST CIRCUMFERENCE IN CENTIMETERS
    double neckCm;   // NECK CIRCUMFERENCE IN CENTIMETERS
    double *hipCm;   // HIP CIRCUMFERENCE FOR FEMALES ONLY (NULLABLE: NULL IF NOT RELEVANT)
    Gender gender;   // GENDER (MALE OR FEMALE)
    int age;         // AGE OF THE USER
} BodyMetrics;

// BMI CALCULATION FUNCTION
double calculate_bmi(double weightKg, double heightCm)
{
    double heightM = heightCm / 100.0; // CONVERT HEIGHT TO METERS
    // BMI FORMULA: BMI = WEIGHT (KG) / (HEIGHT (M) * HEIGHT (M))
    return weightKg / (heightM * heightM); // BMI FORMULA
}

// BODY FAT CALCULATION FUNCTION
double calculate_body_fat_percentage(double waistCm, double neckCm, double heightCm, Gender gender, double *hipCm)
{
    double bodyFatPercentage;
    if (gender == Male)
    { // IF MALE, USE THE MALE BODY FAT FORMULA
        // MALE BODY FAT FORMULA:
        // BODY FAT PERCENTAGE = 495 / (1.0324 - 0.19077 * LOG10(WAIST - NECK) + 0.15456 * LOG10(HEIGHT)) - 450
        bodyFatPercentage = 495 / (1.0324 - 0.19077 * log10(waistCm - neckCm) + 0.15456 * log10(heightCm)) - 450;
    }
    else
    {
        double hipMinusNeck = hipCm ? *hipCm - neckCm : 0; // HANDLE NULLABLE HIP CM FOR FEMALES ONLY
        // FEMALE BODY FAT FORMULA:
        // BODY FAT PERCENTAGE = 495 / (1.29579 - 0.35004 * LOG10(WAIST + HIP - NECK) + 0.22100 * LOG10(HEIGHT)) - 450
        bodyFatPercentage = 495 / (1.29579 - 0.35004 * log10(waistCm + hipMinusNeck) + 0.22100 * log10(heightCm)) - 450;
    }

    return bodyFatPercentage;
}

// BMI CATEGORY FUNCTION
const char *get_bmi_category(double bmi)
{
    if (bmi < 18.5)
        return "Underweight"; // UNDERWEIGHT CATEGORY
    else if (bmi < 24.9)
        return "Normal"; // NORMAL CATEGORY
    else if (bmi < 29.9)
        return "Overweight"; // OVERWEIGHT CATEGORY
    else if (bmi < 34.9)
        return "Obese"; // OBESE CATEGORY
    else
        return "Very Obese"; // VERY OBESE CATEGORY
}

// BODY FAT CATEGORY FUNCTION
const char *get_body_fat_category(double bodyFatPercentage)
{
    if (bodyFatPercentage < 5)
        return "Essential fat"; // ESSENTIAL FAT CATEGORY
    else if (bodyFatPercentage < 14)
        return "Athletes"; // ATHLETES CATEGORY
    else if (bodyFatPercentage < 20)
        return "Fitness"; // FITNESS CATEGORY
    else if (bodyFatPercentage < 24)
        return "Average"; // AVERAGE CATEGORY
    else if (bodyFatPercentage < 31)
        return "Obese"; // OBESE CATEGORY
    else
        return "Very Obese"; // VERY OBESE CATEGORY
}

// DIET RECOMMENDATION BASED ON BMI
const char *get_diet_recommendation(double bmi)
{
    if (bmi < 18.5)
    {
        return "Consider increasing your carbohydrate and protein intake. Aim for a balanced diet with approximately 45-65% of calories from carbohydrates, 10-35% from protein, and 20-35% from fat."; // UNDERWEIGHT DIET RECOMMENDATION
    }
    else if (bmi < 24.9)
    {
        return "Maintain a balanced diet with approximately 45-65% of calories from carbohydrates, 10-35% from protein, and 20-35% from fat."; // NORMAL DIET RECOMMENDATION
    }
    else if (bmi < 29.9)
    {
        return "Consider a lower-carb, higher-protein approach such as a Low Carb High Fat (LCHF) or ketogenic (keto) diet."; // OVERWEIGHT DIET RECOMMENDATION
    }
    else if (bmi < 35)
    {
        return "For obesity, a Low Carb High Fat (LCHF) or ketogenic (keto) diet may be beneficial."; // OBESE DIET RECOMMENDATION
    }
    else
    {
        return "For severe obesity, a Low Carb High Fat (LCHF) or ketogenic (keto) diet may be beneficial. Consult with a healthcare professional."; // VERY OBESE DIET RECOMMENDATION
    }
}

// INPUT VALIDATION FUNCTION
int validate_positive_double(double *input, const char *prompt)
{
    int valid = 0;
    while (!valid)
    {
        printf("%s", prompt);
        if (scanf("%lf", input) != 1 || *input <= 0)
        {
            printf("Invalid input. Please enter a positive number.\n"); // INVALID INPUT ERROR MESSAGE
            while (getchar() != '\n')
                ; // CLEAR INVALID INPUT
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
    int continueProgram = 1; // VARIABLE TO CONTROL THE LOOP
    char tryAgain[2];        // VARIABLE TO STORE YES/NO RESPONSE
    char genderInput;        // VARIABLE TO STORE GENDER INPUT

    while (continueProgram)
    {
        // CREATE A BODYMETRICS STRUCT TO HOLD USER DATA
        BodyMetrics model = {170.0, 70.0, 80.0, 40.0, NULL, Male, 30};

        // ASK FOR GENDER FIRST
        printf("Enter your gender (m for Male, f for Female): ");
        while (scanf(" %c", &genderInput) != 1 || (genderInput != 'm' && genderInput != 'f'))
        {
            printf("Invalid input. Please enter 'm' for Male or 'f' for Female.\n"); // INVALID GENDER INPUT MESSAGE
            while (getchar() != '\n')                                                // CLEAR INVALID INPUT
                ;
        }
        model.gender = (genderInput == 'm') ? Male : Female;

        // PROMPT USER FOR INPUT (HEIGHT, WEIGHT, WAIST, NECK)
        validate_positive_double(&model.heightCm, "Enter height (cm): ");
        validate_positive_double(&model.weightKg, "Enter weight (kg): ");
        validate_positive_double(&model.waistCm, "Enter waist measurement (cm): ");
        validate_positive_double(&model.neckCm, "Enter neck measurement (cm): ");

        // FOR FEMALES, GET HIP MEASUREMENT
        if (model.gender == Female)
        {
            model.hipCm = (double *)malloc(sizeof(double)); // DYNAMICALLY ALLOCATE MEMORY FOR HIPCM
            validate_positive_double(model.hipCm, "Enter hip measurement (cm): ");
        }

        // BMI CALCULATION
        double bmi = calculate_bmi(model.weightKg, model.heightCm);
        printf("BMI: %.2f\n", bmi);
        printf("BMI Category: %s\n", get_bmi_category(bmi));

        // BODY FAT CALCULATION
        double bodyFatPercentage = calculate_body_fat_percentage(model.waistCm, model.neckCm, model.heightCm, model.gender, model.hipCm);
        printf("Body Fat Percentage: %.2f\n", bodyFatPercentage);
        printf("Body Fat Category: %s\n", get_body_fat_category(bodyFatPercentage));

        // DIET RECOMMENDATION BASED ON BMI
        printf("Diet Recommendation: %s\n", get_diet_recommendation(bmi));

        // FREE MEMORY ALLOCATED FOR HIPCM IF NEEDED
        if (model.hipCm != NULL)
        {
            free(model.hipCm); // DON'T FORGET TO FREE THE MEMORY
        }

        // ASK IF THE USER WANTS TO TRY AGAIN OR EXIT
        printf("\nDo you want to try again? (y for Yes, n for No): ");
        while (1) // INFINITE LOOP TO HANDLE INVALID INPUTS
        {
            if (scanf("%1s", tryAgain) == 1 && (tryAgain[0] == 'y' || tryAgain[0] == 'Y' || tryAgain[0] == 'n' || tryAgain[0] == 'N'))
            {
                // VALID INPUT
                break; // EXIT THE LOOP
            }
            else
            {
                printf("Invalid input. Please enter 'y' for Yes or 'n' for No: ");
                while (getchar() != '\n') // CLEAR THE INPUT BUFFER
                    ;
            }
        }

        // HANDLE USER CHOICE
        if (tryAgain[0] == 'n' || tryAgain[0] == 'N')
        {
            continueProgram = 0;         // EXIT IF USER CHOOSES 'n'
            printf("Exiting program\n"); // EXIT MESSAGE
        }
        else if (tryAgain[0] == 'y' || tryAgain[0] == 'Y')
        {
            continueProgram = 1; // ENSURE THE PROGRAM CONTINUES
        }
    }

    return 0;
}
