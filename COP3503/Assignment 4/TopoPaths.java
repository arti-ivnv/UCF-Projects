// Artem Ivanov
// COP 3503, Fall 2019

import java.util.*;
import java.io.*;


public class TopoPaths
{

	// Method returns 1 if there is a topoPath else 0
	// Some of the features had been taken form toposort.java by Dr.Szumlanski
	public static int topoPath(int graphSize, ArrayList<ArrayList<Integer>> adjacencyList)
	{
		// checky[] array shows the amount of incomes to each vertex.
		int [] checky = new int[graphSize];
		int unq = 0;
		int unq2 = 0;
		int count = 0;

		// Initializing checky[] array using adjacency List structure.
		// This approach was created by Dr.Szumlanski with adjacency martrix.
		for (int i = 0; i < graphSize; i++)
		{
			if (adjacencyList.get(i).isEmpty())
			{
				checky[i] += 0;
			}
			else
			{
				for (int j = 0; j < adjacencyList.get(i).size(); j++)
				{
					checky[(adjacencyList.get(i).get(j) - 1)] += 1;
				}
			}
		}

		// Searching for vertices with zero incoming edges.
		// If more or less than 1 such vertices than there is not a TopoPath.
		for (int i = 0; i < graphSize; i++)
		{
			if (checky[i] == 0)
			{
				unq++;

				if (unq != 1)
					return 0;
			}
		}

		// Searching for a starting unique vertex.
		for (int i = 0; i < graphSize; i++)
		{
			// Checks that the vertex has no incomes.
			// Flags a new unique vertex as -1.
			if (checky[i] == 0)
			{
				count++;
				checky[i] = -1;

				// Decreasing adjecent amount to the specific indexes of checky[].
				for (int j = 0; j < adjacencyList.get(i).size(); j++)
				{
					checky[adjacencyList.get(i).get(j) - 1]--;
				}
				break;
			}

			// If there is no unique index at all than there is not topoPath.
			if (checky[i] != 0 && (i == graphSize - 1))
			{
				return 0;
			}
		}

		// Checks again if all vertices are adjecent.
		for (int i = 0; i < graphSize; i++)
		{
			if (checky[i] == 0)
			{
				unq2++;

				if (unq2 != 1)
					return 0;
			}
		}

		// Searching for a new unique vertex
		for (int i = 0; i < graphSize; i++)
		{
			// Checks if i-th vertex can be identified as a unique (no incomes)
			if (checky[i] == 0)
			{
				count++;
				checky[i] = -1;

				for (int j = 0; j < adjacencyList.get(i).size(); j++)
				{
					checky[adjacencyList.get(i).get(j) - 1]--;
				}
			}
		}

		// Checks if there is a cycle in the graph
		if (count != graphSize)
			return 0;

		return 1;
	}

	// Reads the file. Creates adjacency List.
	public static int countTopoPaths(String filename) throws IOException
	{
		Scanner inputFile = new Scanner(new File(filename));

		// Amount of vertices.
		int graphSize = inputFile.nextInt();
		int adjacentAmount;

		ArrayList<ArrayList<Integer>> adjacencyList = new ArrayList<>(graphSize);

		// Filling up adjacency list by the numbers from input file.
		for (int i = 0; i < graphSize; i++)
		{
			adjacentAmount = inputFile.nextInt();
			ArrayList<Integer> vertex = new ArrayList<>(adjacentAmount);
			adjacencyList.add(vertex);

			for (int j = 0; j < adjacentAmount; j++)
			{
				adjacencyList.get(i).add(inputFile.nextInt());
			}
		}

		// Checks if topoPath is possible within current graph.
		if (topoPath(graphSize, adjacencyList) == 0)
			return 0;

		return 1;
	}
}
