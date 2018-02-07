#pragma once

#if defined(EE_DEBUG)
#	if EE_PLATFORM == EE_PLATFORM_WIN32
#		ifndef EE_LOG_FILE
#		define EE_LOG_FILE "../../Logs/Erorrs.log"
#		endif
#	else
#		ifndef EE_LOG_FILE
#		define EE_LOG_FILE "../../Logs/Erorrs.log"
#		endif
#	endif

#	ifndef EE_ASSERT_ERROR
#	define EE_ASSERT_ERROR(condition, error)													\
		{																						\
			if (!(condition))																	\
			{																					\
				std::ofstream errorFile(EE_LOG_FILE, std::ios_base::out | std::ios_base::app);	\
																								\
				errorFile << "Assertion failed at " << __FILE__ << ":" << __LINE__;				\
				errorFile << " inside " << __FUNCTION__ << std::endl;							\
				errorFile << "Date: " << __DATE__ << std::endl;									\
				errorFile << "Time: " << __TIME__ << std::endl;									\
				errorFile << "Error: " << error << std::endl;									\
				errorFile << "Condition: " << condition << std::endl;							\
				errorFile << "############################################: " << std::endl;		\
				abort();																		\
			}																					\
		}																					
#	endif

#	ifndef EE_ASSERT_ERROR_SHORT
#	define EE_ASSERT_ERROR_SHORT(condition, abort)												\
		{																						\
			if (!(condition))																	\
			{																					\
				std::ofstream errorFile(EE_LOG_FILE, std::ios_base::out | std::ios_base::app);	\
																								\
				errorFile << "Assertion failed at " << __FILE__ << ":" << __LINE__;				\
				errorFile << " inside " << __FUNCTION__ << std::endl;							\
				errorFile << "Date: " << __DATE__ << std::endl;									\
				errorFile << "Time: " << __TIME__ << std::endl;									\
				errorFile << "Condition: " << condition;										\
				errorFile << "############################################: " << std::endl;		\
				abort();																		\
			}																					\
		}																					
#	endif
#else 
#	ifndef EE_ASSERT_ERROR
#	define EE_ASSERT_ERROR(condition, error, abort) (condition)
#	endif

#	ifndef EE_ASSERT_ERROR_SHORT
#	define EE_ASSERT_ERROR_SHORT(condition, abort) (condition)
#	endif
#endif