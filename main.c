#include <stdio.h>
#include "lecture.h"
#include "utils.h"
#include "tarjan.h"

int main() {
    list_adjac list1 = readGraph("data/exemple1.txt");
    displayListAdjac(&list1);
    verifMarkovGraph(&list1);
    tarjan(&list1);
    return 0;

}
