#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <uxhw.h>

static void
loadInputs(double *  elevation, double * temperature, double *  humidity, double *  pitot, double *  area, double *  C_L)
{
	double empiricalTemperatureValues[] = {
						11.1,
						4.9,
						7.8,
						2.2,
						10.3,
						3.4,
						8.5,
						2.7,
						10.6,
						4.0,
						8.2,
						1.2,
						8.4,
						2.1,
						5.7,
						0.2,
						10.3,
						3.2,
						9.4,
						4.1,
					};

	*temperature    = UxHwDoubleDistFromSamples(empiricalTemperatureValues, sizeof(empiricalTemperatureValues)/sizeof(double));
	*elevation		= UxHwDoubleUniformDist(30.0, 60.0);
	*humidity		= UxHwDoubleUniformDist(0.0, 1.0);
	*pitot	        = UxHwDoubleUniformDist(102678.0, 103045.0);
	*area	        = UxHwDoubleUniformDist(1.0, 2.0);
	*C_L		    = 0.63;
}

int
main(int argc, char *	argv[])
{
	double	elevation, temperature, humidity, pitot, area, C_L, pressure, vapor_pressure, density, velocity, lift;


	loadInputs(&elevation, &temperature, &humidity, &pitot, &area, &C_L);

// Calculation of pressure, vapor pressure, density, velocity and lift

    pressure = 101325 * pow( 1 - (0.0065 * elevation / 288.15) , 5.25545) ;

	vapor_pressure = humidity * 610.078 * exp((17.27 * temperature) / (temperature + 237.3)) ;

	density = ((pressure - vapor_pressure) / (287.058 * (temperature + 273.1))) + (vapor_pressure / (461.495 * (temperature + 273.1)));

	velocity = sqrt( 2*( pitot - pressure) /  density) ;

	lift = 0.5 * density * pow( velocity , 2) * C_L * area ;


	printf("Lift force (N):\t\t= %.1E MPa\n", lift);


	return 0;
}
