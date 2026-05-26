#ifndef CLFE_MATERIAL_VARIABLE_H
#define CLFE_MATERIAL_VARIABLE_H

#include "clfe/UniString.h"

#include "TypeTraits.h"

namespace clfe
{

	// Variable types

	enum class VariableType
	{

		INVALID = 0,
		UINT16 = 1,
		INT16 = 2,
		UINT32 = 3,
		INT32 = 4,
		FLOAT16 = 5,
		FLOAT32 = 6,
		DOUBLE32 = 7,
		DOUBLE64 = 8,

	};

	template <typename T>
	constexpr VariableType determineVariableType()
	{
		if constexpr (IsSame<T, uint16_t>)
		{
			return VariableType::UINT16;
		}
		if constexpr (IsSame<T, int16_t>)
		{
			return VariableType::INT16;
		}
		if constexpr (IsSame<T, uint32_t>)
		{
			return VariableType::UINT32;
		}
		if constexpr (IsSame<T, int32_t>)
		{
			return VariableType::INT32;
		}
		if constexpr (IsSame<T, float>)
		{
			if constexpr (sizeof(float) == 4)
			{
				return VariableType::FLOAT32;
			}
			if constexpr (sizeof(float) == 2)
			{
				return VariableType::FLOAT16;
			}
			return VariableType::INVALID;
		}
		if constexpr (IsSame<T, double>)
		{
			if constexpr (sizeof(double) == 8)
			{
				return VariableType::DOUBLE64;
			}
			if constexpr (sizeof(double) == 4)
			{
				return VariableType::DOUBLE32;
			}
			return VariableType::INVALID;
		}

		return VariableType::INVALID;
	}

	// Material variable base

	class MVariableBase
	{
	protected:
		const UniString name_;
		const VariableType type_;

		uint32_t references_;
		bool deleteOnNoRef;

		MVariableBase(UniString name, VariableType type, bool deleteOnNoRef = true);

	public:
		virtual const void* getRawData() = 0;
		virtual MVariableBase* copy(bool deleteOnNoRef) = 0;

		inline uint32_t references() const
		{
			return references_;
		}

		void addReference();
		void removeReference();

		inline bool deleteOnNoReferences() const
		{
			return deleteOnNoRef;
		}

		inline void setDeleteOnNoReferences(bool value)
		{
			deleteOnNoRef = value;
		}

		inline UniString name() const
		{
			return name_;
		}

		inline VariableType type() const
		{
			return type_;
		}

	};

	// Material variable

	template <typename T>
	class MVariable : public MVariableBase
	{
	private:
		T var;

	public:
		MVariable(T var, UniString name, VariableType type = VariableType::INVALID, bool deleteOnNoRef = true) : MVariableBase(name, type == VariableType::INVALID ? determineVariableType<T>() : type, deleteOnNoRef), var(var)
		{}

		virtual const void* getRawData() override
		{
			return &var;
		}

		virtual MVariableBase* copy(bool deleteOnNoRef) override
		{
			MVariable<T> var = new MVariable<T>(var, name_, type_, deleteOnNoRef);
		}

		inline T get() const
		{
			return var;
		}

		inline void set(T var)
		{
			this->var = var;
		}

	};

}

#endif