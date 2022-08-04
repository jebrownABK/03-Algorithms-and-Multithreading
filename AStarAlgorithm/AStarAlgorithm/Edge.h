#pragma once
#include "Node.h"
class Edge
{
	Node* m_nodeA;
	Node* m_nodeB;
	int m_cost;

public:
	Edge(Node* nodeA, Node* nodeB, int cost);
	~Edge();

	int GetCost() { return m_cost; };

};