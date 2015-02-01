/*
 * Modificare il metodo
 * LinkedList<Object> getShortestPath (Vertex v1, Vertex v2)
 * in modo da restituire l’albero dei cammini minimi radicato in v1
 * UndirectedWeightedTree<Vertex>   getShortestPaths (Vertex v1)
 */
/*
    * Modificare il metodo UndirectedWeightedTree<Vertex>.getMinimumSpanningTree()
    * in modo da restituire solo un valore double che rappresenta il peso totale di un minimo spanning tree
    */

import java.util.*;

public class Network<Vertex> implements Iterable<Vertex>
{    
    protected TreeMap<Vertex, TreeMap<Vertex, Double>> adjacencyMap;        
   
    /**
     *  Initializes this Network object to be empty, with the ordering of
     *  vertices by an implementation of the Comparable interface.
     */
    public Network()
    {        
        adjacencyMap = new TreeMap<Vertex, TreeMap<Vertex, Double>>();        
    } // default constructor

       
    /**
     *  Initializes this Network object to a shallow copy of a specified Network
     *  object.    
     *
     *  @param network - the Network object that this Network object is
     *                   initialized to a shallow copy of.
     * 
     *  @throws NullPointerException if network is null.
     *
     */
    public Network (Network<Vertex> network)
    {
        adjacencyMap = new TreeMap<Vertex, TreeMap<Vertex, Double>>(network.adjacencyMap);
    } // copy constructor

    /**
     *  Determines if this Network object is equal to a given object. 
     * 
     *  @param obj - the object this Network object is compared to.
     *
     *  @return true - if this Network object is equal to obj.
     *
     */
    public boolean equals (Object obj)
    {
        if (!(obj instanceof Network))
            return false;
        Network<Vertex> other = (Network<Vertex>)obj;
        
        return adjacencyMap.equals (other.adjacencyMap);
    } // method equals
                
    /**
     *  Determines if this Network object contains no vertices.
     *
     *  @return true - if this Network object contains no vertices.
     *
     */
    public boolean isEmpty()
    {
        return adjacencyMap.isEmpty();
    } // method isEmpty

 
    /**
     *  Determines the number of vertices in this Network object.
     *
     *  @return the number of vertices in this Network object.
     *
     */
    public int size()
    {
        return adjacencyMap.size();
    } // method size


    /**
     *  Returns the number of edges in this Network object.
     *  The worstTime(V, E) is O(V).
     *
     *  @return the number of edges in this Network object.
     *
     */
    public int getEdgeCount()
    {
        int count = 0;

        for (Map.Entry<Vertex, TreeMap<Vertex, Double>> entry : adjacencyMap.entrySet())
            count += entry.getValue().size();
        return count;
    } // method getEdgeCount


    /**
     *  Determines the weight of an edge in this Network object.
     *  The worstTime (V, E) is O(log V).
     *
     *  @param v1 - the beginning Vertex object of the edge whose weight is sought.
     *  @param v2 - the ending Vertex object of the edge whose weight is sought.
     *
     *  @return the weight of edge <v1, v2>, if <v1, v2> forms an edge; return -1.0 if
     *                <v1, v2> does not form an edge in this Network object.
     *
     *  @throws NullPointerException if v1 and/or v2 is null. 
     */
    public double getEdgeWeight (Vertex v1, Vertex v2)
    {
        if (v1 == null || v2 == null)
            throw new NullPointerException();
        if (! (adjacencyMap.containsKey (v1) && adjacencyMap.containsKey (v2)))
            return -1.0;

        TreeMap<Vertex, Double> neighborMap = adjacencyMap.get (v1);
        Double weight = neighborMap.get (v2);
        if (weight != null)
           return weight;
        return -1.0;  // there is no edge <v1, v2>
    } // method getEdgeWeight


    /**
     *  Determines if this Network object contains a specified Vertex object.
     *  The worstTime(V, E) is O(log V).
     *
     *  @param vertex - the Vertex object whose presence is sought.
     *
     *  @return true - if vertex is an element of this Network object.
     * 
     *  @throws NullPointerException if vertex is null.
     */
    public boolean containsVertex (Vertex vertex)
    {
        return adjacencyMap.containsKey (vertex);
    } // method containsVertex


    /**
     *  Determines if this Network object contains an edge specified by two vertices.
     *  The worstTime (V, E) is O(log V).
     *
     *  @param v1 - the beginning Vertex object of the edge sought.
     *  @param v2 - the ending Vertex object of the edge sought.
     *
     *  @return true - if this Network object contains the edge <v1, v2>.
     *
     *  @throws NullPointerException if v1 and/or v2 is null.
     * 
     */
    public boolean containsEdge (Vertex v1, Vertex v2)
    {
        return getEdgeWeight (v1, v2) > 0.0;
    } // method containsEdge


    /**
     *  Ensures that a specified Vertex object is an element of this Network object.
     *  The worstTime(V, E) is O(log V).
     *
     *  @param vertex - the Vertex object whose presence is ensured.
     *
     *  @return true - if vertex was added to this Network object by this call; returns
     *               false if vertex was already an element of this Network object when
     *               this call was made.
     * 
     *  @throws NullPointerException if vertex is null.
     * 
     */
    public boolean addVertex (Vertex vertex)
    {     
        if (adjacencyMap.containsKey (vertex))
            return false;
        adjacencyMap.put (vertex, new TreeMap<Vertex, Double>());
        return true;
    } // method addVertex



    /**
     *  Ensures that an edge is in this Network object.
     *  The worstTime(V, E) is O(log V).
     *
     *  @param v1 - the beginning Vertex object of the edge whose presence
     *                         is ensured.
     *  @param v2 - the ending Vertex object of the edge whose presence is
     *                        ensured.
     *  @param weight - the weight of the edge whose presence is ensured.
     *
     *  @return true - if the given edge (and weight) were added to this Network
     *                         object by this call; return false, if the given edge (and weight)
     *                         were already in this Network object when this call was made.
     *
     *  @throws NullPointerException if v1 and/or v2 is null.
     * 
     */
    public boolean addEdge (Vertex v1, Vertex v2, double weight)
    {
        if (containsEdge (v1, v2))
            return false;
        addVertex (v1);
        addVertex (v2);      
        TreeMap<Vertex, Double> neighborMap = adjacencyMap.get (v1);       
        neighborMap.put (v2, weight);
        adjacencyMap.put (v1, neighborMap);      
        return true;
    } // method addEdge


    /**
     *  Ensures that a specified Vertex object is not an element of this Network object.
     *  The worstTime (V, E) is O (V log V).
     *
     *  @param vertex - the Vertex object whose absence is ensured.
     *
     *  @return true - if vertex was removed from this Network object by this call;
     *                returns false if vertex was not an element of this Network object
     *                when this call was made.
     * 
     *  @throws NullPointerException if vertex is null.
     * 
     */
    public boolean removeVertex (Vertex vertex)
    {
        if (!adjacencyMap.containsKey (vertex))
            return false;

        for (Map.Entry<Vertex, TreeMap<Vertex, Double>> entry: adjacencyMap.entrySet()) 
        {
            TreeMap<Vertex, Double> neighborMap = entry.getValue();

            neighborMap.remove (vertex);            
        } // for each vertex in the network
        adjacencyMap.remove (vertex);
        return true;
    } // removeVertex

    /**
     *  Ensures that an edge specified by two vertices is absent from this Network
     *  object.
     *  The worstTime (V, E) is O (log V).
     *
     *  @param v1 -   the beginning Vertex object of the edge whose absence is
     *                          ensured.
     *  @param v2 - the ending Vertex object of the edge whose absence is
     *                        ensured.
     *
     *  @return true - if the edge <v1, v2> was removed from this Network object
     *                          by this call; return false if the edge <v1, v2> was not in this
     *                          Network object when this call was made.
     * 
     *  @throws NullPointerException if v1 and/or v2 is null.
     *
     */
    public boolean removeEdge (Vertex v1, Vertex v2)
    {
        if (v1 == null || v2 == null)
            throw new NullPointerException();
        if (!adjacencyMap.containsKey (v1) || !adjacencyMap.containsKey (v2))
            return false;

       TreeMap<Vertex, Double> neighborMap = adjacencyMap.get (v1);
       if (!neighborMap.containsKey (v2))  
           return false;
       neighborMap.remove (v2);
       return true;
    } // method removeEdge


    /**
     *  Returns a LinkedList<Vertex> object of the neighbors of a specified Vertex object.
     *  The worstTime(V, E) is O(V).
     *
     *  @param v - the Vertex object whose neighbors are returned.
     *
     *  @return a LinkedList<Vertex> object of the vertices that are neighbors of v.
     * 
     *  @throws NullPointerException - if v is null.
     * 
     */
    public LinkedList<Vertex> neighbors (Vertex v)
    {        
        return new LinkedList<Vertex> (adjacencyMap.get (v).keySet());   
    } // method neighbors

    /**
     *  Re-initializes this Network object to be empty.
     */
    public void clear()
    {
        adjacencyMap.clear();
    } // method clear


    /**
     *  Returns an Iterator object over the vertices in this Network object.
     *
     *  @return an Iterator object over the vertices in this Network object.
     *
     */
    public Iterator<Vertex> iterator()
    {
        return new NetworkIterator();
    } // method iterator



    /**
     *  Returns a breadth-first Iterator object over all vertices reachable from
     *  a specified Vertex object.
     *  The worstTime(V, E) is O(V log V).
     *
     *  @param v - the start Vertex object for the Iterator object returned.
     *
     *  @return a  breadth-first Iterator object over all vertices reachable from v.
     *
     *  @throws IllegalArgumentException - if v is not an element of this Network
     *                 object.
     *
     *  @throws NullPointerException if v is null.
     * 
     */
    public Iterator<Vertex> breadthFirstIterator (Vertex v)
    {
        if (!adjacencyMap.containsKey (v))
            throw new IllegalArgumentException();
        return new BreadthFirstIterator(v);
    } // method breadthFirstIterator


    /**
     *  Returns a depth-first Iterator object over all vertices reachable from
     *  a specified Vertex object.
     *  The worstTime(V, E) is O(V log V).
     *
     *  @param v - the start Vertex object for the Iterator object returned.
     *
     *  @return a depth-first Iterator object over all vertices reachable from v.
     *
     *  @throws IllegalArgumentException - if v is not an element of this Network
     *                 object.
     *
     *  @throws NullPointerException if v is null.
     * 
     */
    public Iterator<Vertex> depthFirstIterator (Vertex v)
    {
        if (!adjacencyMap.containsKey (v))
            throw new IllegalArgumentException();
        return new DepthFirstIterator(v);
    } // method depthFirstIterator


    /**
     *  Determines if this (directed) Network object is connected.
     *  The worstTime(V, E) is O(V * V * log V).
     *
     *  @return true - if this (directed) Network object is connected.
     *
     */
    public boolean isConnected()
    {
        for (Vertex v : adjacencyMap.keySet())
        {
            // Count the vertices reachable from v.
            Iterator<Vertex> itr2 = new BreadthFirstIterator (v);
            int count = 0;
            while (itr2.hasNext())
            {
                itr2.next();
                count++;
            } // while
            if (count < adjacencyMap.size())
                return false;
        } // for
        return true;
    } // method isConnected


    /**
     *  Returns a minimum spanning tree for this connected Network object.
     *  The worstTime(V, E) is O(E log V).
     *
     *  @return a minimum spanning tree for this connected Network object.
     *     
     *  
     */
    public UndirectedWeightedTree<Vertex> getMinimumSpanningTree()
    {
        UndirectedWeightedTree<Vertex> tree = new UndirectedWeightedTree<Vertex>();

        PriorityQueue<EdgeTriple> pq = new PriorityQueue<EdgeTriple>();
		// EdgeTriple: <from, to, weight>

        EdgeTriple edgeTriple;
        Vertex root, w, x, y, z;
        Iterator<Vertex> netItr;
        double weight;

        if (isEmpty()) return tree;   
   
        netItr = adjacencyMap.keySet().iterator();
        root = netItr.next();
        tree.addVertex (root);       

        for (Map.Entry<Vertex, Double> entry : adjacencyMap.get (root).entrySet())
        {
            w = entry.getKey();
            weight = entry.getValue();
            edgeTriple = new EdgeTriple (root, w, weight);
            pq.add (edgeTriple);
        } // adding root's edgeTriples to pq
        while (tree.size() < size())
        {
            edgeTriple = pq.remove();
            x = edgeTriple.from;
            y = edgeTriple.to;
            weight = edgeTriple.weight;          
            if (!tree.containsVertex (y))
            {                
                tree.addEdge (x, y, weight);              
                for (Map.Entry<Vertex, Double> entry : adjacencyMap.get(y).entrySet())
                {
                    z = entry.getKey();
                    if (!tree.containsVertex (z))
                    {
                        weight = entry.getValue();
                        edgeTriple = new EdgeTriple (y, z, weight);
                        pq.add (edgeTriple);
                    } // z not already in tree
                } // iterating over y's neighbors
            } // y not already in tree
        } // tree has fewer vertices than this Network
        return tree;
    } // method getMinimumSpanningTree

    /*
    * Modificare il metodo UndirectedWeightedTree<Vertex>.getMinimumSpanningTree()
    * in modo da restituire solo un valore double che rappresenta il peso totale di un minimo spanning tree
    */
    public double getMinimumSpanningTreeWeigth() {
        //ALG: Quando dovrei aggiungere un vertice al MAR aggiorno totalweight
        UndirectedWeightedTree<Vertex> tree = new UndirectedWeightedTree<Vertex>();

        PriorityQueue<EdgeTriple> pq = new PriorityQueue<EdgeTriple>();
        // EdgeTriple: <from, to, weight>

        EdgeTriple edgeTriple;
        Vertex root, w, x, y, z;
        Iterator<Vertex> netItr;
        double weight;
        double totalweight = 0.0; //changed

        if (isEmpty()) return totalweight;   
   
        netItr = adjacencyMap.keySet().iterator();
        root = netItr.next();
        tree.addVertex(root);

        for (Map.Entry<Vertex, Double> entry : adjacencyMap.get (root).entrySet())
        {
            w = entry.getKey();
            weight = entry.getValue();
            edgeTriple = new EdgeTriple (root, w, weight);
            pq.add (edgeTriple);
        } // adding root's edgeTriples to pq
        while (tree.size() < size())
        {
            edgeTriple = pq.remove();
            x = edgeTriple.from;
            y = edgeTriple.to;
            weight = edgeTriple.weight;          
            if (!tree.containsVertex (y))
            {                
                tree.addEdge (x, y, weight);
                totalweight += weight; //changed              
                for (Map.Entry<Vertex, Double> entry : adjacencyMap.get(y).entrySet())
                {
                    z = entry.getKey();
                    if (!tree.containsVertex (z))
                    {
                        weight = entry.getValue();
                        edgeTriple = new EdgeTriple (y, z, weight);
                        pq.add (edgeTriple);
                    } // z not already in tree
                } // iterating over y's neighbors
            } // y not already in tree
        } // tree has fewer vertices than this Network
        return totalweight;
    }

    /**
     *  Finds a shortest path between two specified vertices in this Network
     *  object.
     *  The worstTime(V, E) is O(E log V).
     *
     *  @param v1 - the beginning Vertex object.
     *  @param v2 - the ending Vertex object.
     *
     *  @return a LinkedList object containing the vertices in a shortest path
     *                from Vertex v1 to Vertex v2.  The last element is the
     *                weight of the path, or -1.0 if there is no path.
     *
     */
    public LinkedList<Object> getShortestPath (Vertex v1, Vertex v2)
    {
        final double MAX_PATH_WEIGHT = Double.MAX_VALUE;

        TreeMap<Vertex,Double> weightSum = new TreeMap<Vertex,Double>(); //tabella D

        TreeMap<Vertex,Vertex> predecessor = new TreeMap<Vertex,Vertex>(); //path

        PriorityQueue<VertexWeightPair> pq = new PriorityQueue<VertexWeightPair>();
    
        Vertex vertex,
               to = null,
               from;

        VertexWeightPair vertexWeightPair;

        double weight;
 
        if (v1 == null || v2 == null)
            throw new NullPointerException();
        if (! (adjacencyMap.containsKey (v1) && adjacencyMap.containsKey (v2)))
            return new LinkedList<Object>();
        Iterator<Vertex> netItr = breadthFirstIterator(v1);
        while (netItr.hasNext()) 
        {
            vertex = netItr.next();
            weightSum.put (vertex, MAX_PATH_WEIGHT);
            predecessor.put (vertex, null);
        } // initializing weightSum and predecessor
        weightSum.put (v1, 0.0);
        predecessor.put (v1, v1);
        pq.add (new VertexWeightPair (v1, 0.0));

        boolean pathFound = false;
        while (!pathFound && !pq.isEmpty()) 
        {
            vertexWeightPair = pq.remove();
            from = vertexWeightPair.vertex;
            if (from.equals (v2))
                pathFound = true;
            else if (vertexWeightPair.weight <= weightSum.get(from)) 
            {                  
                for (Map.Entry<Vertex, Double> entry : adjacencyMap.get (from).entrySet())
                {
                     to = entry.getKey();
                     weight = entry.getValue();
                     if (weightSum.get (from) + weight < weightSum.get (to)) 
                     {
                         weightSum.put (to, weightSum.get (from) + weight);
                         predecessor.put (to, from);
                         pq.add (new VertexWeightPair (to,weightSum.get (to)));
                     } // if
                 } // while from's neighbors have not been processed
            } // else path not yet found
        } // while not done and priority queue not empty

        LinkedList<Object> path = new LinkedList<Object>();
        if (pathFound) 
        {
            Vertex current = v2;
            while (!(current.equals (v1))) 
            {
                path.addFirst (current);
                current = predecessor.get (current);
            } // while not back to v1
            path.addFirst (v1);
            path.addLast (weightSum.get (v2));
        } // if path found
        else
            path.addLast (-1.0);
        return path;
    } // method findShortestPath

    /*
     * Modificare il metodo
    * LinkedList<Object> getShortestPath (Vertex v1, Vertex v2)
    * in modo da restituire l’albero dei cammini minimi radicato in v1
    * UndirectedWeightedTree<Vertex>   getShortestPaths (Vertex v1)
    */
    public UndirectedWeightedTree<Vertex> getShortestPaths(Vertex v1) { //Dijkstra
        final double MAX_PATH_WEIGHT = Double.MAX_VALUE;
        TreeMap<Vertex,Double> weightSum = new TreeMap<Vertex,Double>();
        TreeMap<Vertex, Vertex> acm = new TreeMap<Vertex,Vertex>(); //acm, il vecchio "predecessor"
        UndirectedWeightedTree<Vertex> acmret = new UndirectedWeightedTree<Vertex>(); //acm+pesi
        PriorityQueue<VertexWeightPair> pq = new PriorityQueue<VertexWeightPair>();    
        Vertex vertex,
               to = null,
               from;
        VertexWeightPair vertexWeightPair;
        double weight;
 
        if (v1 == null)
            throw new NullPointerException();
        if (! adjacencyMap.containsKey (v1))
            return acmret;
        Iterator<Vertex> netItr = breadthFirstIterator(v1);
        while (netItr.hasNext()) 
        {
            vertex = netItr.next();
            weightSum.put (vertex, MAX_PATH_WEIGHT);
            acm.put (vertex, null);
            acmret.addVertex(vertex);
        } // initializing weightSum and predecessor
        weightSum.put (v1, 0.0);
        acm.put (v1, v1);
        pq.add (new VertexWeightPair (v1, 0.0));

        while (!pq.isEmpty()) 
        {
            vertexWeightPair = pq.remove();
            from = vertexWeightPair.vertex;
            if (vertexWeightPair.weight <= weightSum.get(from)) 
            {                  
                for (Map.Entry<Vertex, Double> entry : adjacencyMap.get (from).entrySet())
                {
                     to = entry.getKey();
                     weight = entry.getValue();
                     double relaxedWeigth = weightSum.get (from) + weight;
                     if (relaxedWeigth < weightSum.get (to)) 
                     {
                         weightSum.put (to, relaxedWeigth);
                         acm.put (to, from);
                         pq.add (new VertexWeightPair (to,weightSum.get (to)));
                         acmret.addEdge(from, to, relaxedWeigth);
                     } // if
                 } // while from's neighbors have not been processed
            } // else path not yet found
        } // while not done and priority queue not empty

        return acmret;
    }

    /**
     *  Returns a Map-String representation of this Network object.
     *  The worstTime(V, E) is O(V * V).
     *
     *  @return a Map-String representation of this Network object.
     *
     */
    public String toString()
    {
        return adjacencyMap.toString();
    } // method toString   

        

    protected class NetworkIterator implements Iterator<Vertex>
    {
        protected Iterator<Vertex> itr;
    
        protected Vertex current;

        /**
         * Initializes this NetworkIterator object to iterate over the
         * vertices in this Network object.
         *
         */
        public NetworkIterator()
        {
            itr = adjacencyMap.keySet().iterator();
        } // default constructor


        /**
         * Returns true if this NetworkIterator object has not yet finished
         * iterating over the vertices in this Network object.  Otherwise, 
         * returns false.
         *
         */
        public boolean hasNext()
        {
            return itr.hasNext();
        } // method hasNext


        /**
         * Returns the next vertex in this NetworkIterator object.
         *
         */    
        public Vertex next()
        {
            current = itr.next();
            return current;
        } // method next


        /**
         * Removes the most recently returned vertex from this
         * NetworkIterator object.
         *
         */
        public void remove()
        {
            removeVertex (current);
        } // method remove

    } // class NetworkIterator


    protected class BreadthFirstIterator implements Iterator<Vertex>
    {
        protected Queue<Vertex> queue;

        protected TreeMap<Vertex, Boolean> reached;

        protected Vertex current;

        /**
         * Initializes this BreadthFirstIterator at start.
         *
         */
        public BreadthFirstIterator (Vertex start)
        {
            queue = new LinkedList<Vertex>();

            reached = new TreeMap<Vertex, Boolean>();

            for (Vertex v: adjacencyMap.keySet())                            
                reached.put (v, false);

            queue.add (start);
            reached.put (start, true);
        } // one-parameter constructor


        /**
         * Returns true if this BreadthFirstIterator has not reached all of its 
         * reachable vertices.  Otherwise, returns false.
         *
         */
        public boolean hasNext()
        {
            return !(queue.isEmpty());
        } // method hasNext


        /**
         * Returns the next reachable vertex in this BreadthFirstIterator object.
         *
         */    
        public Vertex next()
        {            
            Vertex to;

            current = queue.remove();

            TreeMap<Vertex, Double> neighborMap = adjacencyMap.get (current);            

            for (Map.Entry<Vertex, Double> entry: neighborMap.entrySet())
            {
                to = entry.getKey();
                if (!reached.get (to))
                {
                   reached.put (to, true);
                   queue.add (to);
                } // if
            } // for
            return current;
        } // method next


        /**
         * Removes the most recently returned vertex.
         *
         */
        public void remove()
        {
            removeVertex (current);
        } // method remove

    } // class BreadthFirstIterator


    protected class DepthFirstIterator implements Iterator<Vertex>
    {
        Stack<Vertex> stack;

        TreeMap<Vertex, Boolean> reached;

        Vertex current;


        /**
         * Initializes this DepthFirstIterator at start.
         *
         */
        public DepthFirstIterator (Vertex start)
        {
            stack = new Stack<Vertex>();

             reached = new TreeMap<Vertex, Boolean>();

            for (Vertex v: adjacencyMap.keySet())                            
                reached.put (v, false);

            stack.add (start);
            reached.put (start, true);
        } // one-parameter constructor


        /**
         * Returns true if this DepththFirstIterator has not reached all of its 
         * reachable vertices.  Otherwise, returns false.
         *
         */
        public boolean hasNext()
        {
            return !(stack.isEmpty());
        } // method hasNext


        /**
         * Returns the next reachable vertex in this DepththFirstIterator object.
         *
         */    
        public Vertex next()
        {                      
            Vertex to;

            current = stack.pop();

            TreeMap<Vertex, Double> neighborMap = adjacencyMap.get (current);            

            for (Map.Entry<Vertex, Double> entry: neighborMap.entrySet())
            {
                to = entry.getKey();
                if (!reached.get (to))
                {
                   reached.put (to, true);
                   stack.add (to);
                } // if
            } // for
            return current;
        } // method next


        /**
         * Removes the most recently returned vertex.
         *
         */
        public void remove()
        {
            Network.this.removeVertex (current);
        } // method remove

    } // class DepthFirstIterator


    protected class VertexWeightPair implements Comparable<VertexWeightPair>, 
                                                java.io.Serializable
    {
        Vertex vertex; 

        double weight;


        /**
         * Initializes this VertexWeightPair from vertex and weight.
         *
         */
        public VertexWeightPair (Vertex vertex, double weight)
        {
            this.vertex = vertex;
            this.weight = weight;
        } // default constructor

        /**
         *  Returns an int <, = or > 0 , depending on whether this VertexWeightPair's 
         *  weight is <, = or > other's weight.
         *
         */
        public int compareTo (VertexWeightPair other)
        {
            return (int)(weight - other.weight);
        } // method compareTo

        /**
         *  Returns a String representation of this VertexWeightPair.
         *
         */
        public String toString()
        {
            return vertex.toString() + "  " + String.valueOf (weight);
        } // method toString

    } // class VertexWeightPair



    protected class EdgeTriple implements Comparable<EdgeTriple>
    {
        Vertex from,
               to;

        double weight;


        /**
         *  Initializes this EdgeTriple from v1, v2 and weight.
         *
         */
        public EdgeTriple (Vertex v1, Vertex v2, double weight)
        {
            from = v1;
            to = v2;
            this.weight = weight;
        } // default constructor


        /**
         *  Returns an int <, = or > 0, depending on whether this EdgeTriple's 
         *  weight is <, = or > edge's weight.
         *
         */
        public int compareTo (EdgeTriple edge)
        {
            return (int)(weight - edge.weight);
        } // method compareTo


        /**
         *  Returns a String representation of this EdgeTriple.
         *
         */
        public String toString()
        {
            return from.toString() + "  " + to.toString() + String.valueOf (weight);
        } // method toString

    } // class EdgeTriple

} // class Network
