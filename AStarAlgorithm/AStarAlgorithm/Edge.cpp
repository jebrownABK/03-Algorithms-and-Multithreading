#include "Edge.h"

Edge::Edge(Node* nodeA, Node* nodeB, int cost)
	:m_nodeA(nodeA)
	,m_nodeB(nodeB)
	,m_cost(cost)
{
}

Edge::~Edge()
{
	delete m_nodeA;
	delete m_nodeB;

	m_nodeA = nullptr;
	m_nodeB = nullptr;
}
