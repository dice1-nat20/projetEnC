
#include "lecture.h"
#include "utils.h"
#include "hasse.h"
#include "utils.h"

int main() {
    list_adjac * list1 = readGraph("data/exemple_custom.txt");
    displayListAdjac(list1);
    CreateMermaidGraph(list1);
    verifMarkovGraph(list1);
    t_partition* graphTarjan = tarjan(list1);
    displayPartition(graphTarjan);
    t_hasse * graphHasse = hasse(graphTarjan,list1);
    CreateMermaidPartition(graphTarjan, graphHasse);

    return 0;

}
