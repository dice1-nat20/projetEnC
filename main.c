#include <windows.h>
#include "lecture.h"
#include "utils.h"
#include "hasse.h"
#include "utils.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    list_adjac * list1 = readGraph("data/exemple_custom1.txt");
    displayListAdjac(list1);
    CreateMermaidGraph(list1);
    verifMarkovGraph(list1);
    t_partition* graphTarjan = tarjan(list1);
    displayPartition(graphTarjan);
    t_hasse * graphHasse = hasse(graphTarjan,list1);
    displayHasseCarac(graphHasse, graphTarjan);
    CreateMermaidPartition(graphTarjan, graphHasse);

    return 0;

}
