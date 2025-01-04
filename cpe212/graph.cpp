//
// graph.cpp  2023 Spring CPE 212 - Project06 - Graphs and STL
//

#include "graph.h"


Graph::Graph()
{							
// Constructor initializes vertices linked list to empty
	vertices  = NULL;
}


Graph::~Graph()
{
// For each VertexNode in the vertices list, Destructor deallocates all EdgeNodes before
// deallocating the VertexNode itself
	
	VertexNode* vertex = vertices;
	while (vertex != NULL)
	{
		EdgeNode* edge = vertex->edgePtr;
		while (edge != NULL)
		{
			EdgeNode* nextEdge = edge->nextPtr;
			delete edge;  // deallocate EdgeNode
			edge = nextEdge;
		}
		VertexNode* nextVertex = vertex->nextVertex;
		delete vertex;  // deallocate VertexNode
		vertex = nextVertex;
	}
}


void Graph::AddVertex(string v)
{	
// Adds vertex to graph assuming vertex not already present
	
	// initialize new vertex
	VertexNode* vertex = new VertexNode;
	vertex->vname = v;
	vertex->mark = false;
	vertex->edgePtr = NULL;
	vertex->nextVertex = NULL;
	
	// put new vertex in front of linked list vertices
	vertex->nextVertex = vertices;
	vertices = vertex;
}


void Graph::AddEdge(string s, string d, int w)
{	
// Adds edge from source S  to destination D with specified weight W.
// If there is not enough memory to add the edge, throw the GraphFull exception
	
	// initialize source, destination, and currentVertex
	VertexNode* source = NULL;
	VertexNode* destination = NULL;
	VertexNode* currentVertex = vertices;
	// traverse vertices to set source and destination
	while (currentVertex != NULL)
	{
		if (currentVertex->vname == s)
		{
			source = currentVertex;
		}
		if (currentVertex->vname == d)
		{
			destination = currentVertex;
		}
		
		currentVertex = currentVertex->nextVertex;
	}
	
	try
	{
		// create new edge
		EdgeNode* newEdge = new EdgeNode;
		newEdge->destination = destination;
		newEdge->weight = w;
		newEdge->nextPtr = NULL;

		// add edge to front of source vertex's edge list
		newEdge->nextPtr = source->edgePtr;
		source->edgePtr = newEdge;
	}
	catch (bad_alloc())  // if insufficient memory
	{
		throw GraphFull();
	}
}


bool Graph::IsPresent(string v)
{	
// Returns true if vertex V in graph, false otherwise
	
	// search vertices for vertex match
	VertexNode* currentVertex = vertices;
	while (currentVertex != NULL)
	{
		if (currentVertex->vname == v)
		{
			return true;
		}
		currentVertex = currentVertex->nextVertex;
	}
	// otherwise no match, vertex not found
	return false;
}


VertexNode* Graph::WhereIs(string v)		/* Note: This function replaces IndexIs */
{
// Returns pointer to the vertex node that stores vertex v in the vertices linked list; 
// Throws GraphVertexNotFound if V is not present in the vertices list

	// traverse the vertices linked list
	VertexNode* currentVertex = vertices;
	while (currentVertex != NULL)
	{
		if (currentVertex->vname == v)
		{
			return currentVertex; // return pointer to the current vertex node
		}
		currentVertex = currentVertex->nextVertex;
	}

	// otherwise vertex not found
	throw GraphVertexNotFound();
}


int Graph::WeightIs(string s, string d)
{  
// Returns weight of edge (s,d).
// Throws GraphEdgeNotFound or GraphVertexNotFound if applicable.
	
	// look through vertices for source vertex s
	VertexNode* sourceVertex = vertices;
	while (sourceVertex != NULL)
	{
		if (sourceVertex->vname == s)
		{
			break;  // move on if vertex found
		}
		sourceVertex = sourceVertex->nextVertex;
	}
	
	// if source not found, throw exception
	if (sourceVertex == NULL)
	{
		throw GraphVertexNotFound();
	}

	// look through vertices for destination vertex d
	VertexNode* destVertex = vertices;
	while (destVertex != NULL)
	{
		if (destVertex->vname == d)
		{
			break;  // move on if vertex found
		}
		destVertex = destVertex->nextVertex;
	}
	
	// if destination not found, throw exception
	if (destVertex == NULL)
	{
		throw GraphVertexNotFound();
	}
	
	// look through edges from source vertex to destination vertex
	EdgeNode* currentEdge = sourceVertex->edgePtr;
	while (currentEdge != NULL)
	{
		if (currentEdge->destination->vname == d)
		{
			break;  // move on if edge found
		}
		currentEdge = currentEdge->nextPtr;
	}
	
	// if edge not found, throw exception
	if (currentEdge == NULL)
	{
		throw GraphEdgeNotFound();
	}
	
	// finally return weight if edge found
	return currentEdge->weight;
}


void Graph::ClearMarks()
{		
// ClearMarks()
// Clears all vertex marks
	
	// set all vertices mark equal to false
	VertexNode* vertex = vertices;
	while (vertex != NULL)
	{
		vertex->mark = false;
		vertex = vertex->nextVertex;
	}
}


void Graph::MarkVertex(string v)
{
// MarkVertex()
// Marks vertex V as visited
	
	// look for vertex by name in vertices and mark as visited
	VertexNode* vertex = vertices;
	while (vertex != NULL)
	{
		if (vertex->vname == v)
		{
			vertex->mark = true;
			return;
		}
		vertex = vertex->nextVertex;
	}
}


bool Graph::IsMarked(string v)
{		
// IsMarked()
// Returns true if vertex V is marked, false otherwise
	
	// looks for vertex and returns if marked
	VertexNode* vertex = vertices;
	while (vertex != NULL)
	{
		if (vertex->vname == v)
		{
			return vertex->mark;
		}
		vertex = vertex->nextVertex;
	}
	// otherwise not found
	return false;
}


void Graph::GetToVertices(string V, queue<string>& q)
{	
// GetToVertices()
// Returns queue Q of vertex names of those vertices adjacent to vertex V
// The queue here is from the Standard Template Library
	
	// search through vertices to find specified vertex and push adjacent edges onto queue
	VertexNode* vertex = vertices;
	while (vertex != NULL)
	{
		if (vertex->vname == V)
		{
			EdgeNode* edge = vertex->edgePtr;
			// traverse adjacent edges
			while (edge != NULL)
			{
				q.push(edge->destination->vname);
				edge = edge->nextPtr;
			}
			return;
		}
		vertex = vertex->nextVertex;
	}
}


void Graph::DepthFirstSearch(string startVertex, string endVertex, queue<string>& path)
{
// DepthFirstSearch()
// Uses the DFS algorithm from the CPE 212 textbook to determine a path from the
// startVertex to the endVertex.  If a path is found, the path vertices should
// be in the path queue.  If no path is found, the path queue should be emptied
// as a signal to the client code that no path exists between the start and
// end vertices.
//
// Notes:
// (1) This algorithm is flawed in that as it searches for a path, it may
// output some additional vertices that it visited but were not part
// of the actual path.  Implement the algorithm just as it appears in the textbook.
// 
// (2) This algorithm requires use of the stack and queue containers from the
// Standard Template Library.  The STL stack and queue interfaces may require
// minor modifications to the DFS code from the textbook.

	// first check if both start and end vertices exist
	if(IsPresent(startVertex) == false || IsPresent(endVertex) == false)
	{
		throw GraphVertexNotFound();
	}
	
	// declare queue to hold adjacent vertices and stack to hold possible paths
	queue <string> adjacentVertices;
	stack <string> stack;
	string currentVertex;
	string adjacentVertex;

	ClearMarks();
	stack.push(startVertex);  // push start position

	// while stack not empty and path not found, iterate through stack for path
	while (!stack.empty())
	{
		currentVertex = stack.top();  // set current vertex
		stack.pop();  // pop off element
		// if current vertex is the end vertex, path has been found
		if(currentVertex == endVertex)
		{
			path.push(currentVertex);  // push final vertex to path
			return;  // terminate function
		}
		else
		{
			// if the vertex has not yet been visited
			if(!IsMarked(currentVertex))
			{
				MarkVertex(currentVertex);  // mark vertex as visited
				path.push(currentVertex);  // push to path
				
				// get queue of adjacent vertices, possible next moves
				GetToVertices(currentVertex, adjacentVertices);

				// sort through adjacent vertices
				while(!adjacentVertices.empty())
				{
					adjacentVertex = adjacentVertices.front();
					adjacentVertices.pop();
					// push unvisited adjacent vertices to stack
					if(!IsMarked(adjacentVertex))
					{
						stack.push(adjacentVertex);
					}
				}
			}
		}

	}
	// if no path found, empty path
	while(!path.empty())
	{
		path.pop();
	}
}
