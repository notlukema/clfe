#include "Model.h"

namespace clfe
{

	Model* createRectModel(float dx, float dy, float dz, Material* material)
	{
		Model* m = new Model(material);
		float hdx = dx * 0.5f;
		float hdy = dy * 0.5f;
		float hdz = dz * 0.5f;
		m->addVertex(Vector<3, float>(hdx, hdy, hdz), Vector<2, float>(1.0f, 1.0f));
		m->addVertex(Vector<3, float>(-hdx, hdy, hdz), Vector<2, float>(0.0f, 1.0f));
		m->addVertex(Vector<3, float>(-hdx, -hdy, hdz), Vector<2, float>(0.0f, 0.0f));
		m->addVertex(Vector<3, float>(hdx, -hdy, hdz), Vector<2, float>(1.0f, 0.0f));
		m->addVertex(Vector<3, float>(hdx, hdy, -hdz), Vector<2, float>(1.0f, 1.0f));
		m->addVertex(Vector<3, float>(-hdx, hdy, -hdz), Vector<2, float>(0.0f, 1.0f));
		m->addVertex(Vector<3, float>(-hdx, -hdy, -hdz), Vector<2, float>(0.0f, 0.0f));
		m->addVertex(Vector<3, float>(hdx, -hdy, -hdz), Vector<2, float>(1.0f, 0.0f));

		m->addTri(0, 1, 2);
		m->addTri(0, 3, 2);
		m->addTri(4, 5, 6);
		m->addTri(4, 7, 6);

		// add others later

		return m;
	}

}