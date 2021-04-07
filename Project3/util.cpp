#include "util.h"

Graph* initializeGraph()
{
    std::ifstream readFile;

    std::string fileName = "";
    std::cin >> fileName;
    std::string direction = "";
    std::cin >> direction;

    int vertices = 0, edges = 0;
    readFile.open(fileName);
    readFile >> vertices;
    readFile >> edges;

    Graph* graph = new Graph(vertices, direction);

    for (int i = 0; i < edges; i++)
    {
        int edgeNum = 0, x = 0, y = 0, weight = 0;
        readFile >> edgeNum;
        readFile >> x;
        readFile >> y;
        readFile >> weight;

        graph->insertNode(x, y, weight);
    }

    readFile.close();

    return graph;
}

// only command in util.cpp, used to get user input
int nextCommand(int* n, int* f)
{
    char c;
    while (1)
    {

        std::cin >> c;

        // checks if the input in ascii is from a-z or A-Z
        // if its not then it is an invalid input for this program
        if (!((c >= 97 && c <= 122) || (c >= 65 && c <= 90)))
            std::cout << "Warning in nextCommand: invalid input" << std::endl;

        if (c == 'S' || c == 's')
            break;

        if (c == 'C' || c == 'c')
        {
            std::cin >> *n;
            // if the input is a 0
            if (*n == 0)
                std::cout << "Warning in nextCommand: read in int " << *n << std::endl;
            break;
        }

        if (c == 'r' || c == 'R')
        {
            std::cin >> *f;
            break;
        }

        if (c == 'p' || c == 'P')
            break;

        if (c == 'w' || c == 'W')
            break;

        if (c == 'I' || c == 'i')
        {
            std::cin >> *n;
            if (*n == 0)
                std::cout << "Warning in nextCommand: read in int " << *n << std::endl;
            break;
        }
            
        if (c == 'D' || c == 'd')
        {
            std::cin >> *f;
            break;
        }

        if (c == 'K' || c == 'k')
        {
            std::cin >> *n;
            std::cin >> *f;
            break;
        }

        // clears input so if garbage is given to the program it does not get stuck
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    return c;
}
