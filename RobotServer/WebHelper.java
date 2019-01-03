package org.usfirst.frc.team5827.robot;

public class WebHelper 
{
	// Escape a given string of input characters.
	//E.g. Replace < with &lt; and > with &gt;
	public static String htmlEscape(String input)
	{
		StringBuilder result = new StringBuilder(); // Don't use string concatenation.
		
		char currentCharacter;
		
		for(int i = 0; i < input.length(); i++)
		{
			currentCharacter = input.charAt(i);
			
			if(currentCharacter == '<')
			{
				result.append("&lt;");
			}
			else if(currentCharacter == '>')
			{
				result.append("&gt;");
			}
			else if(currentCharacter == '&')
			{
				result.append("&amp;");
			}
			else
			{
				result.append(currentCharacter);
			}
			
		}
		
		return result.toString();
	}
	
	// Get a default stylesheet.
	public static String getDefaultStyleSheet()
	{
		String result = "<style>"
				+ "#contentDiv "
				+ "{"
				+ "	max-width: 400px; "
				+ " border: 1px solid black; "
				+ " margin-left: auto; "
				+ " margin-right: auto; "
				+ " padding: 10px; "
				+ " margin-top: 10px; "
				+ " box-shadow: 10px 10px 5px rgba(0, 0, 0, 0.5); "
				
				+ " border-radius: 4px; "
				+ " background-color: rgba(255, 200, 255, 0.8); "
				+ " transition: 1s ease all; "
				+ "}\n"
				+ "#contentDiv:hover"
				+ "{"
				+ " background-color: rgba(255, 225, 255, 0.8); "
				+ "}\n"
				+ "body"
				+ "{"
				+ " background-image: radial-gradient(purple, white); "
				+ " background-size: 5px 5px; "
				+ "}\n"
				+ "@media screen and (max-width: 800px) "
				+ "{"
				+ " #contentDiv"
				+ " {"
				+ "  max-width: none;"
				+ "  margin: 0px;"
				+ "  box-shadow: none;"
				+ "  border-radius: 0px;"
				+ " }"
				+ "}"
				+ "</style>";
		
		return result;
	}
	
	// Get HTML Meta headers.
	public static String getDefaultMetas()
	{
		String result = "<meta name='viewport' content='width=device-width,initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0'/>"
				+ "<meta charset='UTF-8'/>";
		
		return result;
	}
}
