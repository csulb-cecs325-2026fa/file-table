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

// Purpose: Verify that every valid open descriptor can be closed.
// Debugging hint: close uses the same 1-through-8 descriptor-to-index mapping
// as open.
TEST(FileTableClose, ClosesEveryOpenDescriptor) {
    FileTable table{};

    for (int descriptor{1}; descriptor <= 8; ++descriptor) {
        ASSERT_TRUE(table.open(descriptor)) << "descriptor " << descriptor;
    }

    for (int descriptor{1}; descriptor <= 8; ++descriptor) {
        EXPECT_TRUE(table.close(descriptor)) << "descriptor " << descriptor;
    }
}

// Purpose: Verify that close reports whether it actually changed the table.
// Debugging hint: Closing a descriptor that is already closed must return false.
TEST(FileTableClose, RejectsAlreadyClosedDescriptor) {
    FileTable table{};

    EXPECT_FALSE(table.close(4));
    ASSERT_TRUE(table.open(4));
    EXPECT_TRUE(table.close(4));
    EXPECT_FALSE(table.close(4));
}

// Purpose: Verify that invalid descriptor numbers are rejected and do not
// change the state of a valid open descriptor.
// Debugging hint: Validate the descriptor before converting it to an array index.
TEST(FileTableClose, RejectsInvalidDescriptorsWithoutChangingTable) {
    FileTable table{};
    const std::array<int, 5> invalidDescriptors{-100, -1, 0, 9, 100};

    ASSERT_TRUE(table.open(4));

    for (int descriptor : invalidDescriptors) {
        EXPECT_FALSE(table.close(descriptor)) << "descriptor " << descriptor;
    }

    EXPECT_TRUE(table.close(4));
}

// Purpose: Verify that closing one descriptor does not close another.
// Debugging hint: Only the array entry corresponding to the requested
// descriptor should change.
TEST(FileTableClose, ChangesOnlyTheRequestedDescriptor) {
    FileTable table{};

    ASSERT_TRUE(table.open(2));
    ASSERT_TRUE(table.open(7));
    EXPECT_TRUE(table.close(2));
    EXPECT_FALSE(table.close(2));
    EXPECT_TRUE(table.close(7));
}
