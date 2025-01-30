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
