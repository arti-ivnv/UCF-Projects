/*
 * @author Artem Ivanov
 * Assignment8
 * Program is doing:
    Application that works with list. Adding numbers from 1 to 5 and also doing sorting.
 */

package listapp.java;


public class GenLinkedList<T extends Number>
{
    class ListNode
    {

        // Instance of variables
        private T element;
        private ListNode next;


        //Constructor
        public ListNode(T element)
        {
            this.element = element;
            this.next = null;
        }

        @Override
        public String toString()
        {
            return "" + element;
        }
    }

    // Instance variable for LinkedList
    private ListNode head;
    private int size;
    private Num_Comparator comp;


    //Constructor
    public GenLinkedList()
    {
        this.head = null;
        this.size = 0;
        this.comp = new Num_Comparator();
    }



    //This function is adding a new node to the list in ascending order
    public void insertItem(T element)
    {

        // Create new node
        ListNode newNode = new ListNode(element);

        // Check if list is null
        if (this.size == 0)
        {
            // Set newNode as the head
            this.head = newNode;
        }
        else
        {
            // Check if element is less than head
            if (this.comp.compare(element, this.head.element) < 0)
            {

                   // Set newnode.next as head
                   newNode.next = this.head;

                   // Set newNode as head
                   this.head = newNode;
            }
            else
            {
                // If list is not null
                boolean added = false;

                // Get the head node
                ListNode node = this.head;

                while (!added && (node.next != null))
                {

                    // Compare element with element at node
                    int res = this.comp.compare(element, node.next.element);

                    // If element is less than or equal
                    // to the element at node.next
                    if (res <= 0)
                    {
                        // Set newNode.next as node.next
                        newNode.next = node.next;

                        // Set node.next as newNode
                        node.next = newNode;

                        added = true;
                    }

                    // Go to next node
                    node = node.next;
                }

                // Check if node was not added
                if (!added)
                {
                    if (this.comp.compare(element, node.element) != 0)
                    {
                           // Set node.next as newNode
                           node.next = newNode;
                    }
                }
            }
        }
        // Increment count
        this.size += 1;
    }



    //This function prints the list
    public String printList()
    {
        if (this.size == 0)
          return "";
        else
        {
          StringBuffer sb = new StringBuffer();
          ListNode node = this.head;

          // Append first node
          sb.append(node);
          node = node.next;

          while (node != null)
          {
              sb.append(" -> " + node);
              node = node.next;
          }
          return sb.toString();
        }
    }



    //This is clearing the list
    public void clearList()
    {
        this.head = null;
        this.size = 0;
    }
}
