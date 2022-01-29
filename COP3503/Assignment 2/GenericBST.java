// Artem Ivanov
// COP 3503, Fall 2019

import java.io.*;
import java.util.*;

// Generic class for Node
class Node<T>
{
	T data;
	Node<T> left, right;

	Node(T data)
	{
		this.data = data;
	}
}

// Generic class for GenericBST that deals with BST in Generic form
public class GenericBST<Shrek extends Comparable<Shrek>>
{
	private Node<Shrek> root;

	// Helper method for insert method
	public void insert(Shrek data)
	{
		root = insert(root, data);
	}

	// Recursive private method that inserts generic Nodes into GenericBST
	private Node<Shrek> insert(Node<Shrek> root, Shrek data)
	{
		if (root == null)
		{
			return new Node<Shrek>(data);
		}
		else if (data.compareTo(root.data) < 0)
		{
			root.left = insert(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			root.right = insert(root.right, data);
		}

		return root;
	}

	// Helper method for delete method
	public void delete(Shrek data)
	{
		root = delete(root, data);
	}

	// Recursive private method that deletes generic Nodes from GenericBST
	private Node<Shrek> delete(Node<Shrek> root, Shrek data)
	{
		if (root == null)
		{
			return null;
		}
		else if (data.compareTo(root.data) < 0)
		{
			root.left = delete(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			root.right = delete(root.right, data);
		}
		else
		{
			if (root.left == null && root.right == null)
			{
				return null;
			}
			else if (root.left == null)
			{
				return root.right;
			}
			else if (root.right == null)
			{
				return root.left;
			}
			else
			{
				root.data = findMax(root.left);
				root.left = delete(root.left, root.data);
			}
		}

		return root;
	}

	// This method assumes root is non-null, since this is only called by
	// delete() on the left subtree, and only when that subtree is not empty.
	private Shrek findMax(Node<Shrek> root)
	{
		while (root.right != null)
		{
			root = root.right;
		}

		return root.data;
	}

	// Helper method for contains method
	public boolean contains(Shrek data)
	{
		return contains(root, data);
	}

	// Recursively parses the BST and looking for a specific object/data
	private boolean contains(Node<Shrek> root, Shrek data)
	{
		if (root == null)
		{
			return false;
		}
		else if (data.compareTo(root.data) < 0)
		{
			return contains(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			return contains(root.right, data);
		}
		else
		{
			return true;
		}
	}

	// Helper method for inorder traversal
	public void inorder()
	{
		System.out.print("In-order Traversal:");
		inorder(root);
		System.out.println();
	}

	// Algorithm method for inorder traversal
	// Recursively parses the BST and print data in inorder traversal form
	private void inorder(Node<Shrek> root)
	{
		if (root == null)
			return;

		inorder(root.left);
		System.out.print(" " + root.data);
		inorder(root.right);
	}

	// Helper method for preorder traversal
	public void preorder()
	{
		System.out.print("Pre-order Traversal:");
		preorder(root);
		System.out.println();
	}

	// Algorithm method for preorder traversal
	// Recursively parses the BST and print data in preorder traversal form
	private void preorder(Node<Shrek> root)
	{
		if (root == null)
			return;

		System.out.print(" " + root.data);
		preorder(root.left);
		preorder(root.right);
	}

	// Helper method for postorder traversal
	public void postorder()
	{
		System.out.print("Post-order Traversal:");
		postorder(root);
		System.out.println();
	}

	// Algorithm method for preorder traversal
	// Recursively parses the BST and print data in postorder traversal form
	private void postorder(Node<Shrek> root)
	{
		if (root == null)
			return;

		postorder(root.left);
		postorder(root.right);
		System.out.print(" " + root.data);
	}

}
