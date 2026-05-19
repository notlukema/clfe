#include "Object.h"

#include "clfe/Log.h"

namespace clfe
{

	Object::Object() : smallData{}, first(nullptr), dataCount(0), position(Vector3f(0.0f, 0.0f, 0.0f)) {}

	Object::Object(float x, float y, float z) : smallData{}, first(nullptr), dataCount(0), position(Vector3f(x, y, z)) {}

	Object::Object(const Vector3f& position) : smallData{}, first(nullptr), dataCount(0), position(position) {}

	Object::~Object()
	{
		for (uint16_t i = 0; i < dataCount && i < ObjectDataOptimization; i++)
		{
			delete smallData[i];
		}

		Node* current = first;
		while (current != nullptr)
		{
			Node* next = current->next;
			delete current->data;
			delete current;
			current = next;
		}
	}

	ObjectData* Object::getDataType(DataID_t type) const
	{
		for (uint16_t i = 0; i < dataCount && i < ObjectDataOptimization; i++)
		{
			if (smallData[i]->getType() == type)
			{
				return smallData[i];
			}
		}
		Node* current = first;
		while (current != nullptr)
		{
			if (current->data->getType() == type)
			{
				return current->data;
			}
			current = current->next;
		}
		return nullptr;
	}

	Object* Object::addData(ObjectData* data)
	{
		if (getDataType(data->getType()) != nullptr)
		{
			CLFE_ERROR("Attempting to add already existing data to object!");
			return this;
		}

		if (dataCount < ObjectDataOptimization)
		{
			smallData[dataCount] = data;
		}
		else
		{
			Node* newNode = new Node(data);
			newNode->next = first;
			first = newNode;
		}
		dataCount++;
		return this;
	}

	bool Object::removeData(DataID_t type)
	{
		// Test small data array
		for (uint16_t i = 0; i < dataCount && i < ObjectDataOptimization; i++)
		{
			if (smallData[i]->getType() == type)
			{
				delete smallData[i];

				// Move small data array entries down
				while (i < dataCount - 1 && i < ObjectDataOptimization - 1)
				{
					smallData[i] = smallData[i + 1];
					i++;
				}

				// Fill in small data array if linked list is not empty
				if (dataCount > ObjectDataOptimization)
				{
					if (first == nullptr)
					{
						CLFE_ERROR("Data count is greater than optimization limit but linked list is empty!");
						return true;
					}
					smallData[ObjectDataOptimization - 1] = first->data;
					first = first->next;
				}
				dataCount--;
				return true;
			}
		}

		// Test first node
		if (first == nullptr)
		{
			return false;
		}
		else
		{
			if (first->data->getType() == type)
			{
				Node* node = first;
				first = first->next;
				delete node->data;
				delete node;
				dataCount--;
				return true;
			}
		}

		// Test rest of nodes
		Node* current = first->next;
		Node* prev = first;
		while (current != nullptr)
		{
			if (current->data->getType() == type)
			{
				prev->next = current->next;
				delete current->data;
				delete current;
				dataCount--;
				return true;
			}
			prev = current;
			current = current->next;
		}

		return false;
	}

	void Object::setPosition(const Vector3f& position)
	{
		this->position = position;
	}

	void Object::setPosition(float x, float y, float z)
	{
		this->position.set(x, y, z);
	}

	void Object::setX(float x)
	{
		this->position.x(x);
	}

	void Object::setY(float y)
	{
		this->position.y(y);
	}

	void Object::setZ(float z)
	{
		this->position.z(z);
	}

}