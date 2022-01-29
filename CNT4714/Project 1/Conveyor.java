/*
 * Name: Artem Ivanov
 * Course: CNT4714 Summer 2021
 * Assignment title: Project 1–Multi-threaded programming in Java
 * Date:June 6, 2021
 * Class: Conveyor
*/

package dev;

import java.util.concurrent.locks.*;

public class Conveyor {
	
	int conveyorNum;
	
	// Creating lock on the conveyor instance - no fairness policy needed
	private Lock theLock = new ReentrantLock();
	
	// Constructor - gives the conv its number
	public Conveyor(int conveyorNum) {
		this.conveyorNum = conveyorNum;
	}
	
	// method for routing stations to get lock - utilize tryLock() from ReentrantLock class
	// returns true if the lock was free and thus acquired by the invocation (request) - otherwise
	// returns false.
	public boolean getLock() {
		//if get-the-lock
		if (theLock.tryLock()) {
			return true; // testing purposes only - replace with test using tryLock()
		}
		else {
			return false;
		}
		// otherwise return false 
	} // end getLock() method
	
	public void unlockConveyor() {
		// unlock the lock
		theLock.unlock();
	} // end unLockConveyor() method
} // end Conveyor class
