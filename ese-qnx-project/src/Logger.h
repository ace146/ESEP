#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#define LOG_WRITE(text) Logger::getLogger().log(text, __PRETTY_FUNCTION__)

#define LOG_ENABLE_CONSOLE_OUTPUT Logger::getLogger().enableConsoleOutput();

using namespace std;

class Logger
{
public:
	static Logger& getLogger()
	{
		// Meyers Singleton.
		static Logger Instance;// Will be delete at the end.
		return Instance;
	}

    void log(string s, string prettyFunction)
    {
    	//Extract Classname
    	string classname;
        size_t colons = prettyFunction.find("::");
        size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
        size_t end = colons - begin;

        classname = prettyFunction.substr(begin,end);

   		if(couten_)
   		{
   			std::cout << "[SEC " << time(NULL) - timeoffset_ << "] " << "[" << classname << "] " << s << " " << std::endl;
   		}
   		logfile_ << "[SEC " << time(NULL) - timeoffset_ << "] " << "[" << classname << "] " << s << " " << std::endl; // time ticks in seconds. Check OS for more accurate timer.
    }

    void enableConsoleOutput()
    {
    	logfile_ << "Enabling parallel console output..." << endl;
    	couten_ = true;
    }

private:

	Logger()				// make these private because of singleton.
	: couten_(false),
	  timeoffset_(time(NULL))
	{
		logfile_.open("logging.txt",ios::trunc);
		logfile_<<"LOGFILE. Build: "<<__DATE__<<", "<<__TIME__<<endl;
	}

	~Logger()
	{
		logfile_<<"END OF LOGFILE"<<endl; logfile_.close();
	}
	ofstream logfile_;
	bool couten_;
	int timeoffset_;
};
#endif
