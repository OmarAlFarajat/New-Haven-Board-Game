// Requires boost_1_72_0 https://sourceforge.net/projects/boost/files/boost/1.72.0/
// Run bootstrap.bat, then b2.exe
// Set up property sheet, include and library directories https://www.youtube.com/watch?v=CH_YZ2bePPM
// Code adapted from https://valelab4.ucsf.edu/svn/3rdpartypublic/boost/libs/graph/doc/grid_graph.html

#include "GBMap.h"
#include <iostream>
#include <boost/graph/grid_graph.hpp>

#define DIMENSIONS 2
using namespace boost;

typedef grid_graph<DIMENSIONS> Graph;
typedef graph_traits<Graph> Traits;

int main(int argc, char* argv[]) {

    // Define a 5x5 grid with no wrapping
    boost::array<std::size_t, 2> lengths = { { 5,5 } };
    boost::array<bool, 2> wrapped = { { false, false} };
    Graph graph(lengths, wrapped);

    // Do a round-trip test of the vertex index functions
    for (Traits::vertices_size_type v_index = 0;
        v_index < num_vertices(graph); ++v_index) {

        // The two indices should always be equal
        std::cout << "Index of vertex " << v_index << " is " <<
            get(boost::vertex_index, graph, vertex(v_index, graph)) << std::endl;
    }

    // Do a round-trip test of the edge index functions
    for (Traits::edges_size_type e_index = 0;
        e_index < num_edges(graph); ++e_index) {

        // The two indices should always be equal
        std::cout << "Index of edge " << e_index << " is " <<
            get(boost::edge_index, graph, edge_at(e_index, graph)) << std::endl;
    }
}