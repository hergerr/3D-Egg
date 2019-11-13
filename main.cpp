#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef float point3[3];

struct Point
{
    float x, y, z;
};

const int N = 50;
vector<vector<Point>> points;


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
            u = float(i) / (N-1);
            v = float(j) / (N-1);

            points[i][j].x = calcX(u, v);
            points[i][j].y = calcY(u, v);
            points[i][j].z = calcZ(u, v);
        }
    }
}

void printPoints()
{

    glColor3f(1, 1, 0);

    glBegin(GL_POINTS);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            glVertex3f(points[i][j].x,points[i][j].y, points[i][j].z);

    glEnd();
}

void printLines(){
    for (int i = 0; i < N - 1; i++){
        for (int j = 0; j < N - 1; j++){
            glBegin(GL_LINES);
                glVertex3f(points[i][j].x,points[i][j].y, points[i][j].z);
                glVertex3f(points[i][j + 1].x,points[i][j + 1].y, points[i][j + 1].z);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(points[i][j].x,points[i][j].y, points[i][j].z);
                glVertex3f(points[i + 1][j + 1].x,points[i + 1][j + 1].y, points[i + 1][j + 1].z);
            glEnd();
        
            glBegin(GL_LINES);
                glVertex3f(points[i][j].x,points[i][j].y, points[i][j].z);
                glVertex3f(points[i + 1][j].x,points[i + 1][j].y, points[i + 1][j].z);
            glEnd();
        }        
    }
}

void printTriangles(){

}

void Egg()
{
    resizeVectors();
    calculatePoints();
    // printPoints();
    printLines();
}

void Axes(void)
{

    point3 x_min = {-5.0, 0.0, 0.0};
    point3 x_max = {5.0, 0.0, 0.0};
    // początek i koniec obrazu osi x

    point3 y_min = {0.0, -5.0, 0.0};
    point3 y_max = {0.0, 5.0, 0.0};
    // początek i koniec obrazu osi y

    point3 z_min = {0.0, 0.0, -5.0};
    point3 z_max = {0.0, 0.0, 5.0};
    //  początek i koniec obrazu osi y

    glColor3f(1.0f, 0.0f, 0.0f); // kolor rysowania osi - czerwony
    glBegin(GL_LINES);           // rysowanie osi x
    glVertex3fv(x_min);
    glVertex3fv(x_max);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // kolor rysowania - zielony
    glBegin(GL_LINES);           // rysowanie osi y

    glVertex3fv(y_min);
    glVertex3fv(y_max);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // kolor rysowania - niebieski
    glBegin(GL_LINES);           // rysowanie osi z

    glVertex3fv(z_min);
    glVertex3fv(z_max);
    glEnd();
}

/*************************************************************************************/

// Funkcja określająca co ma być rysowane (zawsze wywoływana gdy trzeba
// przerysować scenę)

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    Egg();
    glFlush();
    glutSwapBuffers();
}

/*************************************************************************************/

// Funkcja ustalająca stan renderowania

void MyInit(void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    // Deklaracja zmiennej AspectRatio  określającej proporcję
    // wymiarów okna
    if (vertical == 0) // Zabezpieczenie przed dzieleniem przez 0
        vertical = 1;
    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkościokna okna widoku (viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)
    glMatrixMode(GL_PROJECTION);
    // Przełączenie macierzy bieżącej na macierz projekcji
    glLoadIdentity();
    // Czyszcznie macierzy bieżącej
    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    // Wyznaczenie współczynnika  proporcji okna
    // Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
    // przestrzeni ograniczającej pozwalającej zachować właściwe
    // proporcje rysowanego obiektu.
    // Do okreslenia przestrzeni ograniczjącej służy funkcja
    // glOrtho(...)
    if (horizontal <= vertical)

        glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
    else

        glOrtho(-7.5 * AspectRatio, 7.5 * AspectRatio, -7.5, 7.5, 10.0, -10.0);
    glMatrixMode(GL_MODELVIEW);
    // Przełączenie macierzy bieżącej na macierz widoku modelu

    glLoadIdentity();
    // Czyszcenie macierzy bieżącej
}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli

int main(int argc, char *argv[])
{

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(300, 300);

    glutInit(&argc, argv);

    glutCreateWindow("Uklad wspolrzednych 3D");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    MyInit();
    glEnable(GL_DEPTH_TEST);
    // Włączenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

    return 0;
}
