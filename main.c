#include <stdio.h>
#include "lecture.h"
#include "utils.h"

int main() {
    list_adjac list1 = readGraph("data/exemple1.txt");
    displayListAdjac(&list1);
    verifMarkovGraph(&list1);
    CreateMermaidGraph(&list1);

    list_adjac list2 = readGraph("data/exemple1_from_chatGPT.txt");
    displayListAdjac(&list2);
    verifMarkovGraph(&list2);

    list_adjac list3 = readGraph("data/exemple1_chatGPT_fixed.txt");
    displayListAdjac(&list3);
    verifMarkovGraph(&list3);
    return 0;

}
