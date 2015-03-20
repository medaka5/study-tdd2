#include "CppUTest/TestHarness.h"
#include "HomeAutomationBuildTime.h"

TEST_GROUP(HomeAutomationBuildTime)
{
  HomeAutomationBuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new HomeAutomationBuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(HomeAutomationBuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

