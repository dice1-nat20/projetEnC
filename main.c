
#include "lecture.h"
#include "utils.h"
#include "hasse.h"

int main() {
    list_adjac * list1 = readGraph("data/exemple1_chatGPT_fixed.txt");
    displayListAdjac(list1);
    verifMarkovGraph(list1);
    t_partition* graphTarjan = tarjan(list1);
    displayPartition(graphTarjan);
    hasse(graphTarjan,list1);

    return 0;

}
