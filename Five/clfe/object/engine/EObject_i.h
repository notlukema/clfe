#ifndef CLFE_OBJECT_ENGINE_I_H
#define CLFE_OBJECT_ENGINE_I_H

#include "EMesh_i.h"

#include "clm/VectorImpl.h"
#include "clm/Quaternion.h"

#include "TypeTraits.h"

#include <cstdint>

namespace clfe
{

	// Object types

	enum class ObjectType
	{

		Static = 1,
		Dynamic = 2

	};

	// Object

	class Scene;

	class EObject
	{
	private:
		ObjectType type_;
		bool active;

		Vector<3, float> pos;
		Quaternion rot;

		uint32_t meshCount;
		EMesh** meshes;

		bool update_;

		void clearData();

		friend class Scene;
		EObject(uint32_t meshCount, EMesh** meshes, ObjectType type = ObjectType::Static, bool active = true, Vector<3, float> pos = Vector<3, float>(), Quaternion rot = Quaternion());
		~EObject();

		inline void requireUpdate()
		{
			update_ = true;
		}

	public:
		void update(uint32_t meshCount, EMesh** meshes, ObjectType type = ObjectType::Static, bool active = true, Vector<3, float> pos = Vector<3, float>(), Quaternion rot = Quaternion());

		inline ObjectType type() const
		{
			return type_;
		}

		inline bool isActive() const
		{
			return active;
		}

		inline void deactivate()
		{
			active = false;
		}

		inline void activate()
		{
			active = true;
		}

		inline void setActive(bool active)
		{
			this->active = active;
		}

		inline bool needUpdate() const
		{
			return update_;
		}

		inline void clearUpdate()
		{
			update_ = false;
		}

		// all the position and rotation things

	};

}

#endif