#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Snap.h"
#include <time.h>
#include <cstdlib>


using namespace std;
typedef PNGraph DGraph;


//Metodos de exportacion

void GraphML(DGraph g) {
	std::ofstream file ("wiki.graphml");
	if (file.is_open()) {
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		file << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
		file << "<graph id=\"G\" edgedefault=\"directed\">\n";

		for (DGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
			file << "<node id=\"" << NI.GetId() << "\"/>\n";

		int i = 1;
		for (DGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
			file << "<edge id=\"e" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\"/>\n";

		file << "</graph>\n";
		file << "</graphml>\n";
		file.close();
	}
}

void GEXF(DGraph g) {
	std::ofstream file ("wiki.gexf");
	if (file.is_open()) {
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		file << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
		file << "<graph mode=\"static\" defaultedgetype=\"directed\">\n";
		
		file << "<nodes>\n";
		for (DGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
			file << "<node id=\"" << NI.GetId() << "\" />\n";
		file << "</nodes>\n";

		file << "<edges>\n";
		int i = 1;
		for (DGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
			file << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
		file << "</edges>\n";

		file << "</graph>\n";
		file << "</gexf>\n";
		file.close();
	}
}

void GDF(DGraph g) {
	std::ofstream file ("wiki.gdf");
	if (file.is_open()) {
		file << "nodedef>id VARCHAR\n";
		for (DGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
			file << NI.GetId() << "\n";

		file << "edgedef>source VARCHAR, destination VARCHAR\n"; 
		for (DGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++)
			file << EI.GetSrcNId() << ", " << EI.GetDstNId() << "\n";

		file.close();
	}
}

void JSON(DGraph g) {
	std::ofstream file ("wiki.json");
	if (file.is_open()) {
		file << "{ \"graph\": {\n";
		file << "\"nodes\": [\n";
		for (DGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); ) {
			file << "{ \"id\": \"" << NI.GetId() << "\" }";
			if (NI++ == g->EndNI())
				file << " ],\n";
			else
				file << ",\n";
		}

		file << "\"edges\": [\n";
		for (DGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); ) {
			file << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
			if (EI++ == g->EndEI())
				file << " ]\n";
			else
				file << ",\n";
		}
		file << "} }";

		file.close();
	}
}



int main(int argc, char* argv[]) {
//Descargando la libreria wiki
DGraph dg = TSnap::LoadEdgeList<DGraph>("wiki.txt",0,1);

clock_t t;

t = clock();
GraphML(dg);
t = clock()-t;
cout<<"GraphML: "<<(float(t)/CLOCKS_PER_SEC)*1000<<" mili segundos"<<endl;

t = clock();
GEXF(dg);
t = clock()-t;
cout<<"GEXF: "<<(float(t)/CLOCKS_PER_SEC)*1000<<" mili segundos"<<endl;

t = clock();
GDF(dg);
t = clock()-t;
cout<<"GDF: "<<(float(t)/CLOCKS_PER_SEC)*1000<<" mili segundos"<<endl;

t = clock();
JSON(dg);
t = clock()-t;
cout<<"JSON: "<<(float(t)/CLOCKS_PER_SEC)*1000<<" mili segundos"<<endl;
  return 0;
}

//El código fue obtenido de la siguiente liga https://github.com/alberto911/exportGraphs/blob/master/grafo.cpp

