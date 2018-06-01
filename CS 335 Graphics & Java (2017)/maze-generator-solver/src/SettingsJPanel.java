/*
* Steven Penava
* Dr. Brent Seales
* CS 335: Program 2
* 11/01/2017
*
* Settings panel
*/

// Imports
import javax.swing.*;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionListener;

// Settings panel
public class SettingsJPanel extends JPanel {

    // Initializations
    private JButton generateButton, solveButton, pauseButton, resetButton;
    private JLabel speedLbl, rowsLbl, colsLbl;
    private JSlider speedSlider, rowsSlider, colsSlider;
    private JCheckBox showGenCB, showSolverCB;
    private int rows;
    private int columns;

    // Constructor
    SettingsJPanel(ActionListener AL, ChangeListener CL) {

        // Initializing buttons
        generateButton = new JButton("Generate");
        solveButton = new JButton("Solve");
        pauseButton = new JButton("Pause/Resume");
        resetButton = new JButton("Reset");

        // Initializing sliders
        speedSlider = new JSlider(JSlider.HORIZONTAL, 5, 1000, 498);
        speedSlider.setName("Speed");
        rowsSlider = new JSlider(JSlider.HORIZONTAL, 10, 50, 30);
        rowsSlider.setName("Rows");
        colsSlider = new JSlider(JSlider.HORIZONTAL, 10, 50, 30);
        colsSlider.setName("Columns");

        // Initializing rows & columns
        rows = rowsSlider.getValue();
        columns = colsSlider.getValue();

        // Initializing labels
        rowsLbl = new JLabel("Rows: " + rowsSlider.getValue());
        colsLbl = new JLabel("Columns: " + colsSlider.getValue());
        speedLbl = new JLabel("Speed (fast to slow):");

        // Initializing checkboxes
        showGenCB = new JCheckBox("Show Generation");
        showSolverCB = new JCheckBox("Show Solver");
        setInitialConditions();

        // Action Listeners
        generateButton.addActionListener(AL);
        solveButton.addActionListener(AL);
        showGenCB.addActionListener(AL);
        showSolverCB.addActionListener(AL);
        pauseButton.addActionListener(AL);
        resetButton.addActionListener(AL);

        // Change Listeners
        rowsSlider.addChangeListener(CL);
        colsSlider.addChangeListener(CL);

        // Adding all settings elements
        super.add(generateButton);
        super.add(showGenCB);
        super.add(solveButton);
        super.add(showSolverCB);
        super.add(speedLbl);
        super.add(speedSlider);
        super.add(rowsLbl);
        super.add(rowsSlider);
        super.add(colsLbl);
        super.add(colsSlider);
        super.add(pauseButton);
        super.add(resetButton);

        // Panel maintenance
        super.setPreferredSize(new Dimension(200,500));
        super.setBackground(Color.CYAN);
        super.setLayout(new GridLayout(12, 1));
    }

    // Centering labels & check boxes, designing sliders
    public void setInitialConditions() {
        speedLbl.setHorizontalAlignment(0);
        rowsLbl.setHorizontalAlignment(0);
        colsLbl.setHorizontalAlignment(0);
        showGenCB.setHorizontalAlignment(0);
        showSolverCB.setHorizontalAlignment(0);
        setSliderSettings(colsSlider);
        setSliderSettings(rowsSlider);
        pauseButton.setEnabled(false);
    }

    // Resetting buttons and settings row/col values
    public void resetInterface() {
        rowsSlider.setValue(30);
        colsSlider.setValue(30);
        rows = rowsSlider.getValue();
        columns = colsSlider.getValue();
        rowsLbl.setText("Rows : " + rows);
        colsLbl.setText("Columns: " + columns);
        speedSlider.setValue(498);
        pauseButton.setEnabled(false);
        showGenCB.setEnabled(true);
        generateButton.setEnabled(true);
    }

    // Putting ticks on slider
    public void setSliderSettings(JSlider slider) {
        slider.setMinorTickSpacing(1);
        slider.setMajorTickSpacing(10);
        slider.setPaintTicks(true);
        slider.setPaintLabels(true);
    }

    // Maintenance: rows
    public int getRows() {return rows;}
    public void setRows(int r) { rows = r; }
    public void setRowsLbl(String r) { rowsLbl.setText(r); }

    // Maintenance: columns
    public int getCols() {return columns;}
    public void setCols(int c) { columns = c; }
    public void setColsLbl(String r) { colsLbl.setText(r); }

    // Maintenance: checkbox values & slider
    public boolean getShowGenCBValue() { return showGenCB.isSelected(); }
    public boolean getSolveCBValue() {
        return showSolverCB.isSelected();
    }
    public JSlider getSpeedSlider() {
        return speedSlider;
    }

    // Maintenance: enabling/disabling things
    public void enableSolveFunctions() {
        showSolverCB.setEnabled(true);
        solveButton.setEnabled(true);
    }
    public void disableSolveFunctions() {
        showSolverCB.setEnabled(false);
        solveButton.setEnabled(false);
    }
    public void enablePauseFunction() {
        pauseButton.setEnabled(true);
    }
    public void disableGenFunctions() {
        generateButton.setEnabled(false);
        showGenCB.setEnabled(false);
    }

}