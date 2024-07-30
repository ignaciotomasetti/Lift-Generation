[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/ignaciotomasetti/Lift-Generation/v2#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/ignaciotomasetti/Lift-Generation/v2#gh-light-mode-only)


# C model for lift generation

A simple model for the lift generated by an airfoil, which is moving at a certain relative velocity with respect to the air, can be derived from the Bernoulli equation. In this example we will use one of the simplest and most widely used formulas to calculate the lift force:

$$L=\frac{1}{2}\rho v^2 C_LA$$

which can be found in John Anderson's book [^0]. Reasonable measurement uncertainties were taken into account for each of the parameters. The subsequent uncertainty distribution of the output can be observed and used by the client to gain insight on the model.

## Inputs

The inputs and their ranges are:

-	`elevation`:	30 to 60 m
-	`temperature`:		0 to 20 C
-	`humidity`:		0.0 to 1.0
-	`pitot`:		102678 to 103045 N/m^2
-	`area`:		1 to 2 m^2 (i.e., constant)
-	`C_L`:		0.63 (i.e., constant)

The parameter `elevation` measures the height above mean sea level (AMSL) in meters, the `temperature` of the air measured in Celsius, `humidity` is the relative humidity (up to 1.0 which represents a 100%) , the parameter `pitot` refers to the Pitot's pressure, or stagnation pressure, and it is the pressure measured by the Pitot's tube in Pascals(N/m^2), the `area` of the airfoil which is assumed beforehand to have a chord of 1.3 meters, and `C_L` is the lift coefficient, a dimensionless quantity which depends on many factors in a complex manner (on the shape of the airfoil, assumed NACA 2421, on the angle of attack of the airfoil, assumed 4 degrees), but we will assume it as a constant for the simplification of the model.


## Intermediate results

Before arriving to the final output, we derive some intermediate values which can be of interest by themselves.

The total `pressure`,

$$101325 ( 1 - (0.0065 \frac{elevation}{288.15}))^{5.25545}$$

the vapor pressure of water, `vapor_pressure`,

$$humidity \ \ 610.078 \ \exp(\frac{17.27 * temperature}{temperature + 237.3})$$

the density of air, or atmospheric density, $\rho$

$$\frac{pressure - vapor\_pressure}{287.058 \  (temperature + 273.1} + \frac{vapor\_pressure}{461.495 \ (temperature + 273.1)}$$

and the `velocity`,

$$\sqrt{ 2 \ \frac{pitot - pressure}{\rho}}$$

## Outputs

The output is the lift force, `L` where

$$L=\frac{1}{2}\rho v^2 C_LA$$

## Repository Tree Structure
The repository contains two different variants of the lift generation model. The first variant (`v1`), allows the user to choose the inputs one by one and returs the exact value of the main output, as well as the intermediate results. The second variant (`v2`) has the Temperature as the distribution constructed directly from empirical values (obtained from MetOffice data, 2020/2024, Sutton-Bonnington), and the rest of the inputs as uniform distributions with the mentioned tolerance.

```
.
├── README.md
├── v1
│   ├── README.md
│   └── src
│       ├── README.md
│       └── Lift-Generation.c
└── v2
    ├── README.md
    └── src
        ├── Lift-Generation-with-all-parameters-as-distributions.c
        └── README.md
```



<br/>
<br/>
<br/>

[^0]: Anderson, J. D., & Bowden, M. L. (2005). Introduction to flight (Vol. 582). New York, NY, USA: McGraw-Hill Higher Education.
