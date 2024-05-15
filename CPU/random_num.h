
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

// Utility Functions

double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

double random_double2(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}