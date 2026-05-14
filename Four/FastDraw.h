#pragma once

// Unecessary but whatever
#include "clfe/window/Window.h"
#include "clfe/window/WinWnd.h"
#include <windows.h>
//#include "glad/glad.h"
#include "clfe/pipeline/Opengl4_6/glad/glad.h"
#include "gl/GL.h"
#include "gl/GLU.h"
#include <random>
#include <ctime>

namespace clfe
{

    struct ColorNode {
        float r, g, b;
        ColorNode* next;
        ColorNode() : next(nullptr)
        {
            r = (std::rand() % 1001) / 1000.0f;
            g = (std::rand() % 1001) / 1000.0f;
            b = (std::rand() % 1001) / 1000.0f;
        }
        ~ColorNode()
        {
            free(next);
        }
        void set()
        {
            glColor4f(r, g, b, 1.0f);
        }
    };

    ColorNode* firstNode = nullptr;
    ColorNode* currentNode = nullptr;

    void nextColor()
    {
        if (currentNode->next == nullptr) {
            currentNode->next = new ColorNode();
        }
        currentNode = currentNode->next;
    }

	bool fastDrawInit(WinWnd* window)
	{
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        firstNode = new ColorNode();

        return true;
	}

    template <typename T>
    T* getColumnMajor(Matrix<4, 4, T> mat44)
    {
        auto arr = new T[16];
        for (int i = 0; i < 16; i++)
        {
            arr[i] = mat44.get(i / 4, i % 4);
        }
        return arr;
    }

    void dothefunny(Matrix<4, 4, float> change, double rad)
    {
        glMatrixMode(GL_MODELVIEW);
        float* a = getColumnMajor<float>(change);
        glLoadMatrixf(a);
        free(a);

        currentNode->set();
        glBegin(GL_QUADS);
        glVertex3d(-rad, -rad, -rad);
        glVertex3d(rad, -rad, -rad);
        glVertex3d(rad, rad, -rad);
        glVertex3d(-rad, rad, -rad);
        glEnd();

        nextColor();
        currentNode->set();
        glBegin(GL_QUADS);
        glVertex3d(-rad, -rad, rad);
        glVertex3d(rad, -rad, rad);
        glVertex3d(rad, rad, rad);
        glVertex3d(-rad, rad, rad);
        glEnd();

        nextColor();
        currentNode->set();
        glBegin(GL_QUADS);
        glVertex3d(-rad, -rad, -rad);
        glVertex3d(rad, -rad, -rad);
        glVertex3d(rad, -rad, rad);
        glVertex3d(-rad, -rad, rad);
        glEnd();

        nextColor();
        currentNode->set();
        glBegin(GL_QUADS);
        glVertex3d(-rad, rad, -rad);
        glVertex3d(rad, rad, -rad);
        glVertex3d(rad, rad, rad);
        glVertex3d(-rad, rad, rad);
        glEnd();

        nextColor();
        currentNode->set();
        glBegin(GL_QUADS);
        glVertex3d(-rad, -rad, -rad);
        glVertex3d(-rad, rad, -rad);
        glVertex3d(-rad, rad, rad);
        glVertex3d(-rad, -rad, rad);
        glEnd();

        nextColor();
        currentNode->set();
        glBegin(GL_QUADS);
        glVertex3d(rad, -rad, -rad);
        glVertex3d(rad, rad, -rad);
        glVertex3d(rad, rad, rad);
        glVertex3d(rad, -rad, rad);
        glEnd();
    }

	void fastDraw(WinWnd* window, float delf)
	{
        static float rot = 0;

        rot += delf;

        glViewport(0, 0, window->getWidth(), window->getHeight());
        glClearColor(0.9f, 0.9f, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45/*70 * Constd.pi / 180*/, (double)window->getWidth() / window->getHeight(), 1, -1);

        glTranslatef(0, 0, -5);

        currentNode = firstNode;
        dothefunny(
            mtranslate(0.8f, 0.0f, 0.0f)
            * mrotateX(0.3f)
            * mrotateZ(rot * 1.5f)
        , 0.4);

        dothefunny(
            mtranslate(-3.0f, 0.5f*sinf(rot * 1.5f), 0.0f)
            * mrotateX(Constf.Pi * sinf(rot * 3))
            * mrotateY(Constf.Pi * sinf(rot * 2 + 1))
            * mrotateZ(Constf.Pi * sinf(rot + 5))
        , 0.2);

        dothefunny(
            mtranslate(12.0f * sinf(rot * 5), -14.0f, -50 + 30.0f * cosf(rot * 5))
            * mrotateX(0.2f)
        , 3);

        dothefunny(
            mtranslate(-1.2f, 0.3f, 0.0f)
            * mrotateX(rot * 1.2f)
        , 0.4);

        dothefunny(
            mtranslate(3.0f, 1.0f, 0.0f)
            * mrotateY(rot * 9)
        , 0.2);

        SwapBuffers(window->getHDC());
	}

}