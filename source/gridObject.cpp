#include "gridObject.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>


gridObject::gridObject() { // Assign current value of nextId to id and increment it

    // Initialize the model matrix
    modelMatrix = glm::mat4(1.0f);

    // Generate and bind VAO, VBO, and EBO
    // Generate and bind VAO, VBO, and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // TODO: P1aTask1 - Modify vertices and indices to draw grid and axis lines. Note: multiple vertices at the origin will be needed due to different color of axis lines.

    // Tetrahedron vertices with positions and colors
    std::cout << "Test" << std::endl;

    std::vector<GLfloat> vertices = {
        // Positions          // Colors
         0.0f,  0.0f,  0.0f,   1.0f, 0.0f, 0.0f,  // X Axis
         5.0f,  0.0f,  0.0f,   1.0f, 0.0f, 0.0f,
         0.0f,  0.0f,  0.0f,   0.0f, 1.0f, 0.0f,  // Y Axis
         0.0f,  5.0f,  0.0f,   0.0f, 1.0f, 0.0f,
         0.0f,  0.0f,  0.0f,   0.0f, 0.0f, 1.0f,  // Z Axis
         0.0f,  0.0f,  5.0f,   0.0f, 0.0f, 1.0f,

    };

    // generate vertices for grid
    for (int i = -5; i <= 5; i++) {
        for (int j = -5; j <= 5; j++) {
            if ((i == -5 || i == 5) || (j == -5 || j == 5)) {
                vertices.push_back(i);
                vertices.push_back(0);
                vertices.push_back(j);

                vertices.push_back(1);
                vertices.push_back(1);
                vertices.push_back(1);

                std::cout << i << ", 0, " << j << std::endl;
            }
            else {
                std::cout << "else" << std::endl;
            }

        }
    }


    // Tetrahedron indices
    std::vector<GLuint> indices = {
        0, 1,
        2, 3,
        4, 5,
        6, 16,
        17, 18,
        19, 20,
        21, 22,
        23, 24,
        25, 26,
        27, 28,
        29, 30,
        31, 32,
        33, 34,
        35, 45,
        6, 35,
        7, 36,
        8, 37,
        9, 38,
        10, 39,
        11, 40,
        12, 41,
        13, 42,
        14, 43,
        15, 44,
        16, 45,
    };



    numIndices = (GLsizei)indices.size();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Load and compile shaders
    shaderProgram = LoadShaders("gridVertexShader.glsl", "gridFragmentShader.glsl");
}

gridObject::~gridObject() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

}

void gridObject::draw(const glm::mat4& view, const glm::mat4& projection) {
    glUseProgram(shaderProgram);

    // TODO: P1aTask1 - Compute the MVP matrix and send to shader as a uniform. Refer to meshObject.cpp as reference.
    glm::mat4 MVP = projection * view * modelMatrix;
    GLuint matrixID = glGetUniformLocation(shaderProgram, "MVP");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(MVP));

    // TODO: P1aTask1 - Bind the VAO and draw the grid using glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
