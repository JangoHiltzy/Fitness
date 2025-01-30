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
