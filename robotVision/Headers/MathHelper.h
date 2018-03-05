#pragma once

#define PI 3.141592653589793238462643383
#define E 2.718281828

namespace MathHelper
{
	// A solution to a quadratic equation.
	struct QuadraticResult
	{
		double solution1;
		double solution2;
		
		bool defined;
	};
	
	QuadraticResult solveQuadratic(double a, double b, double c); // Solve an equation in the form of ax*x + bx + c = 0.
}
