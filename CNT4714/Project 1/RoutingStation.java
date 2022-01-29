/*
 * Name: Artem Ivanov
 * Course: CNT4714 Summer 2021
 * Assignment title: Project 1–Multi-threaded programming in Java
 * Date:June 6, 2021
 * Class: RoutingStation
*/

package dev;

import java.util.Random;


public class RoutingStation implements Runnable {
	
	protected static int MAXSLEEP = 512;
	
	protected Random sleeptime = new Random();
	protected int stationNum;
	protected int workload;
	protected Conveyor inconveyor;
	protected Conveyor outconveyor;
	protected boolean bothLocks = false;
	protected int workLoadCounter;
	
	public RoutingStation(int stationNum, int workload, Conveyor inconveyor, Conveyor outconveyor) {
		this.stationNum = stationNum;
		this.workload = workload;
		this.inconveyor = inconveyor;
		this.outconveyor = outconveyor;
		workLoadCounter = workload;
	}
	
	// Method for routing station threads to go to sleep - simulates random time behavior
	public void goToSleep() {
		try {
			// Simulating random time between 1 - MAXSLEEP msec
			Thread.sleep(sleeptime.nextInt(MAXSLEEP-1+1)+1);
		}
		catch(InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public void doWork() {
		 // print out messages that station in moving packages in a package group in and out of the station
		System.out.println("Station " + this.stationNum + ": . . . Active. . . moving packages into station on input conveyor "+ this.inconveyor.conveyorNum + ".");
		System.out.println("Station " + this.stationNum + ": . . . Active. . . moving packages out of station on output conveyor " + this.outconveyor.conveyorNum + ".");
		
		
		// decrement the station's workload
		workLoadCounter--; 
		
		this.inconveyor.unlockConveyor();
		this.outconveyor.unlockConveyor();
		
		goToSleep();
		
	}
	
	public void run() {
		// print out messages for input and output conveyor assignments
		System.out.println("Routing Station " + this.stationNum + ": Input connection is set to conveyor number " + this.inconveyor.conveyorNum +  ".");
		System.out.println("Routing Station " + this.stationNum + ": Input connection is set to conveyor number " + this.outconveyor.conveyorNum +  ".");
		// print out message showing station's initial workload
		System.out.println("Routing Station "+ this.stationNum + ": Workload set. Station " + this.stationNum + " has a total of " + workLoadCounter + " package groups to move.");
		
		// TODO:
		// loop that runs for routing stations workload (workLoadCounter)
			// initially set variable bothlocks to indicate station holding both needed conveyor locks to false - it doesn't hold any yet
			// loop as long as both locks acquired
				// try to get output lock
				// if both locks true - set bothlocks variable to true
					// then
							// doWork()
							// release both locks
							// print message about lock release
							// print message about workload remaining
					// else	// didn't get both locks - need to release input conveyor lock
							// print message about not getting output conveyor lock and releasing input conveyor
							// sleep the station for a while to simulate waiting for another station to do work
			// end all loops

		while(workLoadCounter != 0) {
			
			boolean bothLocks = false;
			while(bothLocks == false) {
				
				if(this.inconveyor.getLock() == true) {
					
					System.out.println("Station "+ this.stationNum +": LOCK ACQUIRED! Now holding lock on input conveyor "+ this.inconveyor.conveyorNum +".");
					
					if(this.outconveyor.getLock() == true) {
						System.out.println("Station " + this.stationNum +": LOCK ACQUIRED! Now holding lock on output conveyor "+ this.outconveyor.conveyorNum +".");
						bothLocks = true;
						doWork();
						
						System.out.println("Station " + this.stationNum + ": Unlocks input conveyor " + this.inconveyor.conveyorNum + ".");
						System.out.println("Station " + this.stationNum + ": Unlocks output conveyor " + this.outconveyor.conveyorNum + ".");
						System.out.println("Station" + this.stationNum + ": Number of packages groups left to move is: " + this.workload + ".");
						System.out.println();
						
						if (workLoadCounter == 0) {
							System.out.println("\n\n* * Station "+ this.stationNum +": Workload successfully completed. * * Station Going Idle!\n\n");
						}
					}
					else {
						inconveyor.unlockConveyor();
						System.out.println("Station" + this.stationNum + ": Unable to lock output conveyor "+ this.outconveyor.conveyorNum +" – releasing lock on input conveyor "+ this.inconveyor.conveyorNum +".");
						goToSleep();
					}
				}
			}
			
			
		}
	}

}
