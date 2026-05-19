#ifndef CLFE_OBJECT_H
#define CLFE_OBJECT_H

#include "ObjectData.h"

#include "clm/Vector3.h"

#include <cstdint>

namespace clfe
{

	inline constexpr uint16_t ObjectDataOptimization = 10;

	class Object
	{
	public:
		struct Node
		{

			ObjectData* data;
			Node* next;
			Node(ObjectData* data) : data(data), next(nullptr) {}

		};

	private:
		ObjectData* smallData[ObjectDataOptimization];
		Node* first;
		uint16_t dataCount;

		Vector3f position;

	public:
		Object();
		Object(float x, float y, float z);
		Object(const Vector3f& position);
		~Object();

		inline uint16_t getDataCount() const
		{
			return dataCount;
		}

		ObjectData* getDataType(DataID_t type) const;
		Object* addData(ObjectData* data);
		bool removeData(DataID_t type);

		inline Vector3f getPosition() const
		{
			return position;
		}

		inline Vector3f& getPositionRef()
		{
			return position;
		}

		inline float getX() const
		{
			return position.x();
		}

		inline float getY() const
		{
			return position.y();
		}

		inline float getZ() const
		{
			return position.z();
		}

		void setPosition(const Vector3f& position);
		void setPosition(float x, float y, float z);
		void setX(float x);
		void setY(float y);
		void setZ(float z);

	};

}

#endif