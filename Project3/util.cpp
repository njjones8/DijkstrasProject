#include "util.h"

using namespace std;

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
int nextCommand(int* c, int* s, int* d, int* f)
{
    string cmd = "";
    bool foundCommand = false; // loop runs until it gets valid command
    int valid = 0;

    while (foundCommand == false)
    {
        cin >> cmd;
        if (cmd == "find" || cmd == "Find")
        {
            *c = 1;
            cin >> *s;
            cin >> *d;
            cin >> *f;
            printQuery(cmd, *c, *s, *d, *f);
            foundCommand = true;
        }
        else if (cmd == "write" || cmd == "Write")
        {
            *c = 2;
            cin >> *s;
            cin >> *d;
            printQuery(cmd, *c, *s, *d, *f);
            foundCommand = true;
        }
        else if (cmd == "stop" || cmd == "Stop")
        {
            *c = 0;
            printQuery(cmd, *c, *s, *d, *f);
            return 0;
        }
        else
        {
            cout << "Error invalid command" << endl;
        }
        clearInput();
    }
    return 1;
}

void printQuery(string cmd, int c, int s, int d, int f)
{
    if (c == 1)
        cout << "Query: " << cmd << " " << s << " " << d << " " << f << endl;
    else if (c == 2)
        cout << "Query: " << cmd << " " << s << " " << d << endl;
    else if (c == 0)
        cout << "Query: " << cmd << endl;
}

// clears input so if garbage is given to the program it does not get stuck
void clearInput()
{
    cin.clear();
    cin.ignore(1000, '\n');
}

int checkInput()
{
    if (!cin)
        return 0;
    else
        return 1;
}