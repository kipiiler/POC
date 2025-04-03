#include <iostream>

#include "Renderer.hpp"

int main() {
    Renderer renderer(800, 600); // Create a Renderer object with specified width and height
    try {
        renderer.run(); // Start the rendering loop
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return -1; // Return an error code if an exception occurs
    }
    return 0;
}
