/*  
 * 	Name: Artem Ivanov
 *  Course: CNT 4714–Summer2021–Project 
 *  ThreeAssignment title: A Three-Tier Distributed Web-Based Application
 *  Date: Sunday August 1, 2021
*/

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.*;

public class SQLFormatter
{
	/*
	 * The getHtmlRows() method in this class takes the output of the SQL
	 * return (a ResultSet object) and converts it into an HTML table that can be
	 * rendered in any web-browser. All HTML table elements (except fot the table element itself) are
	 * embedded in the returned StringBuffer object
	 */
	
	public static synchronized String getHtmlRows(ResultSet results) throws SQLException
	{
		// create a StringBuffer object to hold the html table markup
		StringBuffer holder = new StringBuffer();
		// extract the meta data from the ResultSet object
		ResultSetMetaData dbMeta = results.getMetaData();
		// find out how many columns are in the returned ResultSet object
		int columnCount = dbMeta.getColumnCount();
		
		// begin creating html table markup - intial row - column headers
		holder.append("<tr bgcolor=#FF0000 align=center>");
		
		for (int i = 1; i <= columnCount; i++)
		{
			holder.append("<td><b>" + dbMeta.getColumnName(i) + "</td>");
		}
		
		holder.append("</tr>");
		
		int cnt = 0;
		// iterate through the ResultSet object extracting one row of data at a time.
		while (results.next())
		{
			//append table markup element to [StringBufferObject]
			if (cnt % 2 == 0)
			{
				holder.append("<tr bgcolor=#cccccc>");
			}
			else
			{
				holder.append("<tr bgcolor=#FFFFFF>");
			}
			
			cnt++;
			
			for (int i = 1; i <= columnCount; i++)
			{
				holder.append("<td align=center>" + results.getString(i) + "</td>");
			}
		}
		
		holder.append("</tr>");
		
		return holder.toString();
	}
}
