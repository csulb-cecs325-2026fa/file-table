#include "filetable.h"

// TODO: Open the descriptor if it is valid and currently closed.
bool FileTable::open(int descriptor) {
    return false;
}

// TODO: Close the descriptor if it is valid and currently open.
bool FileTable::close(int descriptor) {
    return false;
}

// TODO: Return whether the descriptor is valid and currently open.
bool FileTable::isOpen(int descriptor) const {
    return false;
}

// TODO: Return the maintained number of open descriptors.
int FileTable::countOpen() const {
    return 0;
}
