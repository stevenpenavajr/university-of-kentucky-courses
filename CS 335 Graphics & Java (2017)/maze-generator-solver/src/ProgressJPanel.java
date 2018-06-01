/*
* Steven Penava
* Dr. Brent Seales
* CS 335: Program 2
* 11/01/2017
*
* Progress Pane
*/

// Imports
import javax.swing.*;
import java.awt.*;

public class ProgressJPanel extends JPanel {

    // Initialization
    private JLabel visitedLbl;

    // Constructor
    ProgressJPanel() {
        visitedLbl = new JLabel("Visited: 0% of cells.");
        visitedLbl.setHorizontalAlignment(0);
        super.add(visitedLbl);
        super.setBackground(Color.CYAN);
        super.setPreferredSize(new Dimension(10, 30));
        super.setLayout(new GridLayout(1,1));
    }

    // Returning label
    public JLabel getVisitedLbl() { return visitedLbl; }
}
