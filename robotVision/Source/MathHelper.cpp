#include "MathHelper.h"

// Include the math library.
#include <math.h>

namespace MathHelper
{
	// Solve an equation in the form ax^2 + bx + c = 0.
	QuadraticResult solveQuadratic(double a, double b, double c)
	{
		double solution1 = 0, solution2 = 0;
		
		double squareRootContents = b*b - 4*a*c,
			denominator = 2*a;
			
		bool defined = false;
		
		if(denominator != 0 && squareRootContents >= 0)
		{
			double squareRootResult = sqrt(squareRootContents);
			
			// Use the quadratic formula to calculate the result.
			solution1 = (-b + squareRootResult)/denominator;
			solution2 = (-b - squareRootResult)/denominator;
			
			// Note that the result is defined.
		}
		
		// Compile the solutions into a result.
		QuadraticResult result = {solution1, solution2, defined};
		
		return result;
	}
}
