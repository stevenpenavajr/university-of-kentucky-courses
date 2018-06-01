/*
* Steven Penava
* Dr. Brent Seales
* CS 335: Program 2
* 11/01/2017
*
* Individual cell in grid
*/

// Imports
import javax.swing.*;
import java.awt.*;

// Cell on grid
public class Cell extends JPanel {

    // Initializations
    public int row,col;
    public int[] edges = {1,1,1,1}; // top, left, bottom, right

    // Constructor
    Cell() {
        super();
        row = 0;
        col = 0;
        super.setBackground(Color.BLACK);
    }

    // Functions that allow the program to remember previous cells' edges
    public void setTop(int x) {
        edges[0] = x;
    }
    public void setLeft(int x) {
        edges[1] = x;
    }
    public void setBottom(int x) {
        edges[2] = x;
    }
    public void setRight(int x) {
        edges[3] = x;
    }

}