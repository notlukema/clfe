#ifndef CLE_ERRORS_H
#define CLE_ERRORS_H

#include <iostream>

namespace cle {
	/*
	enum class ErrorCode {
		NONE,
		UNKNOWN_ERROR,
		UNKNOWN_SIZE,
		STRING_CONVERT_FAILED,
		WINDOW_CREATION_FAILED,
	};

	const char* getErrorMessage(ErrorCode code) {
		// figure out later, might remove or smth
		switch (code) {
			case ErrorCode::NONE:
				return "No error.";
			case ErrorCode::UNKNOWN_ERROR:
				return "An unknown error occurred.";
			case ErrorCode::UNKNOWN_SIZE:
				return "";
			default:
				return "Unrecognized error code.";
		}
	}
	*/

	void logError(const char* message);
}

#endif