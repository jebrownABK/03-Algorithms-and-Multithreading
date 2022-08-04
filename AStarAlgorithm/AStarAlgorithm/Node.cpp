#include "Node.h"

Node::Node(char data)
	:m_data(data)
{
}

Node::~Node()
{
	delete m_next;
	m_next = nullptr;
}
