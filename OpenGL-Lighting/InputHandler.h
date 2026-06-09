/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   InputHandler.h
 Description :   Declares the InputHandler Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include <glfw3.h>
#include <glm.hpp>
#include <unordered_map>

/// <summary>
///     Input Handler singleton class that manages keyboard and
///     mouse input via both direct query and GLFW callbacks.
/// </summary>
class InputHandler {
private:
    // -- Input Handler Properties -- //
    GLFWwindow* m_window = nullptr;

    // Stores keys that were pressed on THIS frame only (cleared by flush())
    std::unordered_map<int, bool> m_keyPressedThisFrame;
    std::unordered_map<int, bool> m_mouseButtonPressedThisFrame;
    // -- //

    //==================================================
    // PRIVATE CONSTRUCTORS SINGLETON DESIGN PATTERN
    //==================================================

    /// <summary>
    ///     Private default constructor.
    /// </summary>
    InputHandler() = default;

    /// <summary>
    ///     Private default destructor.
    /// </summary>
    ~InputHandler() = default;

    /// <summary>
    ///     Private deleted copy constructor.
    /// </summary>=
    InputHandler(const InputHandler&) = delete;

    /// <summary>
    ///     Private delete assignment operator.
    /// </summary>
    InputHandler& operator=(const InputHandler&) = delete;

public:
    //==================================================
    // SINGLETON INSTANCE DESIGN PATTERN
    //==================================================

    /// <summary>
    ///     Singleton instance of the Input Handler.
    /// </summary>
    /// 
    /// <returns>
    ///     The singleton instance of the Input Handler.
    /// </returns>
    static InputHandler& getInstance();

    /// <summary>
    ///     Initialise the Input Handler.
    ///     Call once after GLFW window creation to register the GLFW callback.
    /// </summary>
    /// <param name="window"></param>
    void initialise(GLFWwindow* window);

    //==================================================
    // PRIMARY INPUT HANDLER METHODS
    //==================================================

    /// <summary>
    ///     Get the axis from per-frame key (held down) queries for movement.
    ///     Normally, W and S for forward (+Y) and backward (-Y) movements
    ///     whereas A and D for right (+X) and left (-X) movements.
    /// </summary>
    /// 
    /// <param name="positiveKey">Key for a position axis.</param>
    /// <param name="negativeKey">Key for a negative axis.</param>
    /// 
    /// <returns>
    ///     Tri-Bool Pattern:
    ///     Both held or neither held = 0,
    ///     Only Positive = 1,
    ///     Only Negative = -1.
    /// </returns>
    int getAxis(int positiveKey, int negativeKey) const;

    // Returns true every frame the key is held down

    /// <summary>
    ///     Per-frame key held down queries.
    ///     Check if the key is being held down per frame.
    /// </summary>
    /// 
    /// <param name="glfwKey">Key to check if it is being held down.</param>
    /// 
    /// <returns>
    ///     True if the key is being held down; false otherwise.
    /// </returns>
    bool isKeyHeld(int glfwKey) const;

    /// <summary>
    ///     Single key press queries.
    ///     Only checks the first frame the key was pressed.
    ///     Best used for toggles or actions.
    /// </summary>
    /// 
    /// <param name="glfwKey">Key to check if it was pressed.</param>
    /// 
    /// <returns>
    ///     True on the first frame the key was pressed; false otherwise.
    /// </returns>
    bool wasKeyPressed(int glfwKey) const;

    /// <summary>
    ///     Get the position of the cursor in relation to the window coordinates.
    /// </summary>
    /// 
    /// <returns>
    ///     2D floating-point vector representing the position of the mouse.
    /// </returns>
    glm::vec2 getCursorPos() const;

    /// <summary>
    ///     Single mouse button press queries.
    ///     Only checks the first frame the key was pressed.
    ///     Best used for toggles or actions.
    /// </summary>
    /// 
    /// <param name="glfwKey">Mouse button to check if it was pressed.</param>
    /// 
    /// <returns>
    ///     True on the first frame the mouse button was pressed; false otherwise.
    /// /// </returns>
    bool wasMouseButtonPressed(int glfwButton) const;

    /// <summary>
    ///     Called internally by the GLFW callback.
    ///     Registers the each key pressed into the key pressed hash map.
    ///     DO NOT CALL MANUALLY.
    /// </summary>
    void onKey(int key, int action);

    /// <summary>
    ///     Called internally by the GLFW callback.
    ///     Registers the each key pressed into the mouse button pressed hash map.
    ///     DO NOT CALL MANUALLY.
    /// </summary>
    void onMouseButton(int button, int action);
    
    /// <summary>
    ///     Clears the single press hash maps.
    ///     Call at the end of the frame to ensure single press checks are valid.
    /// </summary>
    void flush();
};