#include <iostream>

#include <cstdio>
#include <fstream>

#include "lemon/smart_graph.h"
#include "lemon/network_simplex.h"
#include "lemon/dimacs.h"
#include "lemon/graph_to_eps.h"
#include "lemon/list_graph.h"
#include "lemon/dim2.h"
#include "lemon/math.h"

using namespace std;
using namespace lemon;

int main()
{
    typedef dim2::Point<int> Point;

    Palette palette(true, 50);

    //creates a directed graph
    DIGRAPH_TYPEDEFS(SmartDigraph);
    SmartDigraph g;

    // Create data structures (i.e. maps) associating values to nodes and arcs of the graph
    IntArcMap lower(g), capacity(g), cost(g),length(g);
    IntNodeMap supply(g);
    Node s;

    SmartDigraph::NodeMap<int> colors(g), shapes(g);
    SmartDigraph::NodeMap<double> sizes(g);
    SmartDigraph::NodeMap<Point> coords(g);
    SmartDigraph::ArcMap<int> acolors (g), widths(g);
    SmartDigraph::NodeMap<string> label(g);

    // Read DIMACS input file
    ifstream input("USA-road-d.NY.gr");
    readDimacsSp(input, g, length, s);
    input.close();

    cout << "Cant Nodos: "<<g.maxNodeId();

    colors[g.nodeFromId(0)]=4;
    sizes[g.nodeFromId(0)]= 100;
    shapes[g.nodeFromId(0)] = 2;
    label[g.nodeFromId(0)] = 'A';
    coords[g.nodeFromId(0)] = Point(0,300);
    coords[g.nodeFromId(1)] = Point(200,300);
    coords[g.nodeFromId(2)] = Point(-100,300);
    coords[g.nodeFromId(3)] = Point(400,300);

    graphToEps(g, "salida.eps").title("Salida Grafo").arcWidths(widths).nodeColors(composeMap(palette,colors)).arcColors(composeMap(palette,acolors)).nodeScale(1).absoluteNodeSizes().absoluteArcWidths().coords(coords).nodeSizes(sizes).nodeShapes(shapes).nodeTexts(label).nodeTextSize(1).run();

    return 0;
}
