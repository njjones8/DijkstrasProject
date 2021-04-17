#include "vertex.h"


Vertex::Vertex()
{
	color = 0;
	pi = 0;
	distance = 0;
	position = 0;
	name = "";
}

Vertex::Vertex(int c, int p, float d, int pos, std::string n)
{
	color = c;
	pi = p;
	distance = d;
	position = pos;
	name = n;
}

void Vertex::setColor(int x)
{
	color = x;
}

void Vertex::setPi(int x)
{
	pi = x;
}

void Vertex::setPosition(int x)
{
	position = x;
}

void Vertex::setDistance(float x)
{
	distance = x;
}

void Vertex::setName(std::string x)
{
	name = x;
}

int Vertex::getColor()
{
	return color;
}

int Vertex::getPi()
{
	return pi;
}

int Vertex::getPosition()
{
	return position;
}

float Vertex::getDistance()
{
	return distance;
}

std::string Vertex::getName()
{
	return std::string();
}
