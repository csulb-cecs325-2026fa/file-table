/**
 * WARNING TO STUDENTS:
 * DO NOT MODIFY THIS FILE IN ANY WAY. DO NOT LET YOUR EDITOR CHANGE THE INDENTATION,
 * OR ADD BLANK LINES, OR MAKE ANY OTHER MODIFICATION. THE CLASSROOM 50 AUTOGRADER
 * WILL FAIL YOUR SUBMISSION IF YOU MAKE EVEN A SINGLE INSIGNIFICANT CHANGE.
 *
 * THE SAME IS TRUE FOR THE FILE "vcpkg.json" IN THE ROOT OF THIS PROJECT,
 * AND EVERY OTHER FILE IN THE "tests" FOLDER.
 */

#include <gtest/gtest.h>

#include <array>

#include "filetable.h"

// Purpose: Verify that every descriptor named as valid by the specification
// can be opened from the initial closed state.
// Debugging hint: Descriptors are numbered 1 through 8, while array indexes are
// numbered 0 through 7.
TEST(FileTableOpen, OpensEveryValidDescriptor) {
    FileTable table{};

    for (int descriptor{1}; descriptor <= 8; ++descriptor) {
        EXPECT_TRUE(table.open(descriptor)) << "descriptor " << descriptor;
    }
}

// Purpose: Verify that open reports whether it actually changed the table.
// Debugging hint: Opening an already-open descriptor must return false.
TEST(FileTableOpen, RejectsAlreadyOpenDescriptor) {
    FileTable table{};

    EXPECT_TRUE(table.open(4));
    EXPECT_FALSE(table.open(4));
}

// Purpose: Verify that invalid descriptor numbers are rejected without making
// any valid descriptor unavailable afterward.
// Debugging hint: Validate the descriptor before converting it to an array index.
TEST(FileTableOpen, RejectsInvalidDescriptorsWithoutChangingTable) {
    FileTable table{};
    const std::array<int, 5> invalidDescriptors{-100, -1, 0, 9, 100};

    for (int descriptor : invalidDescriptors) {
        EXPECT_FALSE(table.open(descriptor)) << "descriptor " << descriptor;
    }

    for (int descriptor{1}; descriptor <= 8; ++descriptor) {
        EXPECT_TRUE(table.open(descriptor)) << "descriptor " << descriptor;
    }
}
