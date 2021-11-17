#include "GraphicalUserInterface.hpp"

#include <sstream>

#include "GeneticAlgorithm.hpp"

namespace GeneticAlgorithm {

    constexpr int KEY_ENTER = 13;
    constexpr int KEY_DOT = 46;
    constexpr int KEY_COMMA = 44;
    constexpr int KEY_R = 114;

    void Render() {
        static const auto& pop = GeneticAlgorithm::Population::Get();

        // background colour (BLACK)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // plots the function we're maximizing
        // we could just store them instead of calculating every single time but whatever
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        glColor3f(0.4f, 0.4f, 0.0f);  // yellow
        for (GeneticAlgorithm::Gene x = 0.0f; x < 1000.0f; x++) {
            GeneticAlgorithm::FitType y = GeneticAlgorithm::Population::EvaluateGene(x);
            glVertex2f((GLfloat)x, (GLfloat)y);
        }
        glEnd();

        // Print GenNumber and MutationRate to screen
        std::stringstream screenText;
        screenText << "Generation: " << pop.GenNumber() << "   Mutation Rate: " << pop.MutationRate();
        glColor3f(0.0, 1.0, 0.0);  // Text color (GREEN)
        glRasterPos2f(0, 980);     // Print position
        for (const char& letter : screenText.str())
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);

        // Print best guy
        screenText.str("");
        screenText << "Best fitness(" << pop.MaxFitGene() << "): " << pop.MaxFit();
        glColor3f(0.0, 1.0, 0.0);  // Text color (GREEN)
        glRasterPos2f(0, 960);     // Print position
        for (const char& letter : screenText.str())
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);

        // Print help
        screenText.str("Enter->Next / r->Restart / .->TaxMut*2 / ,->TaxMut/2");
        glColor3f(0.0, 1.0, 0.0);  // Text color (GREEN)
        glRasterPos2f(0, 940);     // Print position
        for (char letter : screenText.str())
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);

        // Render the population
        glPointSize(4.0f);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);  // GREEN
        for (const auto& citizen : pop.Citizens())
            glVertex2f(citizen.gene, citizen.fitness);
        glEnd();

        // Render the best guy in RED
        glPointSize(10.0f);  //point size
        glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);  // RED
        glVertex2f(pop.MaxFitGene(), pop.MaxFit());
        glEnd();

        // Render
        glFlush();
    }

    void Keyboard(unsigned char key, int x, int y) {
        static auto& pop = GeneticAlgorithm::Population::Get();
        switch (key) {
            case KEY_ENTER: {
                pop.NextGeneration();
                glutPostRedisplay();
            } break;
            case KEY_DOT: {
                pop.DoubleMutationRate();
                glutPostRedisplay();
            } break;
            case KEY_COMMA: {
                pop.HalveMutationRate();
                glutPostRedisplay();
            } break;
            case KEY_R: {
                pop.Init();
                glutPostRedisplay();
            } break;
            default: {
            }
        }
    }

    void RunGui(int& argc, char* argv[]) {
        // Creates a RGB full sized window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
        glutCreateWindow("Evolutive Systems - Alice | Warrior");

        // Sets the DisplayFunc and the KeyboardFunc
        glutDisplayFunc(Render);
        glutKeyboardFunc(Keyboard);

        // Starts the drawing loop
        gluOrtho2D(0, 1000, 0, 1000);
        glutMainLoop();
    }

    void PlotStuff() {
        FILE* gnuplot = popen("gnuplot", "w");
        fprintf(gnuplot, "set term pngcairo\nset output 'plots/fitness.png'\n");
        fprintf(gnuplot, "set title 'Fitness plot'\nset key outside\nset xlabel 'Generation'\nset ylabel 'Fitness'\n");
        fprintf(gnuplot, "plot 'data/maxFit.txt' title 'MaxFit' with lines, 'data/avgFit.txt' title 'AvgFit' with lines");
        fclose(gnuplot);

        FILE* gnuplot2 = popen("gnuplot", "w");
        fprintf(gnuplot2, "set term pngcairo\nset output 'plots/mutationRate.png'\n");
        fprintf(gnuplot2, "set title 'Mutation Rate'\nset key left top\nset xlabel 'Generation'\nset ylabel 'Mutation Rate'\nset logscale y\n");
        fprintf(gnuplot2, "plot 'data/mutationRate.txt' title 'Mutation Rate' with lines");
        fclose(gnuplot2);
    }
}  // namespace GeneticAlgorithm
