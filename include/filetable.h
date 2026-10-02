#ifndef FILETABLE_H
#define FILETABLE_H

#include <array>

class FileTable {
private:
    std::array<bool, 8> openDescriptors{};

public:
    bool open(int descriptor);
    bool close(int descriptor);
    bool isOpen(int descriptor) const;
    int countOpen() const;
};

#endif  // FILETABLE_H
