// Artem Ivanov
// COP 3503, Fall 2019

import java.util.*;
import java.lang.*;

public class RunLikeHell
{

	// Returns the biggest possible sum of values. (according to requirments)
	public static int maxGain(int [] blocks)
	{
		int len = blocks.length;
		int [] algorithmist = new int [len];

		// Checks if our input is more than 2 blocks.
		if (len < 2)
			return blocks[0];

		// Base cases for last and pre-last indexes.
		algorithmist[len-1] = blocks[len-1];
		algorithmist[len-2] = Math.max(blocks[len-1], blocks[len-2]);

		// Doing our for loop in reverse order. (from bottom to top)
		// Ends up with the highest possible sum of values. (according to requirments)
		for (int i = len - 3; i >= 0; i--)
		{
			algorithmist[i] = Math.max(blocks[i] + algorithmist[i+2], algorithmist[i+1]);
		}

		// Returns sum.
		return algorithmist[0];
	}
}
