#pragma once
#include <DatabaseConnector.h>
#include <math.h>
#include <limits>
#include <gtest/gtest.h>
#include <cstddef>
#include <iostream>

TEST(DatabaseConnector, DefaultConstructor)
{
    auto dbConnection = new DatabaseConnector();
    delete(dbConnection);
    ASSERT_EQ(1, 1);
}
