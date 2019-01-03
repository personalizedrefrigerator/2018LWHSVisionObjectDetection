package org.usfirst.frc.team5827.robot;

public class MathHelper 
{
	/**
	 *  Parse an integer, without errors.
	 * @param stringToConvert A string, null or non-null to be converted to an integer.
	 * @return The given string, as an integer.
	 */
	public static int forceParseInt(String stringToConvert)
	{
		if(stringToConvert == null) // Allow input to be null.
		{
			return 0;
		}
		
		int result = 0, // Store the result here.
				power = 0; // The power to raise 10 to.
		
		for(int characterIndex = stringToConvert.length() - 1; characterIndex >= 0; characterIndex--)
		{
			// Add the digit to the result.
			result += ((int)(stringToConvert.charAt(characterIndex) - '0')) * Math.pow(10, power);
			
			power++;
		}
		
		return result;
	}
	
	/**
	 *  Like forceParseInt, but returns a double.
	 *  This function operates in base 10.
	 * @param stringToConvert A string to convert to a double.
	 * @return The double version of the given string.
	 */
	public static double forceParseDouble(String stringToConvert)
	{
		if(stringToConvert == null) // Give an output, even if input is null.
		{
			return 0.0;
		}
		
		int decimalLocation = stringToConvert.indexOf('.'); // Find the location of the decimal point.
		
		double result = 0;  // Output will be stored in result.
		int power = 0; // 10 is raised to powers of an integer.
		
		if(decimalLocation == -1) // If no decimal is found,
		{
			power = 0;
		}
		else
		{
			power = decimalLocation - stringToConvert.length() + 1; // The number of digits after the decimal point.
		}
		
		char currentChar;
		
		// Loop from the last character to the first.
		for(int characterIndex = stringToConvert.length() - 1; characterIndex >= 0; characterIndex--)
		{
			currentChar = stringToConvert.charAt(characterIndex);
			
			if(currentChar <= '9' && currentChar >= '0')
			{
				result += ((double)(currentChar - '0')) * Math.pow(10, power);
				
				// Only increase the power if a digit was added to the result.
				power++;
			}
		} // End for.
		
		return result;
	}
}
