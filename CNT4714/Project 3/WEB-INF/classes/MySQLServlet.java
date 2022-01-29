/*  
 * 	Name: Artem Ivanov
 *  Course: CNT 4714–Summer2021–Project 
 *  ThreeAssignment title: A Three-Tier Distributed Web-Based Application
 *  Date: Sunday August 1, 2021
*/

import java.io.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;
import java.sql.*;
import java.util.Properties;
import com.mysql.cj.jdbc.MysqlDataSource;

public class MySQLServlet extends HttpServlet 
{
	private Connection connection;
	private Statement statement;
	
	/*
	 * The init() method connects to the MySQL backend and reports all errors to the web-browser screen.
	 * Call is implicitly initiated by the servlet container prior to any servlet instance handling a request.
	 */
	
	@Override
	public void init() throws ServletException
	{
		
		/*
		 * 3.
		 * Classical technique for static loading of driver - tightly coupled connection details
		 * insert code here to utilize the standard classical static method for loading the db driver and establish a connection to the DB
		 */
		
		try
		{
			// establish Connection object - see examples in notes for using static technique
			 Class.forName("com.mysql.cj.jdbc.Driver");
			 connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/project3?useTimezone=true&serverTimezone=UTC", "root", "LuckerCode26" );
			 statement = connection.createStatement();
		}
		catch (ClassNotFoundException e)
		{
			System.out.println("Error loading driver.");
		}
		catch (SQLException e)
		{
			System.out.println("Error opening the db connection: " + e.getMessage());
		}
	}
	
	@Override
	public void destroy()
	{
		try
		{
			statement.close();
			connection.close();
		}
		catch (SQLException e)
		{
			System.out.println("Error opening the db connection: " + e.getMessage());
		}
	}
	
	/*
	 * The doGet() method executes the actual query. It takes
	 * the text from the HTML text area and checks it to determine
	 * if it is a SELECT or an UPDATE statement. Based upon the
	 * result, the command is passed to the appropriate executor.
	 * All the results of the query are then passed to the 
	 * SQLFormatter class for conversion into a format that can
	 * be deciphered by any web browser (HTML). All errors or
	 * responses by the server are reported to the web-browser
	 */
	
	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
	{
		// get the user SQL command from the user interface (index.jsp)
		String sqlStatement = request.getParameter("sqlStatement");
		
		// set up the return message string object
		String message = "";
		
		try
		{
			// create a Statement object on the Connection object that was created in init() above
			
			// message the incoming user SQL command to eliminate any leading/trailing whitespace
			
			sqlStatement = sqlStatement.trim();
			// grab the leading six characters from the user SQL command - we're looking for queries vs non-queries
			String sqlType = sqlStatement.substring(0, 6);
			// set up a return value for MySQL return status
			int mysqlReturnVal;
			
			// handle user command
			// top case is a query - all others are non-queries
			if(sqlType.equalsIgnoreCase("select"))
			{
				// process query on MySQL-side - get ResultSet object back
				ResultSet resultSet = statement.executeQuery(sqlStatement);
				
				// convert the ResultSet object into an HTML table using SQLFormatter class
				message = SQLFormatter.getHtmlRows(resultSet);
			}
			else
			{
				// updating command is issued by user - non bonus version
				if (sqlStatement.contains("shipments"))
				{
					// business logic to fire
					// uncomment the next line to run the simple version (non-bonus) version of the business logic
					mysqlReturnVal = simpleBusinessLogic(connection, statement, sqlStatement);
					// build appropriate return message for business logic case
					message = "<tr bgcolor=#00FF00 align=center><td><b>The statement executed successfully.<br>" + mysqlReturnVal 
							+ " row(s) affected. <br><br> Bussiness Logic Detected! - Updating Supplier Status. <br><br> Business Logic updated " 
							+ mysqlReturnVal + " supplier status marks.<br><br></b></tr></td>";
				}
				// Second option on updating command does not involve the shipments table - business logic does not trigger/fire
				else
				{
					// no business logic (shipment table not involved) - just execute user update
					mysqlReturnVal = statement.executeUpdate(sqlStatement);
					
					if (mysqlReturnVal != 0)
					{
						// success
						// build appropriate return message for business logic not triggering - but command successful
						message = "<tr bgcolor=#00FF00 align=center><td><b>The statement executed successfully. <br><br> Business Logic Not Triggered!<br><br></b></tr></td>";
					}
					else
					{
						// statement executed successfully but no rows were updated
						// build message for update successful but rows update
						message = "<tr bgcolor=#00FF00 align=center><td><b>The statement executed successfully. <br><br> No rows were updated<br><br></b></tr></td>";
					}
				}
				//statement.close();
			}
		} catch (SQLException e){
			message = "<tr bgcolor=#ff0000><td><font color=#ffffff><b>Error executing the SQL statement:</b><br>" +e.getMessage() + "</tr></td></font>";
			
		}
		
		// identify session variables and set their attributes for return to calling page via RequestDispatcher object
		HttpSession session = request.getSession();
		session.setAttribute("message", message);
		session.setAttribute("sqlStatement", sqlStatement);
		// tell dispatcher where to forward results
		RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/index.jsp");
		// have dispatcher forward results
		dispatcher.forward(request, response);
	}
	
	/*
	 * The doPost() method simply calls for the doGet method
	 */
	
	@Override
	public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
	{
		doGet(request, response);
	}
	
	private int simpleBusinessLogic(Connection incomingConnection, Statement incomingStatement, String userUpdate)
	{
		int sBLReturnVal = 0;
		String sBLCommand = "update suppliers set status = status + 5 where snum in (select distinct snum from shipments where quantity >= 100)";
		
		try {
			// execute original user update command
			sBLReturnVal = incomingStatement.executeUpdate(userUpdate); // run user update
			// execute the simple version if the business logic - see above as sBLCommand
			sBLReturnVal = incomingStatement.executeUpdate(sBLCommand);
		} catch (SQLException e) {
			System.out.println("Error opening the db connection: " + e.getMessage());
		}
		return sBLReturnVal;
	}

}
