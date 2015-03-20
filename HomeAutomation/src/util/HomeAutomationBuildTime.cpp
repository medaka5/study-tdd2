#include "HomeAutomationBuildTime.h"

HomeAutomationBuildTime::HomeAutomationBuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

HomeAutomationBuildTime::~HomeAutomationBuildTime()
{
}

const char* HomeAutomationBuildTime::GetDateTime()
{
    return dateTime;
}

