/*
 * Logger.h
 *
 *  Created on: Mar 29, 2012
 *      Author: nguichon
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#define LOGGER_ENABLED
#include <string>
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>

class Logger {
private:
	static Logger* m_Instance;
	std::ofstream m_LogFile;
	Logger();
	~Logger();
public:
	static Logger* get();
	void Output( std::string );
	void Output( int );
	void Output( double );
	static void Close();
};


#endif /* LOGGER_H_ */
