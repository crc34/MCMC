#include "ChainTest.h"
#include "ChainRunnerTests.h"
#include "DatabaseConnectorTests.h"
#include "MCMCDatabaseConnectorTests.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}  
