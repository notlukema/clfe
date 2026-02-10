#pragma once

// Unecessary but whatever
#include "clfe/window/Window.h"
#include "clfe/window/WinWnd.h"
#include <windows.h>
#include "glad/glad.h"
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

    static HDC hDC;

	bool fastDrawInit(WinWnd* window)
	{

        static PIXELFORMATDESCRIPTOR pfd =                  // pfd Tells Windows How We Want Things To Be
        {
            sizeof(PIXELFORMATDESCRIPTOR),                  // Size Of This Pixel Format Descriptor
            1,                              // Version Number
            PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
            PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
            PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
            PFD_TYPE_RGBA,                          // Request An RGBA Format
            32,                               // Select Our Color Depth
            0, 0, 0, 0, 0, 0,                       // Color Bits Ignored
            0,                              // No Alpha Buffer
            0,                              // Shift Bit Ignored
            0,                              // No Accumulation Buffer
            0, 0, 0, 0,                         // Accumulation Bits Ignored
            24,                             // Z-Buffer Depth
            0,                              // No Stencil Buffer
            0,                              // No Auxiliary Buffer
            PFD_MAIN_PLANE,                         // Main Drawing Layer
            0,                              // Reserved
            0, 0, 0                             // Layer Masks Ignored
        };

		hDC = GetDC(window->getHWND());
        std::cout << "1 " << hDC << "\n";
        if (!hDC) {
            return false;
		}

		int pixelFormat = ChoosePixelFormat(hDC, &pfd);
        std::cout << "2 " << pixelFormat << "\n";
        if (pixelFormat == 0) {
            return false;
        }

        std::cout << "3" << "\n";
        if (!SetPixelFormat(hDC, pixelFormat, &pfd)) {
            return false;
        }

        static HGLRC hRC = wglCreateContext(hDC);
        std::cout << "4 " << hRC << "\n";
        if (!hRC) {
            return false;
        }

        std::cout << "5" << "\n";
        if (!wglMakeCurrent(hDC, hRC)) {
            return false;
        }

        std::cout << gladLoadGL() << "\n";
        //std::cout << gladLoadGLLoader((GLADloadproc)wglGetProcAddress) << "\n";

        std::cout << glGetString(GL_VENDOR) << "\n";
        std::cout << glGetString(GL_RENDERER) << "\n";
        std::cout << glGetString(GL_VERSION) << "\n";

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
            translate(0.8f, 0.0f, 0.0f)
            * rotateX(0.3f)
            * rotateZ(rot * 1.5f)
        , 0.4);

        dothefunny(
            translate(-3.0f, 0.5f*sinf(rot * 1.5f), 0.0f)
            * rotateX(Constf.pi * sinf(rot * 3))
            * rotateY(Constf.pi * sinf(rot * 2 + 1))
            * rotateZ(Constf.pi * sinf(rot + 5))
        , 0.2);

        dothefunny(
            translate(12.0f * sinf(rot * 5), -14.0f, -50 + 30.0f * cosf(rot * 5))
            * rotateX(0.2f)
        , 3);

        dothefunny(
            translate(-1.2f, 0.3f, 0.0f)
            * rotateX(rot * 1.2f)
        , 0.4);

        dothefunny(
            translate(3.0f, 1.0f, 0.0f)
            * rotateY(rot * 9)
        , 0.2);

        SwapBuffers(hDC);
	}

}