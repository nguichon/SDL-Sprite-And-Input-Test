/*
 * Logger.cpp
 *
 *  Created on: Mar 29, 2012
 *      Author: nguichon
 */

#include "../include/Logger.h"


Logger* Logger::m_Instance = 0;

Logger::Logger() {
#ifdef LOGGER_ENABLED
	m_LogFile.open( "logs/current.log" );
#endif
}

Logger::~Logger() {
#ifdef LOGGER_ENABLED
	m_LogFile.close();
#endif
}

Logger* Logger::get() {
	if( m_Instance == 0 ) {
		m_Instance = new Logger();
	}
	return m_Instance;
}

void Logger::Output( std::string output ) {
#ifdef LOGGER_ENABLED
	m_LogFile << "[" << SDL_GetTicks() << "] - " << output << std::endl;
#endif
}

void Logger::Output( int output ) {
#ifdef LOGGER_ENABLED
	m_LogFile << "[" << SDL_GetTicks() << "] - " << output << std::endl;
#endif
}
void Logger::Output( double output ) {
#ifdef LOGGER_ENABLED
	m_LogFile << "[" << SDL_GetTicks() << "] - " << output << std::endl;
#endif
}

void Logger::Close() {
	delete m_Instance;
}

