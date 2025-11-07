#include <stdio.h>
#include "lecture.h"

int main() {
    list_adjac list = readGraph("data/exemple1_from_chatGPT.txt");
    displayListAdjac(&list);
    verifMarkovGraph(&list);
    return 0;

}
