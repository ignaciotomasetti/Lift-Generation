#include <stdio.h>
#include <math.h>

// Functions to calculate pressure, vapor pressure, density, velocity and lift
double calculate_pressure(double elevation) {
    return 101325 * pow( 1 - (0.0065 * elevation / 288.15) , 5.25545) ;
}

double calculate_vapor_pressure(double temperature, double humidity) {
    return humidity * 610.078 * exp((17.27 * temperature) / (temperature + 237.3)) ;
}

double calculate_density(double temperature, double pressure, double vapor_pressure) {
    return ((pressure - vapor_pressure) / (287.058 * (temperature + 273.1))) + (vapor_pressure / (461.495 * (temperature + 273.1)));
}

double calculate_velocity(double pressure, double pitot, double density) {
    return sqrt( 2*( pitot - pressure) /  density) ;
}

double calculate_lift(double density, double velocity, double C_L, double area) {
    return 0.5 * density * pow( velocity , 2) * C_L * area ;
}


int main() {
    double elevation, temperature, humidity, pitot, area, pressure, vapor_pressure, density, velocity, C_L, lift;

    // Input values
    printf("Enter the elevation (30 to 60 m): ");
    scanf("%lf", &elevation);

    printf("Enter the air temperature (0 to 20 C): ");
    scanf("%lf", &temperature);

    printf("Enter the air humidity (0.0 to 1.0): ");
    scanf("%lf", &humidity);

    printf("Enter the Pitot tube's pressure (stagnation pressure) (102678 to 103045 N/m^2): ");
    scanf("%lf", &pitot);

    printf("Enter airfoil area (1 to 2 m^2): ");
    scanf("%lf", &area);

    C_L = 0.63;

    // Calculation of pressure, vapor pressure, density, velocity and lift
    pressure = calculate_pressure(elevation);

    vapor_pressure = calculate_vapor_pressure(temperature, humidity);

    density = calculate_density(temperature, pressure, vapor_pressure);

    velocity = calculate_velocity(pressure, pitot, density);

    lift = calculate_lift(density, velocity, C_L, area);


    // Output the results
    printf("Air pressure (N/m^2): %.2lf\n", pressure);
    printf("Vapor pressure (N/m^2): %.2lf\n", vapor_pressure);
    printf("Air density (N/m^2): %.2lf\n", density);
    printf("Air free-stream velocity (m/s): %.2lf\n", velocity);
    printf("Lift force (N): %.2lf\n", lift);

    return 0;
}
