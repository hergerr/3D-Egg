#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int model = 1;
static GLfloat theta[] = {0.0, 0.0, 0.0}; // trzy kąty obrotu

int getRand(int a, int b)
{
    return a + rand() % (b - a);
}

struct Point
{
    float x, y, z;
    int a, b, c;
};

const int N = 21;
vector<vector<Point>> points;

void spinEgg()
{

    theta[0] -= 0.5;
    if (theta[0] > 360.0)
        theta[0] -= 360.0;

    theta[1] -= 0.5;
    if (theta[1] > 360.0)
        theta[1] -= 360.0;

    theta[2] -= 0.5;
    if (theta[2] > 360.0)
        theta[2] -= 360.0;

    glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
}

void resizeVectors()
{
    points.resize(N);
    for (int i = 0; i < N; i++)
    {
        points[i].resize(N);
    }
}

float calcX(float u, float v)
{
    return (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(M_PI * v);
}

float calcY(float u, float v)
{
    return 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2) - 5;
}

float calcZ(float u, float v)
{
    return (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * sin(M_PI * v);
}

void calculatePoints()
{

    float u, v;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            u = float(i) / (N - 1);
            v = float(j) / (N - 1);

            points[i][j].x = calcX(u, v);
            points[i][j].y = calcY(u, v);
            points[i][j].z = calcZ(u, v);

            points[i][j].a = getRand(0, 255);
            points[i][j].b = getRand(0, 255);
            points[i][j].c = getRand(0, 255);
        }
    }
}

void printPoints()
{

    glColor3f(1, 1, 0);

    glBegin(GL_POINTS);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);

    glEnd();
}

void printLines()
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            glBegin(GL_LINES);
            glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
            glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);
            glEnd();

            glBegin(GL_LINES);
            glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
            glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);
            glEnd();

            glBegin(GL_LINES);
            glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
            glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);
            glEnd();
        }
    }
}

void printTriangles()
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            if (points[i][j].z > 0)
            {
                glBegin(GL_TRIANGLES);

                glColor3ub(points[i][j].a, points[i][j].b, points[i][j].c);
                glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);

                glColor3ub(points[i][j + 1].a, points[i][j + 1].b, points[i][j + 1].c);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);

                glColor3ub(points[i + 1][j].a, points[i + 1][j].b, points[i + 1][j].c);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);

                glEnd();

                glBegin(GL_TRIANGLES);

                glColor3ub(points[i + 1][j].a, points[i + 1][j].b, points[i + 1][j].c);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);

                glColor3ub(points[i + 1][j + 1].a, points[i + 1][j + 1].b, points[i + 1][j + 1].c);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);

                glColor3ub(points[i][j + 1].a, points[i][j + 1].b, points[i][j + 1].c);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);

                glEnd();
            }
            else
            {
                glBegin(GL_TRIANGLES);

                glColor3ub(points[i][j].a, points[i][j].b, points[i][j].c);
                glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);

                glColor3ub(points[i][j + 1].a, points[i][j + 1].b, points[i][j + 1].c);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);

                glColor3ub(points[i + 1][j].a, points[i + 1][j].b, points[i + 1][j].c);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);

                glEnd();

                glBegin(GL_TRIANGLES);

                glColor3ub(points[i + 1][j].a, points[i + 1][j].b, points[i + 1][j].c);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);

                glColor3ub(points[i + 1][j + 1].a, points[i + 1][j + 1].b, points[i + 1][j + 1].c);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);

                glColor3ub(points[i][j + 1].a, points[i][j + 1].b, points[i][j + 1].c);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);

                glEnd();
            }
        }
    }
}

void Egg()
{
    if (model == 1)
        printPoints();
    else if (model == 2)
        printLines();
    else
        printTriangles();
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

    // Axes();
    Egg();
    glFlush();
    glutSwapBuffers();
}

/*************************************************************************************/

// Funkcja ustalająca stan renderowania

void MyInit(void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    resizeVectors();
    calculatePoints();
    // Kolor czyszcący (wypełnienia okna) ustawiono na czarny
}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
    GLfloat AspectRatio;
    if (vertical == 0) // Zabezpieczenie przed dzieleniem przez 0
        vertical = 1;
    glViewport(0, 0, horizontal, vertical);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    if (horizontal <= vertical)

        glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
    else

        glOrtho(-7.5 * AspectRatio, 7.5 * AspectRatio, -7.5, 7.5, 10.0, -10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keys(unsigned char key, int x, int y)
{

    if (key == 'p')
        model = 1;
    if (key == 'w')
        model = 2;
    if (key == 's')
        model = 3;

    RenderScene(); // przerysowanie obrazu sceny
}

int main(int argc, char *argv[])
{

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(300, 300);

    glutInit(&argc, argv);
    glutCreateWindow("Uklad wspolrzednych 3D");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    MyInit();
    glutKeyboardFunc(keys);
    glutIdleFunc(spinEgg);

    glEnable(GL_DEPTH_TEST);
    // Włączenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

    return 0;
}
