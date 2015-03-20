#ifndef D_HomeAutomationBuildTime_H
#define D_HomeAutomationBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  HomeAutomationBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class HomeAutomationBuildTime
  {
  public:
    explicit HomeAutomationBuildTime();
    virtual ~HomeAutomationBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    HomeAutomationBuildTime(const HomeAutomationBuildTime&);
    HomeAutomationBuildTime& operator=(const HomeAutomationBuildTime&);

  };

#endif  // D_HomeAutomationBuildTime_H
