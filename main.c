#include <stdio.h>
#include "lecture.h"

int main() {
    list_adjac list = readGraph("data/exemple1.txt");
    displayListAdjac(&list);
    verifMarkovGraph(&list);
    return 0;

}
