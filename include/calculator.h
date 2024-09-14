#include <iostream>
#include <string>
using namespace std;

static float bmi;
static float BMI(float height, float weight) {
    bmi = weight / (height*height);
    return bmi;
}
