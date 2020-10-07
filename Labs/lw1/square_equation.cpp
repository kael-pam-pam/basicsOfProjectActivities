#include <cstdio>
#include <cmath>

int main()
{
    // 1. prompt user to enter coefficients
    std::puts("please enter a, b and c for `ax^2 + bx + c = 0`:");
    // 2. read coefficients for equation `ax + b = 0`
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);
    float d = (b * b) - 4 * a * c;
    // 3. solve equation `ax + b = 0`
    // solution: `x = -b / a`
    if (d < 0)
    {
        std::printf("No solutions");
    }
    else
    {
        float x1 = (-b + sqrt(d)) / (2 * a);
        float x2 = (-b - sqrt(d)) / (2 * a);
        if (d == 0)
        {
            std::printf("solution: %f\n", x1);
        }
        else
        {
            std::printf("solution: %f and %f\n", x1, x2);
        }
    }
}