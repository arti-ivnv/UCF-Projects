/*
 * Name: Artem Ivanov
 * Course: CNT4714 Summer 2021
 * Assignment title: Project 2:  Two-Tier Client-Server Application Development With MySQL andJDBC
 * Date:July 4, 2021
 * Class: SQLClientApp
*/

package package1;

import java.awt.*;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import com.mysql.cj.jdbc.MysqlDataSource;
import java.lang.*;

// Maybe implemented from the helper class, so, delete later.
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;


public class SQLClientApp extends JPanel
{
	// Variables
	private JButton ConnectButton, ClearQuery, ExecuteButton, ClearWindow;
	private JLabel QueryLabel, dbInfoLabel, JbdcLabel, UrlLabel, UserLabel, PasswordLabel;
	private JTextArea TextQuery;
	private JComboBox DriverCombo;
	private JComboBox UrlCombo;
	private JTextField UserText;
	private JPasswordField PasswordText;
	private JLabel StatusLabel, WindowLabel;
	private ResultSetTableModel tableModel;
	private Connection connect;
	private TableModel Empty;
	private JTable resultTable;

	public SQLClientApp()
	{
		// Construct GUI

		//Initialize the drop down menus
		String[] DriverItems = {"com.mysql.cj.jdbc.Driver","oracle.jbdc,driver.OracleDriver"};
		String[] UrlItems = {"jdbc:mysql://localhost:3306/project2?useTimezone=true&serverTimezone=UTC",
							 "jdbc:mysql://localhost:3306/bikedb?useTimezone=true&serverTimezone=UTC"};

		// Construct GUI components
		ConnectButton = new JButton ("Connect to Database");
		ClearQuery = new JButton ("Clear SQL Command");
		ExecuteButton = new JButton("Execute SQL Command");
		ClearWindow = new JButton("Clear Result Window");
		ConnectButton.setFont(new Font("Arial", Font.BOLD, 12));
		ClearQuery.setFont(new Font("Arial", Font.BOLD, 12));
		ExecuteButton.setFont(new Font("Arial", Font.BOLD, 11));
		ClearWindow.setFont(new Font("Arial", Font.BOLD, 12));

		QueryLabel = new JLabel();
		QueryLabel.setFont(new Font("Arial", Font.BOLD, 14));
		QueryLabel.setForeground(Color.BLUE);
		QueryLabel.setText("Enter An SQL Command");

		dbInfoLabel = new JLabel();
		dbInfoLabel.setFont(new Font("Arial", Font.BOLD, 14));
		dbInfoLabel.setText("Enter Database Information");

		JbdcLabel = new JLabel(" JBDC Driver");
		JbdcLabel.setOpaque(true);
		JbdcLabel.setBackground(Color.LIGHT_GRAY);
		JbdcLabel.setForeground(Color.BLACK);

		UrlLabel = new JLabel(" Database URL ");
		UrlLabel.setOpaque(true);
		UrlLabel.setBackground(Color.LIGHT_GRAY);
		UrlLabel.setForeground(Color.BLACK);

		UserLabel = new JLabel(" Username ");
		UserLabel.setOpaque(true);
		UserLabel.setBackground(Color.LIGHT_GRAY);
		UserLabel.setForeground(Color.BLACK);

		PasswordLabel = new JLabel(" Password ");
		PasswordLabel.setOpaque(true);
		PasswordLabel.setBackground(Color.LIGHT_GRAY);
		PasswordLabel.setForeground(Color.BLACK);

		TextQuery = new JTextArea (5, 5);
		DriverCombo = new JComboBox (DriverItems);
		UrlCombo = new JComboBox (UrlItems);
		UserText = new JTextField ("",10);
		PasswordText = new JPasswordField ("", 10);

		StatusLabel = new JLabel ("No Connection Now");
		StatusLabel.setOpaque(true);
		StatusLabel.setBackground(Color.BLACK);
		StatusLabel.setForeground(Color.RED);

		WindowLabel = new JLabel();
		WindowLabel.setFont(new Font("Arial", Font.BOLD, 14));
		WindowLabel.setForeground(Color.BLUE);
		WindowLabel.setText("SQL Execution Result Wondow");

		resultTable = new JTable();

		Empty = new DefaultTableModel();

		// Window size and layout
		setPreferredSize (new Dimension (1000,520));
		setLayout (null);
		final Box square = Box.createHorizontalBox();
		square.add( new JScrollPane(resultTable) );
		Box sqlSquare = Box.createHorizontalBox();
		sqlSquare.add(new JScrollPane( TextQuery ));
		resultTable.setEnabled(false);
		resultTable.setGridColor(Color.BLACK);

		// set up components with bounds (x, y, w, h)
		// x = pixels from the left edge of container
		// y = pixels from the top edge of container
		// w = pixel width of element
		// h = pixel height of element
		ConnectButton.setBounds(20, 187, 165, 25);
		ConnectButton.setBackground(Color.BLUE);
		ConnectButton.setForeground(Color.YELLOW);
		ConnectButton.setBorderPainted(false);
		ConnectButton.setOpaque(true);

		ClearQuery.setBounds(480, 150, 175, 25);
		ClearQuery.setForeground(Color.RED);
		ClearQuery.setBackground(Color.WHITE);
		ClearQuery.setBorderPainted(false);
		ClearQuery.setOpaque(true);

		ExecuteButton.setBounds(695, 150, 175, 25);
		ExecuteButton.setBackground(Color.GREEN);
		ExecuteButton.setBorderPainted(false);
		ExecuteButton.setOpaque(true);

		ClearWindow.setBounds(25, 480, 168, 25);
		ClearWindow.setBackground(Color.YELLOW);
		ClearWindow.setBorderPainted(false);
		ClearWindow.setOpaque(true);

		dbInfoLabel.setBounds(10, 0, 300, 25);
		dbInfoLabel.setForeground(Color.BLUE);

		JbdcLabel.setBounds(10, 21, 125, 25);
		UrlLabel.setBounds(10, 49, 125, 25);
		PasswordLabel.setBounds(10, 107, 125, 24);
		StatusLabel.setBounds(200, 187, 690, 25);
		WindowLabel.setBounds(45, 231, 220, 25);
		square.setBounds(45, 254, 841, 220);
		QueryLabel.setBounds(450, 0, 215, 25);
		sqlSquare.setBounds(450, 22, 438, 125);
		DriverCombo.setBounds(135, 21, 290, 25);
		UrlCombo.setBounds(135, 49, 290, 25);
		UserLabel.setBounds(10, 78, 125, 25);
		UserText.setBounds(135, 78, 290, 25);
		PasswordText.setBounds(135, 106, 290, 25);

		// add button, text, and labels...

		add (ConnectButton);
		add (ClearQuery);
		add (ExecuteButton);
		add (ClearWindow);
		add (QueryLabel);
		add (sqlSquare);
		add (dbInfoLabel);
		add (JbdcLabel);
		add (UrlLabel);
		add (UserLabel);
		add (PasswordLabel);
		add (DriverCombo);
		add (UrlCombo);
		add (UserText);
		add (PasswordText);
		add (StatusLabel);
		add (WindowLabel);
		add (square);

		// Action Listeners

		// "Connect Button"
		ConnectButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				try {
					// If already connected, close previous connection
					if (connect != null)
						connect.close();
					
					// Display status message when not connected
					StatusLabel.setText("No connection now");
					
					// Load JBDC driver
					Class.forName((String)DriverCombo.getSelectedItem());
					
					// Establish a connection
					connect = DriverManager.getConnection((String)UrlCombo.getSelectedItem(),UserText.getText(),PasswordText.getText());
					
					// Display status message when connected
					StatusLabel.setText("Connected to " + (String)UrlCombo.getSelectedItem());
				}
				catch (SQLException e) {
					JOptionPane.showMessageDialog(null, e.getMessage(), "Database error", JOptionPane.ERROR_MESSAGE);
				}
				catch (ClassNotFoundException classnotfound) {
					JOptionPane.showMessageDialog(SQLClientApp.this, "Error! Driver not found");
				}
			}
		});
		
		
		// "Clear Result Window" button
		ClearWindow.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				// Clear the results displayed in the window
				resultTable.setModel(Empty);
			}
		});
		
		// "Clear Query" Button
		ClearQuery.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				TextQuery.setText("");
			}
		});
		
		// "Execute" Button
		ExecuteButton.addActionListener(new ActionListener() 
		{
			public void actionPerformed(ActionEvent event) 
			{
				try 
				{
				
					// activate result table
					resultTable.setEnabled(true);
					
					// scrolling - set auto scrolling on
					resultTable.setAutoscrolls(true);
					
					// create tableModel for results
					ResultSetTableModel resultSet = new ResultSetTableModel(connect, TextQuery.getText());
					// JTable = resultTable
					
					// tableModel = resultSet
					// results.setModel(resultSet);
					//LuckerCode26
					//select * from riders
					
					// If select statement is used, use executeQuery()
					// All other command types will use executeUpdate() from the ResultSetTableModel helper class
					// New window will pop up with the message for user that does not have permission
					
					if (TextQuery.getText().toLowerCase().charAt(0) == 's' 
						&& TextQuery.getText().toLowerCase().charAt(1) == 'e'
						&& TextQuery.getText().toLowerCase().charAt(2) == 'l'
						&& TextQuery.getText().toLowerCase().charAt(3) == 'e'
						&& TextQuery.getText().toLowerCase().charAt(4) == 'c'
						&& TextQuery.getText().toLowerCase().charAt(5) == 't')
					{
						resultSet.setQuery(TextQuery.getText());
						resultTable.setModel(resultSet);
					}
					else
					{
						resultSet.setUpdate(TextQuery.getText());
						resultTable.setModel(resultSet);
					}

				}
				// catch database error
				catch (SQLException e) 
				{
					JOptionPane.showMessageDialog(null, e.getMessage(), "Database error", JOptionPane.ERROR_MESSAGE);
				}
				
				// catch driver error
				catch (ClassNotFoundException NotFound) 
				{
					JOptionPane.showMessageDialog(null, "MysSQL driver not found", "Driver not found", JOptionPane.ERROR_MESSAGE);
				}
			}
		
		});
	}
	
	
	public static void main( String args[] ) 
	{
	    // new JFrame
		JFrame frame = new JFrame ("Project 2 - SQL Client App - (CNT4714 - Summer 2021 - Artem Ivanov)");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//Create GUI instance
		frame.getContentPane().add(new SQLClientApp());
		frame.pack();
		frame.setLocationRelativeTo(null);
		//show GUI
		frame.show();
	} 
}
