#include "filetable.h"

#include <iostream>

void printFileTable(const FileTable& table) {
    std::cout << "Open descriptors: " << table.countOpen() << '\n';

    for (int descriptor = 1; descriptor <= 8; ++descriptor) {
        std::cout << "[" << descriptor << "] "
                  << (table.isOpen(descriptor) ? "open" : "closed") << '\n';
    }
}

int main() {
    FileTable table;

    std::cout << "Initial file table\n";
    printFileTable(table);

    table.open(2);
    table.open(5);

    std::cout << "\nAfter opening descriptors 2 and 5\n";
    printFileTable(table);

    table.close(2);

    std::cout << "\nAfter closing descriptor 2\n";
    printFileTable(table);
}
