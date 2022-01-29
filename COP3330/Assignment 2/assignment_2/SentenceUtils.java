package assignment_2;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *@author Artem Ivanov
 * Assignment 2
 * Divides each token in a string into letter groups specified size and then counts how many times the groups were used.
 */

class Histogram{

    private HashMap<String, Integer> mHistogram;

    public Histogram(){
        this.mHistogram = new HashMap<>();
    }

    /*
    This function counts the number of occurence of each letter group
    input: letter groups
    output: histogram

    example: input: ["an","an","or","or","or"]
             output: [<"an",2>, <"or",3>]
    */
    public void generateHistogram(ArrayList<String> letterGroups)
    {

        /*
            Loop through lettergroups and add it to a hashmap if it is not already there with value 1.
            Otherwise, add 1 to value of the element of lettergroups
        */

        for(String s : letterGroups)
        {
            if(this.mHistogram.get(s) == null)
                this.mHistogram.put(s, 1);
            else
                this.mHistogram.put(s, this.mHistogram.get(s) + 1);
        }
    }

    /*
    This function prints the histogram
    input: histogram
    output: histogram printed on the display

    example: input: [<"an",2>, <"or",3>]
             output:

    an: **
    or: ***

    */
    public void printHistogram()
    {
        /*
              Print the right number of stars
        */

        for(String key : this.mHistogram.keySet()) {
            System.out.print(key + ": ");
            for(int i = 0; i < this.mHistogram.get(key); i++) {
                System.out.print("*");
            }
            System.out.println();
        }
    }

}





public class SentenceUtils {
    private ArrayList<String> mLetterGroups;
    private int mLetterGroupLen;

    public SentenceUtils(int letterGroupLen){
        this.mLetterGroups = new ArrayList<>();
        this.mLetterGroupLen = letterGroupLen;
    }
    public void addWords(String line){

        String[] tokens = this.getTokens(line);
        this.splitTokenstoLetterGroups(tokens);
    }
    public ArrayList<String> getLetterGroups(){
        return (this.mLetterGroups);
    }

    /*
    This function splits a string into array of strings separated by space
    character
    input: a string
    output: array of words seperated by space character

    example: input: "object oriented"
             output: ["object", "oriented"]
    */
    private String[] getTokens(String line)
    {
        /*
            Split the string whenever there is a space
        */
        String[] arr = line.split(" ");
        for(int i = 0; i < arr.length; i++)
        {
            arr[i] = arr[i].toLowerCase();
        }
        return arr;
    }

    /*
    This function splits the tokens into letter groups according to
    this.mLetterGroupLen
    input: array of tokens
    output: letterGroups of size this.mLetterGroupLen appended to
    this.mLetterGroups

    example: input: "object" "oriented"
             output: this.mLetterGroups (of size 4) = this.mLetterGroups +
                  ["obje","bjec", "ject","orie", "rien", "ient", "ente", "nted"]
    */
    private void splitTokenstoLetterGroups(String[] tokens)
    {
        /*
            spliting each tokens in the groups of size mLetterGroupLen
        */
        String s = "";

        for(String a : tokens)
        {
            for(int i = 0; i < a.length() - this.mLetterGroupLen + 1; i++)
            {
                for(int j = 0; j < this.mLetterGroupLen; j++)
                {
                    s += a.charAt(i + j);
                }
                this.mLetterGroups.add(s);
                s = "";
            }
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        /*
            You are going to implement to read the file and also to call appropriate functions to
            generate and print the histogram.

            Ensure that if a non-existing file is input to your program, your program do not cause
            an exception and halt.

            First argument is the filename, and the second argument is the letterGroupLength.
        */

        /*
        Reading the arguments
        */
        String filename = args[0];
        int letterGroupLength = Integer.parseInt(args[1]);

        //Checking your file exists
        BufferedReader reader = null;
        try
        {
            reader = new BufferedReader(new FileReader(new File(filename)));
        } catch (FileNotFoundException ex)
        {
            System.err.println("File \'" + filename + "\' was not found.  Try a different file maybe?");
            System.exit(1);
        }

        //reading the file into the list lines
        List<String> lines = new ArrayList<String>();
        String s;
        try
        {
            while((s = reader.readLine()) != null)
            {
                if(s.trim().length() > 0)
                lines.add(s);
            }
        } catch (IOException ex)
        {
            System.err.println("Error reading from \'" + filename + "\'...");
            System.exit(1);
        }

        SentenceUtils sentenceUtils;
        Histogram histogram;

        //Get the tokens, split the tokens, generate the histogram and print the histogram
        for(String a : lines)
        {
            sentenceUtils = new SentenceUtils(letterGroupLength);
            histogram = new Histogram();
            System.out.println("Input:");
            System.out.println(a);
            System.out.println("Output:");
            String[] tokens = sentenceUtils.getTokens(a);
            System.out.println("Tokens: " + Arrays.toString(tokens));
            sentenceUtils.splitTokenstoLetterGroups(tokens);
            System.out.println("Letter Groups: " + sentenceUtils.getLetterGroups().toString());
            histogram.generateHistogram(sentenceUtils.getLetterGroups());
            System.out.println("\nHistogram:");
            histogram.printHistogram();
            System.out.println();
        }
    }
}
