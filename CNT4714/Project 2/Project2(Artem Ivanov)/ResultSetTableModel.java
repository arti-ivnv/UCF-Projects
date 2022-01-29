/*
 * Name: Artem Ivanov
 * Course: CNT4714 Summer 2021
 * Assignment title: Project 2:  Two-Tier Client-Server Application Development With MySQL andJDBC
 * Date:July 4, 2021
 * Class: ResultSetTableModel
*/

package package1;

import java.sql.*;
import javax.swing.table.AbstractTableModel;

import com.mysql.cj.jdbc.MysqlDataSource;

import java.util.Properties;
import java.io.FileInputStream;
import java.io.IOException;


public class ResultSetTableModel extends AbstractTableModel 
{
	private Connection connection;
	private Connection oplogConnection;
	private Statement statement;
	private Statement oplogStatement;
	private ResultSet resultSet;
	private ResultSetMetaData metaData;
	private int numberOfRows;
	private String checkQuery;
	
	
	// keep track of database connection status
	public boolean connectedToDatabase = false;
	public boolean connectedToDatabase2 = false;
	
	// constructor initializes resultSet and obtains its meta data object, determines number of rows
	public ResultSetTableModel (Connection incomingConnection, String query) throws SQLException, ClassNotFoundException
	{
		Properties properties = new Properties();
		
		FileInputStream filein = null;
		MysqlDataSource dataSource = null;
	    
		//read properties file
		try 
		{
	    	filein = new FileInputStream("oplog.properties");
	    	properties.load(filein);
	    	dataSource = new MysqlDataSource();
	    	dataSource.setURL(properties.getProperty("MYSQL_DB_URL"));
	    	dataSource.setUser(properties.getProperty("MYSQL_DB_USERNAME"));
	    	dataSource.setPassword(properties.getProperty("MYSQL_DB_PASSWORD")); 	
	    
            // connect to database bikes and query database
  	        // establish connection to database
   	        Connection oplogConnection = dataSource.getConnection();
	
            // create Statement to query database
   	        oplogStatement = oplogConnection.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY );

            // update database connection status
            connectedToDatabase2 = true;
		}
		catch ( SQLException sqlException ) 
	    {
			sqlException.printStackTrace();
	        System.exit( 1 );
	    } // end catch
	    catch (IOException e) 
		{
	   	    e.printStackTrace();
	    }

		// connect to database
		connection = incomingConnection;
		
		// create Statement to query and update database
		statement = connection.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE);
		
		// update database connection status
		connectedToDatabase = true;
		
	}
	
	// get class that represents column type
	public Class getColumnClass(int column) throws IllegalStateException
	{
		// Ensure database connection is available
		if (!connectedToDatabase)
			throw new IllegalStateException("Not Connected to Database");
		
		// determine Java Class of column
		try
		{
			String className = metaData.getColumnClassName(column + 1);
			
			// return Class object that represents className
			return Class.forName(className);
		}
		catch (Exception exception) {
			exception.printStackTrace();
			
		}
		
		// if problems occur above, assume type Object
		return Object.class;
		
	}
	
	// get number of columns in ResultSet
	public int getColumnCount() throws IllegalStateException
	{
		// Ensure database connection is available
		if (!connectedToDatabase)
			throw new IllegalStateException("Not Connected to Database");
		
		// determine number of columns
		try
		{
			if(metaData != null)
			{
			return metaData.getColumnCount();
			}
		}
		catch (SQLException sqlException)
		{
			sqlException.printStackTrace();
		}
		
		// If problems occur above, return 0 for number of columns
		return 0;
	}
	
	// get name of a particular column in ResultSet
	public String getColumnName(int column) throws IllegalStateException
	{
		// Ensure database connection is available
		if (!connectedToDatabase)
			throw new IllegalStateException("Not Connected to Database");
		
		// determine column name
		try
		{
			return metaData.getColumnName(column + 1);
		}
		catch (SQLException sqlException)
		{
			sqlException.printStackTrace();
		}
		
		return "";
	}
	
	// return number of rows in ResultSet
	public int getRowCount() throws IllegalStateException
	{
		// Ensure database connection is available
		if (!connectedToDatabase)
			throw new IllegalStateException("Not Connected to Database");
		
		return numberOfRows;
	}
	
	// obtain value in particular row and column
	public Object getValueAt(int row, int column) throws IllegalStateException
	{
		// Ensure database connection is available
		if (!connectedToDatabase)
			throw new IllegalStateException("Not Connected to Database");
		
		// obtain a value at specific ResultSet row and column
		try
		{
			resultSet.absolute(row + 1);
			return resultSet.getObject(column + 1);
		}
		catch (SQLException sqlException)
		{
			sqlException.printStackTrace();
		}
		
		return "";
	}
	
	
	// set new database query string
	public void setQuery (String query) throws SQLException, IllegalStateException, ClassNotFoundException
	{
		int op;
		// ensure database connection is available
		if (!connectedToDatabase)
			throw new IllegalStateException("Not Connected to Database");
		
		// specify query and execute it
		resultSet = statement.executeQuery( query );
		
		// obtain meta data for ResultSet
		metaData = resultSet.getMetaData();
		
		// determine number of rows in ResultSet
		resultSet.last();                   // move to last row
		numberOfRows = resultSet.getRow();  // get row number  
		
			// add code here to update the operation log db as a user client: +1 to query count
		
		//num_queries = num_queries + 1;
		op = oplogStatement.executeUpdate( "UPDATE operationscount SET num_queries = num_queries + 1 " );
		
			// end code to update operations log database
		
		// notify JTable that model has changed
		fireTableStructureChanged();
	}
	
	// set new database update-query string 
	public void setUpdate (String query) throws SQLException, IllegalStateException
	{
		int res;
		int op2;
		
		// ensure database connection is available
		if (!connectedToDatabase)
			throw new IllegalStateException("Not Connected to Database");
		
		// specify update and execute it
		res = statement.executeUpdate( query );
		
		// obtain meta data for ResultSet
		// metaData = resultSet.getMetaData();
		
		// determine number of rows in ResultSet
		// resultSet.last();                   // move to last row
		// numberOfRows = resultSet.getRow();  // get row number 
		
		// add code here to update the operation log db as a root user client: +1 to update count
		
		op2 = oplogStatement.executeUpdate( "UPDATE operationscount SET num_updates = num_updates + 1 " );
			
		// end code to update operations log database
		// notify JTable that model has changed
		fireTableStructureChanged();
	}
	
	// close Statement and Connection
	public void disconnectFromDatabase()
	{
		if (!connectedToDatabase)
			return;
		
		// close Statement and Connection
		try
		{
			statement.close();
			connection.close();
			oplogStatement.close();
			oplogConnection.close();
		}
		catch(SQLException sqlException) 
		{
			sqlException.printStackTrace();
		}
		finally
		{
			connectedToDatabase = false;
			connectedToDatabase2 = false;
		}
	}
	
	
}