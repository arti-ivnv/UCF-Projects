/*
 * Name: Artem Ivanov
 * Course: CNT4714 Summer 2021
 * Assignment title: Project 1–Multi-threaded programming in Java
 * Date:June 6, 2021
 * Class: PackageManagement
*/

package dev;

import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class PackageManagement {
	
	// Max of conv and stations
	static int MAX = 10;

	public static void main(String[] args) {
		try {
			System.out.println("\n CNT 4713 - Project 1 - Summer 2021 \n");
			System.out.println("\n * * * SIMULATION BEGINS * * * \n");
			
			// Reading the config.txt file
			Scanner file = new Scanner(new File("config.txt"));
			
			// Array list to store the integers from config.txt
			ArrayList<Integer> config = new ArrayList<Integer>();
			
			// Create thread pool of MAX size
			ExecutorService application = Executors.newFixedThreadPool(MAX);
			
			// Read file into array - get the simulation scenario for this simulation run
			while(file.hasNext()) {
				int number = file.nextInt();
				config.add(number);
			}
			
			// Close config.txt
			file.close();
			
			// Save the first integer as number of routing stations
			int numberOfRoutingStations = config.get(0);
			
			// TODO: 
			// Creating array of conveyors
			Conveyor[] conveyors = new Conveyor[numberOfRoutingStations];

			
			// Filling array of conveyors
			// Workloads
			for (int i = 0; i < numberOfRoutingStations; i++) {
				conveyors[i] = new Conveyor(i);
			}
			
			
			// Creating the routing stations
			for (int i = 0; i < numberOfRoutingStations; i++) {
				try {
					// calling station constructor and starts the RoutingStation threads
					application.execute(new RoutingStation(i, config.get(i+1), conveyors[i], conveyors[(i + numberOfRoutingStations - 1) % numberOfRoutingStations]));
				}
				
				catch(Exception e) {
					e.printStackTrace();
				}
			}
			
			application.shutdown();
			
			// application shutdown
			while (!application.isTerminated()) {
				
				// Simulation running
				
			}
			
			
			System.out.println("\n * * * * ALL WORKLOADS COMPLETE * * * SIMULATION ENDS * * * *");
		}
		catch(FileNotFoundException e) {
			System.out.println("file not found");
		}
		
	}

}
