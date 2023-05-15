#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <stdlib.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
int ADD_FRAMETIME = 0;

POINTFLOAT cameraPos = {0,0};
float lightPosition[] = {1, 1, 5, 1};

float xAlpha = 60;
float zAlpha = 45;

void moveCamera()
{
    float verSpeed = 0;
    float horSpeed = 0;

    if (GetKeyState(VK_UP) < 0) xAlpha = ++xAlpha > 180 ? 180 : xAlpha;
    if (GetKeyState(VK_DOWN) < 0) xAlpha = --xAlpha < 0 ? 0 : xAlpha;
    if (GetKeyState(VK_LEFT) < 0) zAlpha++;
    if (GetKeyState(VK_RIGHT) < 0) zAlpha--;


    float angle = -zAlpha / 180 * M_PI;

    if (GetKeyState('W') < 0) verSpeed = 0.1;
    if (GetKeyState('S') < 0) verSpeed = -0.1;
    if (GetKeyState('D') < 0) horSpeed = 0.1;
    if (GetKeyState('A') < 0) horSpeed = -0.1;

    if (verSpeed != 0)
    {
        cameraPos.x += sin(angle) * verSpeed;
        cameraPos.y += cos(angle) * verSpeed;
    };
    if (horSpeed != 0)
    {
        cameraPos.x += sin(angle + 0.5 * M_PI) * horSpeed;
        cameraPos.y += cos(angle + 0.5 * M_PI) * horSpeed;
    };


    glRotatef(-xAlpha, 1, 0, 0);
    glRotatef(-zAlpha, 0, 0, 1);

    glTranslatef(-cameraPos.x, -cameraPos.y, 0);
}

void drawChessBoard(float size)
{
    float verteces[] =
    {
         1,  1, 0,
         1, -1, 0,
        -1, -1, 0,
        -1,  1, 0
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glPushMatrix();

        if (fmod(size, 2) != 1)
        {
            glTranslatef(1,1,0);
        }

        glVertexPointer(3, GL_FLOAT, 0, verteces);
        for (int i = -size / 2; i < size / 2; i++)
        {
            for (int j = -size / 2; j < size / 2; j++)
            {
                glPushMatrix();

                    if ((i+j) % 2 == 0) glColor3f (0, 0, 0.3);
                    else glColor3f(1,1,1);
                    glTranslatef(i*2, j*2, 0);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

                glPopMatrix();

            }
        }

    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
};

void drawCoords()
{
    glPushMatrix();

        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3d(0.0f, 0.0f, 0.0f); glVertex3d(1.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3d(0.0f, 0.0f, 0.0f); glVertex3d(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3d(0.0f, 0.0f, 0.0f); glVertex3d(0.0f, 0.0f, 1.0f);
        glEnd();

    glPopMatrix();
}

void drawCube(){
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        7, 6, 5,
        5, 4, 7,
        4, 0, 3,
        3, 7, 4,
        4, 5, 1,
        1, 0, 4,
        3, 2, 6,
        6, 7, 3
    };
    GLfloat normals[] = {
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f
    };
    glColor3f(1, 0.3, 0.3);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          768,
                          768,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 80);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    float light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float light_specular[] = { 0.2f, 0.2f, 0.2f, 32.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glTranslatef(0, 0, -10);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glPushMatrix();

                moveCamera();

                glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

                drawCoords();

                drawChessBoard(8);

                glPushMatrix(); //Куб посередине

                    glScalef(2, 2, 2);
                    glTranslatef(0, 0, 0.5);
                    drawCube();

                glPopMatrix();

                glPushMatrix(); //Малый куб

                    glScalef(1, 1, 1);
                    glTranslatef(2, 2, 0.5);
                    drawCube();

                glPopMatrix();

                glPushMatrix(); //Большой куб

                    glScalef(3, 3, 3);
                    glTranslatef(-1, -1, 0.5);
                    drawCube();

                glPopMatrix();

            glPopMatrix();

            SwapBuffers(hDC);

            lightPosition[0] = 5 * sin(theta * 0.1);
            lightPosition[1] = 5 * cos(theta * 0.1);

            theta += 1.0f;
            Sleep (1 + ADD_FRAMETIME);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

