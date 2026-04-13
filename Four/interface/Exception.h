#ifndef CLFE_INTERFACE_EXCEPTION_H
#define CLFE_INTERFACE_EXCEPTION_H

#include <stdexcept>

namespace clfe
{

	using LogicError = std::logic_error;
	using InvalidArgument = std::invalid_argument;
	using DomainError = std::domain_error;
	using LengthError = std::length_error;
	using OutOfRange = std::out_of_range;
	using RuntimeError = std::runtime_error;
	using RangeError = std::range_error;
	using OverflowError = std::overflow_error;
	using UnderflowError = std::underflow_error;

}

#endif