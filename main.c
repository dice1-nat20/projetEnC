
#include "lecture.h"
#include "utils.h"
#include "tarjan.h"

int main() {
    list_adjac * list1 = readGraph("data/exemple_valid_step3.txt");
    displayListAdjac(list1);
    displayPartition(tarjan(list1));
    return 0;

}
