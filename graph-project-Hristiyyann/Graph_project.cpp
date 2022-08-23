#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 100;

int nodesCount = 0;
int distances[N], distanceCostFromTo[N][N];
bool visitedNodes[N];
int paths[N];
static vector<vector<int>> pathCombinations;
vector<vector<int>> allShortestPaths;
int smallestValueForPath = INT_MAX;

bool checkPoint(int point)
{
    if(point >= 0 && point < nodesCount)
    {
        return true;
    }
    return false;
}

int nearestNode()
{
    int minimumValue = INT_MAX;
    int minimumNodeIndex = 0;

    for(int i = 0; i < nodesCount; i++)
    {
        if(distances[i] < minimumValue && visitedNodes[i] != true)
        {
            minimumValue = distances[i];
            minimumNodeIndex = i;
        }
    }
    
    return minimumNodeIndex;
}

void dijkstra(int startPoint, vector<vector<int>>& graph)
{
    for(int i = 0; i < nodesCount; i++)
    {
        distances[i] = INT_MAX;
        paths[i] = -1;
    }

    distances[startPoint] = 0;

    for(int i = 0; i < nodesCount; i++)
    {
        int node = nearestNode();
        visitedNodes[node] = true;

        for(int currentNode = 0; currentNode < nodesCount; currentNode ++)
        {
            if(graph[node][currentNode] != -1 && 
            distances[currentNode] > distances[node] + graph[node][currentNode])
            {
                distances[currentNode] = distances[node] + graph[node][currentNode];
                paths[currentNode] = node;
            }
        }
    }
}

void makeGraph(vector<vector<int>>& graph)
{
    ifstream matrix ("matrix.txt");
    string line;

    while(getline(matrix,line))
    {
        nodesCount++;
    }

    matrix.close();
    matrix.open("matrix.txt");

    for(int i = 0; i < nodesCount; i++)
    {
        vector<int> currentNode;
        
        for(int j = 0; j < nodesCount; j++)
        {
            int value; 
            matrix >> value;
            currentNode.push_back(value);
        }

        graph.push_back(currentNode);
    }
}

void printPath(int nodeIndex)
{
    vector<int> nodesNeededForPath;
    cout << "To node " << nodeIndex << " the path is : ";

    if(distances[nodeIndex] < 0 || distances[nodeIndex] == INT_MAX)
    {
        cout << " No path " << endl;
        return;
    }

    nodesNeededForPath.push_back(nodeIndex);
    int node = paths[nodeIndex];

    while(node != -1)
    {
        nodesNeededForPath.push_back(node);
        node = paths[node];
    }

    reverse(nodesNeededForPath.begin(), nodesNeededForPath.end());
    int size = nodesNeededForPath.size();
    int currentNode = 0;

    for(auto nodeNumber : nodesNeededForPath)
    {
        cout << nodeNumber;
        currentNode++;
    
        if(currentNode != size)
        {
            cout << " -> ";
        }

    }
    cout << " (Weigh = " << distances[nodeIndex] << ")";
    cout << endl;
}

void makeCombinations(int fromIndex, vector<int> values)
{
    pathCombinations.push_back(values);

    for(int i = fromIndex; i < values.size(); i++)
    {
        for(int j = i + 1; j < values.size(); j++)
        {
            vector<int> current = values;
            int temp = current[i];
            current[i] = current[j];
            current[j] = temp;

            makeCombinations(i + 1, current);
        }
    } 
}

void pathThroughAllNodes(vector<vector<int>> paths,vector<vector<int>> matrix, int startPoint)
{
    int totalWeight = 0;
    bool flag;
    for(auto currentPath: paths)
    {
        totalWeight = 0;
        flag = false;

        for(int i = 0; i <= currentPath.size() - 1; i++)
        {
            int currentX = currentPath[i];
            int currentY = currentPath[i + 1];
            
            if(i == currentPath.size() - 1)
            {
                if(matrix[currentX][startPoint] == -1)
                {
                    flag = true;
                    break;
                }

                totalWeight += matrix[currentX][startPoint];
               
                break;
            }

            if(matrix[currentX][currentY] == -1)
            {
                flag = true;
                break;
            }

            totalWeight += matrix[currentX][currentY];
        }

        if(!flag)
        { 
            if(totalWeight <= smallestValueForPath)
            {
                if(totalWeight == smallestValueForPath)
                {
                    allShortestPaths.push_back(currentPath);
                    continue;    
                }

                smallestValueForPath = totalWeight;
                allShortestPaths.clear();
                allShortestPaths.push_back(currentPath);
            }
        }
        
    }
    return ;
}

bool isTherePathThroughAllNodes(vector<vector<int>> paths)
{
    //Идеята на тази функция е да провери дали има поне 1 път, който минава през всяка една точка. В горната функция има проверки за път от точка до точка дали не е -1
    //Ако е -1 то този път няма да се провери и няма да се брои за комбинация, минаваща през всички точки. Дори и само един път да премине проверките за стойност -1 от 
    //точка до точка, означава че има най-малко един път, минаващ през всяка точка, който път е достатъчен, за да се изпълни условието да има поне един път, минаващ през
    //точка.
    
    if(paths.size() != 0)
    {
        return true;
    }
    return false;
}

void printShortestPathsThroughAllNodes(vector<vector<int>> paths)
{
    //Тази функция принтира всички пътища с най-кратко време. Нужна е, защото може да има 2 или повече различни пътя, но с едно и също минимално време.
    // Например ако минималното време е 65 минути, това условие би могло да бъде изпълнено както от път 0 2 3 1, така и от 0 3 2 1, 0 2 1 3 и така нататък.
    for(auto path : paths)
    {
        for(auto node : path)
        {
            cout << node << " ";
        }
        cout << "(Weigh " << smallestValueForPath << ")" << endl; 
    }
}

int main()
{
    int startPoint, endPoint;
    vector<vector<int>> graph;
    makeGraph(graph);

    cout << "Start point is: " << endl;
    cin >> startPoint;
    cout << "End point is: " << endl;
    cin >> endPoint; 
    cout << endl;

    if(!checkPoint(startPoint) || !checkPoint(endPoint))
    {
        //Тук се проверяват началната и крайна точка дали са валидни, защото може някой да иска начална точка 7-ми връх, а графа да има само 4 върха.
        cout << "Not valid start point or end point" << endl;
        return 1;
    }

    vector<int> nodes;
    nodes.push_back(startPoint);

    for(int i = 0; i < nodesCount; i++)
    {
        if(!(i == startPoint))
        {
            nodes.push_back(i);
        }
    }

    dijkstra(startPoint, graph);
  
    cout << "From node " << startPoint << " ";
    printPath(endPoint);
    cout << endl;
    cout << "The other paths are : " << endl;

    for(int i = 0; i < nodesCount; i++)
    {
        if(i == endPoint)
        {
            continue;
        }

        printPath(i);
    }

    makeCombinations(1, nodes);
    pathThroughAllNodes(pathCombinations, graph, startPoint);
    
    cout << endl;
    
    if(!isTherePathThroughAllNodes(allShortestPaths) || smallestValueForPath == 0)
    {
        cout << "There is no path through all nodes!" << endl;
        return 0;
    }

    cout << "These are the shorthest paths through all nodes" << endl;
    printShortestPathsThroughAllNodes(allShortestPaths);
}