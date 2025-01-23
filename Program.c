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
