#include "../header/graphical_user_interface.hpp"
#include "../header/genetic_algorithm.hpp"
#include <sstream>

#define KEY_ENTER 13
#define KEY_DOT 46
#define KEY_COMMA 44
#define KEY_R 114

Population pop = Population::get_onlyInstance();

using namespace std;

void render() {

    // background colour (BLACK)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
 
    // plots the function we're maximizing
    // we could just store them instead of calculating every single time but whatever
    glPointSize(3.0f);
    glBegin(GL_POINTS);
   	glColor3f(0.4f, 0.4f, 0.0f); // yellow
    for(Gene x = 0.0f; x < 1000.0f; x++) {
        FitType y = Population::evaluate_gene(x);
        glVertex2f((GLfloat) x, (GLfloat) y);	
    }
    glEnd();

	// Print genNumber and  to screen
	stringstream screenText;
    screenText << "Generation: " << pop.get_genNumber() << "   Mutation Rate: " << pop.get_mutationRate();
	glColor3f(0.0, 1.0, 0.0);   // Text color (GREEN)
	glRasterPos2f(0, 980);      // Print position
	for(char letter : screenText.str())
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);

	// Print best guy 
	screenText.str("");
    screenText << "Best fitness(" << pop.get_maxFitGene() << "): " << pop.get_maxFit();
	glColor3f(0.0, 1.0, 0.0);   // Text color (GREEN)
	glRasterPos2f(0,960);       // Print position
	for(char letter : screenText.str())
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);

	// Print help
    screenText.str("Enter->Next / r->Restart / .->TaxMut*2 / ,->TaxMut/2");
	glColor3f(0.0, 1.0, 0.0);   // Text color (GREEN)
	glRasterPos2f(0, 940);      // Print position
	for(char letter : screenText.str())
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);

    // Render the population
    vector<Gene> genes = pop.get_genes();
    vector<Gene> fitness = pop.get_fitness();
 	glPointSize(4.0f);
    glBegin(GL_POINTS);
   	glColor3f(0.0f, 1.0f, 0.0f); // GREEN
    for(size_t i = 0; i < pop.get_popSize(); i++)                       
        glVertex2f(genes[i], fitness[i]);	
    glEnd();

    // Render the best guy in RED
 	glPointSize(10.0f); //point size
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f); // RED
    glVertex2f(pop.get_maxFitGene(), pop.get_maxFit());
    glEnd();

    // Render
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case KEY_ENTER: {
            pop.next_generation();
	 	    glutPostRedisplay();
        } break;
        case KEY_DOT: {
            pop.double_mutationRate();
	 	    glutPostRedisplay();
        } break;
        case KEY_COMMA: {
            pop.halve_mutationRate();
	 	    glutPostRedisplay();
        } break;
        case KEY_R: {
            pop.initialize_population();
	 	    glutPostRedisplay();
        } break;
        default: {}
    }
}

void run_gui(int& argc, char* argv[]) {

    /* Creates a RGB full sized window */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("Evolutive Systems - Alice | Warrior");

    /* Sets the DisplayFunc and the KeyboardFunc */
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);

    /* Starts the drawing loop */
    gluOrtho2D(0, 1000, 0, 1000);
    glutMainLoop();
}

