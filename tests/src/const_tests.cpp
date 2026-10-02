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

// Purpose: Verify the constructor's externally visible initial state.
// Debugging hint: Every descriptor must begin closed, and the maintained count
// must begin at zero.
TEST(FileTableConstruction, StartsWithEveryDescriptorClosed) {
    const FileTable table{};

    EXPECT_EQ(table.countOpen(), 0);

    for (int descriptor{1}; descriptor <= 8; ++descriptor) {
        EXPECT_FALSE(table.isOpen(descriptor)) << "descriptor " << descriptor;
    }
}

// Purpose: Verify that isOpen reports the state of every valid descriptor.
// Debugging hint: The method must inspect the requested descriptor rather than
// merely reporting whether any descriptor is open.
TEST(FileTableObservers, IsOpenReportsEachValidDescriptorState) {
    FileTable table{};

    ASSERT_TRUE(table.open(2));
    ASSERT_TRUE(table.open(8));

    for (int descriptor{1}; descriptor <= 8; ++descriptor) {
        const bool expected = descriptor == 2 || descriptor == 8;
        EXPECT_EQ(table.isOpen(descriptor), expected)
            << "descriptor " << descriptor;
    }
}

// Purpose: Verify the specified result for invalid isOpen queries.
// Debugging hint: An invalid descriptor is never open, so isOpen must return false.
TEST(FileTableObservers, IsOpenReturnsFalseForInvalidDescriptors) {
    const FileTable table{};
    const std::array<int, 5> invalidDescriptors{-100, -1, 0, 9, 100};

    for (int descriptor : invalidDescriptors) {
        EXPECT_FALSE(table.isOpen(descriptor)) << "descriptor " << descriptor;
    }
}

// Purpose: Verify that the maintained count increases exactly once for each
// successful open and not for failed open attempts.
// Debugging hint: Increment the count only when open changes false to true.
TEST(FileTableCount, TracksSuccessfulOpenOperations) {
    FileTable table{};

    EXPECT_EQ(table.countOpen(), 0);
    EXPECT_TRUE(table.open(1));
    EXPECT_EQ(table.countOpen(), 1);
    EXPECT_TRUE(table.open(5));
    EXPECT_EQ(table.countOpen(), 2);
    EXPECT_FALSE(table.open(5));
    EXPECT_EQ(table.countOpen(), 2);
    EXPECT_FALSE(table.open(0));
    EXPECT_FALSE(table.open(9));
    EXPECT_EQ(table.countOpen(), 2);
}

// Purpose: Verify that the maintained count decreases exactly once for each
// successful close and not for failed close attempts.
// Debugging hint: Decrement the count only when close changes true to false.
TEST(FileTableCount, TracksSuccessfulCloseOperations) {
    FileTable table{};

    ASSERT_TRUE(table.open(1));
    ASSERT_TRUE(table.open(5));
    ASSERT_TRUE(table.open(8));
    ASSERT_EQ(table.countOpen(), 3);

    EXPECT_TRUE(table.close(5));
    EXPECT_EQ(table.countOpen(), 2);
    EXPECT_FALSE(table.isOpen(5));
    EXPECT_TRUE(table.isOpen(1));
    EXPECT_TRUE(table.isOpen(8));

    EXPECT_FALSE(table.close(5));
    EXPECT_FALSE(table.close(0));
    EXPECT_FALSE(table.close(9));
    EXPECT_EQ(table.countOpen(), 2);
}

// Purpose: Verify the rule that every operation receiving an invalid descriptor
// leaves all observable table state unchanged.
// Debugging hint: Check validity before reading or writing the array or count.
TEST(FileTableInvalidDescriptors, LeaveTheEntireTableUnchanged) {
    FileTable table{};
    const std::array<int, 5> invalidDescriptors{-100, -1, 0, 9, 100};

    ASSERT_TRUE(table.open(4));

    for (int descriptor : invalidDescriptors) {
        EXPECT_FALSE(table.open(descriptor)) << "descriptor " << descriptor;
        EXPECT_FALSE(table.close(descriptor)) << "descriptor " << descriptor;
        EXPECT_FALSE(table.isOpen(descriptor)) << "descriptor " << descriptor;
        EXPECT_TRUE(table.isOpen(4));
        EXPECT_EQ(table.countOpen(), 1);
    }
}

// Purpose: Verify that both observer methods retain the const qualifications
// required by the public interface.
// Debugging hint: A method called through a const reference must itself be const.
TEST(FileTableObservers, CanBeCalledThroughAConstReference) {
    FileTable table{};
    ASSERT_TRUE(table.open(3));
    const FileTable& view = table;

    EXPECT_TRUE(view.isOpen(3));
    EXPECT_EQ(view.countOpen(), 1);
}
