import java.util.*;

import java.io.*;

public class NetworkExample
{
    public static void main (String[] args)
    {
        new NetworkExample().run();
    } // main
    
    public void run()
    {       
        final String SHORTEST_PATH_MESSAGE1 = "\n\nThe shortest path from ";
        final String SHORTEST_PATH_MESSAGE2 = " and its total weight are ";
        final String REMOVAL_MESSAGE = "\niterating over network after removing B-E and D:";
        
        Network<String> network = new Network<String>();
        
        try
        {
            Scanner sc = new Scanner (new File ("network.in1"));
            
            String start,
                   finish,
                   vertex1,
                   vertex2;
        
            double weight;
        
            // Get start and finish vertices.           
            start = sc.next();
            finish = sc.next();
            
            // Get edges and weights.
            while (sc.hasNext())
            {              
                vertex1 = sc.next();
                vertex2 = sc.next();
                weight = sc.nextDouble();
                network.addEdge (vertex1, vertex2, weight);
            } // while
            
            LinkedList<Object> pathList = network.getShortestPath (start, finish);
            System.out.println (SHORTEST_PATH_MESSAGE1 + start + " to " +
                                finish + SHORTEST_PATH_MESSAGE2 + pathList);
                                   
            boolean networkIsConnected = network.isConnected();
            System.out.println ("is connected: " + networkIsConnected);
            if (networkIsConnected)
                System.out.println ("spanning tree: " + network.getMinimumSpanningTree());
            
            System.out.println ("neighbors of " + start + ": " + network.neighbors (start));            
            System.out.println ("is empty: " + network.isEmpty());
            System.out.println ("vertex count: " + network.size());
            System.out.println ("edge count: " + network.getEdgeCount());
            System.out.println ("contains Q:  " + network.containsVertex ("Q"));
            System.out.println ("contains edge B-D: " + network.containsEdge ("B", "D"));
            System.out.println ("contains edge F-C: " + network.containsEdge ("F", "C"));
            System.out.println ("edge weight of A-B: " +
                                network.getEdgeWeight ("A", "B"));

            System.out.println ("\nbreadth-first iterating from " + start + ": ");
            Iterator<String> itr = network.breadthFirstIterator (start);
            while (itr.hasNext())
                System.out.print (itr.next() + " ");
            
            System.out.println ("\ndepth-first iterating from " + start + ": ");
            itr = network.depthFirstIterator (start);
            while (itr.hasNext())
                System.out.print (itr.next() + " ");
            
            System.out.println ("\niterating over network:");
            for (String s : network)
                System.out.print (s + " ");
            
            network.removeEdge ("B", "E");
            network.removeVertex ("D");
            System.out.println (REMOVAL_MESSAGE);
            for (String s : network)
                System.out.print (s + " ");            
            
            pathList = network.getShortestPath (start, finish);
            System.out.println (SHORTEST_PATH_MESSAGE1 + start + " to " +
                                finish + SHORTEST_PATH_MESSAGE2 + pathList);
        } // try
        catch (FileNotFoundException e)
        {
            System.out.println (e);
        } // catch
    } // method run
} // class NetworkExample
