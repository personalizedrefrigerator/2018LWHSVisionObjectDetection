package org.usfirst.frc.team5827.robot;

import java.util.HashMap;

/**
 *  The output from the vision program.
 * Usable with both network tables and Sockets.
 */
public class VisionOutput
{
	private HashMap<String, String> data;
	
	public VisionOutput()
	{
		data = new HashMap<String, String>();
	}
	
	// Get a value as an integer.
	public int getInt(String key)
	{
		return MathHelper.forceParseInt(data.get(key));
	}
	
	// Get a value as a double.
	public double getDouble(String key)
	{
		return MathHelper.forceParseDouble(data.get(key));
	}
	
	// Get a value as a string.
	public String getString(String key)
	{
		return data.get(key);
	}
	
	// Put or update a key in the vision table.
	public void putKey(String key, String value)
	{
		if(key != null)
		{
			data.put(key,  value);
		}
		else
		{
			System.err.println("WARNING: KEY IS NULL.");
		}
	}
	
	// Get the table as an HTML string.
	public String getAsHTMLString()
	{
		StringBuilder resultBuilder = new StringBuilder();
		
		for(String key : data.keySet())
		{
			resultBuilder.append("<li>");
			resultBuilder.append("<b>");
			resultBuilder.append(WebHelper.htmlEscape(key));
			resultBuilder.append("</b> ");
			resultBuilder.append(WebHelper.htmlEscape(getString(key)));
			resultBuilder.append("</li>\r\n");
		}
		
		return resultBuilder.toString();
	}
	
	// Get the table's contents as a standard string.
	public String toString()
	{
		StringBuilder resultBuilder = new StringBuilder();
		
		for(String key : data.keySet())
		{
			resultBuilder.append(key);
			resultBuilder.append(": ");
			resultBuilder.append(getString(key));
			resultBuilder.append("\r\n");
		}
		
		return resultBuilder.toString();
	}
}
