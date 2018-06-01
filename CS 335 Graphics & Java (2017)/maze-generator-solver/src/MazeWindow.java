/*
* Steven Penava
* Dr. Brent Seales
* CS 335: Program 2
* 11/01/2017
*
* Driver
*/

// Imports
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

// Window JFrame
public class MazeWindow extends JFrame implements ActionListener, ChangeListener {

    // Initializations
    private MazeJPanel mazePanel;
    private SettingsJPanel settingsPanel;
    private ProgressJPanel progressPanel;
    private int DEFAULT_ROWS = 30;
    private int DEFAULT_COLS = 30;
    private int runCounter;

    // Constructor
    MazeWindow() {
        Container c = getContentPane();
        settingsPanel = new SettingsJPanel(this, this);
        progressPanel = new ProgressJPanel();
        mazePanel = new MazeJPanel(DEFAULT_ROWS, DEFAULT_COLS);

        c.add(settingsPanel, BorderLayout.EAST);
        c.add(progressPanel, BorderLayout.SOUTH);
        c.add(mazePanel, BorderLayout.CENTER);

        runCounter = 0;

        super.setSize(700,500);
        super.setLocationRelativeTo(null);
        super.setTitle("The Maze");
        super.setVisible(true);
    }

    // Driver
    public static void main(String args[]){
        MazeWindow Maze = new MazeWindow();
    }

    // Button presses
    public void actionPerformed(ActionEvent e) {
        JButton clickedButton;
        String buttonText;

        // Handling type errors
        try {
            clickedButton = (JButton)e.getSource();
            buttonText = clickedButton.getText();
            boolean genAnimationEnabled = settingsPanel.getShowGenCBValue();
            boolean solveAnimationEnabled = settingsPanel.getSolveCBValue();

            if (buttonText == "Generate") {

                progressPanel.getVisitedLbl().setText("Visited: 0% of cells.");
                settingsPanel.enableSolveFunctions();
                settingsPanel.disableGenFunctions();

                if (genAnimationEnabled) {
                    settingsPanel.disableGenFunctions();
                    settingsPanel.enablePauseFunction();
                }

                // Removing cells if it isn't the first run
                runCounter++;
                if (runCounter > 1) {
                    mazePanel.removeCellsFromGrid();
                }

                // General grid setup
                mazePanel.setRows(settingsPanel.getRows());
                mazePanel.setColumns(settingsPanel.getCols());
                mazePanel.resetGridSize();
                mazePanel.resetArraySize();
                mazePanel.fillCellArray();
                mazePanel.placeCellsOnGrid();
                mazePanel.revalidate();
                mazePanel.repaint();

                // Generating the maze
                mazePanel.generateMaze(genAnimationEnabled, settingsPanel.getSpeedSlider().getValue(), progressPanel.getVisitedLbl());
            }

            if (buttonText == "Solve") {

                progressPanel.getVisitedLbl().setText("Visited: 0% of cells.");

                if (solveAnimationEnabled) {
                    settingsPanel.enablePauseFunction();
                }
                if (!mazePanel.isGenerating()) { // handling timer complications
                    settingsPanel.disableSolveFunctions();
                    mazePanel.solveMaze(solveAnimationEnabled, settingsPanel.getSpeedSlider().getValue(), progressPanel.getVisitedLbl());
                }

            }

            if (buttonText == "Pause/Resume") {

                if (mazePanel.isGenerating()) {
                    mazePanel.setSolveFalse();

                    if(mazePanel.mazeTimerRunning()) {
                        mazePanel.stopMazeTimer();
                    }
                    else {
                        mazePanel.startMazeTimer();
                    }
                }

                if (mazePanel.isSolving()) {
                    if(mazePanel.solveTimerRunning()){
                        mazePanel.stopSolveTimer();
                    }
                    else {
                        mazePanel.startSolveTimer();
                    }
                }
            }

            if (buttonText == "Reset") {

                progressPanel.getVisitedLbl().setText("Visited: 0% of cells.");
                settingsPanel.resetInterface();

                if (mazePanel.mazeTimerRunning()) {
                    mazePanel.stopMazeTimer();

                }

                if (mazePanel.solveTimerRunning()) {
                    mazePanel.stopSolveTimer();
                }

                // General reset maintenance
                settingsPanel.disableSolveFunctions();
                mazePanel.removeCellsFromGrid();
                mazePanel.setRows(settingsPanel.getRows());
                mazePanel.setColumns(settingsPanel.getCols());
                mazePanel.resetGridSize();
                mazePanel.resetArraySize();
                mazePanel.fillCellArray();
                mazePanel.placeCellsOnGrid();
                mazePanel.revalidate();
                mazePanel.repaint();
            }

        } catch (ClassCastException c) {
            // Do nothing
        }
    }

    // Handling slider changes, updating values
    public void stateChanged(ChangeEvent e) {

        JSlider changedSlider = (JSlider)e.getSource();
        String currentSliderName = changedSlider.getName();

        if (currentSliderName == "Rows") {
            settingsPanel.setRows(changedSlider.getValue());
            settingsPanel.setRowsLbl("Rows: " + changedSlider.getValue());
        }
        if (currentSliderName == "Columns") {
            settingsPanel.setCols(changedSlider.getValue());
            settingsPanel.setColsLbl("Columns: " + changedSlider.getValue());
        }
    }
}

