import java.util.*;

public class UndirectedWeightedTree<Vertex> extends UndirectedNetwork<Vertex>
{
  
    protected Vertex root;
    
    protected boolean okToAddVertex;

    /**
     *  Initializes this UndirectedNetwork object to be empty, with the ordering of
     *  vertices by an implementation of the Comparable interface.
     */
    public UndirectedWeightedTree()
    {        
        super();   
        root = null;
        okToAddVertex = false;
    } // default constructor

       
    /**
     *  Initializes this UndirectedWeightedTree object to a shallow copy of a specified 
     *  UndirectedWeightedTree object.    
     *
     *  @param network - the UndirectedWeightedTree object that this UndirectedWeightedTree object is
     *                   initialized to a shallow copy of.
     * 
     *  @throws NullPointerException if network is null.
     *
     */
    public UndirectedWeightedTree (UndirectedWeightedTree<Vertex> network)
    {
        super (network);         
    } // copy constructor

    /**
     *  Determines if this UndirectedWeightedTree object is equal to a given object. 
     * 
     *  @param obj - the object this UndirectedWeightedTree object is compared to.
     *
     *  @return true - if this UndirectedWeightedTree object is equal to obj.
     *
     */
    public boolean equals (Object obj)
    {
        if (!(obj instanceof UndirectedWeightedTree))
            return false;
        UndirectedWeightedTree<Vertex> other = (UndirectedWeightedTree<Vertex>)obj;
        
        return adjacencyMap.equals (other.adjacencyMap);
    } // method equals
                   
    public boolean addVertex (Vertex v)
    {
        if (root == null) 
        {
            root = v;        
            return super.addVertex (root);
        } // adding root
        if (okToAddVertex)        
            return super.addVertex (v);
        return false;      
    } // method addVertex
    
    /**
     *  Ensures that a given edge with a given weight is in this UndirectedWeightedTree 
     *  object.  
     *
     *  @param v1  the first vertex of the edge.
     *  @param v2 -  the second vertex of the edge (the neighbor of v1).
     *  @param weight  the weight of the edge (v1, v2).
     *
     *  @return true if this UndirectedWeightedTree object changed as a result of this call.
     *
     */ 
    public boolean addEdge (Vertex v1, Vertex v2, double weight) 
    {
        if ((containsVertex (v1) && containsVertex (v2)) || (root != null && !containsVertex (v1) && !containsVertex (v2)))
            return false;
        if (root == null)
            root = v1;
        okToAddVertex = true;     
        boolean result = super.addEdge (v1, v2, weight) && super.addEdge (v2, v1, weight);
        okToAddVertex = false;
        return result;
    } // method addEdge 
    
    public boolean removeVertex (Vertex v)
    {
        if (!containsVertex (v))
            return false;
        int size = adjacencyMap.get (v).size();
        if (size > 1)
            return false;
        if (v.equals (root))
            root = null;
        if (adjacencyMap.get (v).containsKey (root))
            root = v;
        return super.removeVertex (v);
    } // method removeVertex
              
    /**
     *  Returns false -- edge removal is not allowed in an undirected tree.
     *
     */
    public boolean removeEdge (Vertex v1, Vertex v2)
    {
        return false;
    } // method removeEdge        
                         
} // class UndirectedWeightedTree
