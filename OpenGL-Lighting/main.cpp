/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   main.cpp
 Description :   Initilises and Runs an OpenGL Window
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include "Window.h"

int main() {
	// Create a Window
	Window window(1200, 800);

	// Initialise Window
	if (window.initialize(4 /*Major*/, 3 /*Minor*/) == true) {
		// Process the Window
		while (window.process());
	} else {
		// Failed to Initialise a Window
		return -1; // Return -1 to inidicate an error has occurred
	}

	return 0;
}