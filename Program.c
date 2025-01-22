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
