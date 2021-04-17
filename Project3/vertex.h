#ifndef _vertex_h
#define _vertex_h 1

#include <string>

class Vertex
{
private:
	int color, pi, position;
	float distance;
	std::string name;
public:
	Vertex();
	Vertex(int, int, float, int, std::string);

	void setColor(int);
	void setPi(int);
	void setPosition(int);
	void setDistance(float);
	void setName(std::string);

	int getColor();
	int getPi();
	int getPosition();
	float getDistance();
	std::string getName();
};

#endif