#pragma once

#if defined(EE_DEBUG)
#	if EE_PLATFORM == EE_PLATFORM_WIN32
#		ifndef EE_DEBUG_LOG_FILE
#		define EE_DEBUG_LOG_FILE "../../Logs/Debug.log"
#		endif
#	else
#		ifndef EE_DEBUG_LOG_FILE
#		define EE_DEBUG_LOG_FILE "../../Logs/Debug.log"
#		endif
#	endif

#	ifndef EE_LOG_DEBUG
#	define EE_LOG_DEBUG(message)																	\
		{																							\
				std::ofstream logFile(EE_DEBUG_LOG_FILE, std::ios_base::out | std::ios_base::app);	\
																									\
				logFile << "Log: " << __FILE__ << ":" << __LINE__;									\
				logFile << " inside " << __FUNCTION__ << std::endl;									\
				logFile << "Date: " << __DATE__ << std::endl;										\
				logFile << "Time: " << __TIME__ << std::endl;										\
				logFile << "Message: " << message << std::endl;										\
				logFile << "############################################: " << std::endl;			\
		}																					
#	endif
#else 
#	ifndef EE_DEBUG
#	define EE_DEBUG(message)
#	endif
#endif