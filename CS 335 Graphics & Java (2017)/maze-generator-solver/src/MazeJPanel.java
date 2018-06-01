/*
* Steven Penava
* Dr. Brent Seales
* CS 335: Program 2
* 11/01/2017
*
* Maze Panel (holds grid)
*/

// Imports
import javax.swing.*;
import javax.swing.Timer;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;

// The maze itself
public class MazeJPanel extends JPanel {

    // Initializations
    private int rows, columns;
    private Cell[][] cellArray;
    private boolean[][] visitedArray;
    private boolean[][] visitedArrSolver;
    private Timer mazeTimer;
    private Timer solveTimer;
    private boolean isGenerating, isSolving;
    private double visitedCount;

    // Constructor
    MazeJPanel(int rows, int columns) {
        this.rows = rows;
        this.columns = columns;
        cellArray = new Cell[rows][columns];
        visitedArray = new boolean[rows][columns];
        mazeTimer = new Timer(100, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // DUMMY TIMER
            }
        }); // dummy timer to avoid null prt exc.
        solveTimer = new Timer(100, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // DUMMY TIMER
            }
        }); // dummy timer to avoid null ptr exc.
        super.setLayout(new GridLayout(rows, columns));
        super.setBackground(Color.BLACK);
    }

    // Grid: creating cells
    public void fillCellArray() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                Cell c = new Cell();
                c.row = i;
                c.col = j;
                cellArray[i][j] = c;
            }
        }
    }

    // Grid: filling it with created cells
    public void placeCellsOnGrid() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                super.add(cellArray[i][j]);
            }
        }
    }

    // Grid: resizing cell array
    public void resetArraySize() {
        cellArray = new Cell[rows][columns];
    }

    // Grid: removing cells from grid
    public void removeCellsFromGrid() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                super.remove(cellArray[i][j]);
            }
        }
        super.invalidate();
    }

    // Grid: resetting grid layout size
    public void resetGridSize() {
        super.setLayout(new GridLayout(rows, columns));
    }

    // Mazegen: DFS maze gen algorithm
    public void generateMaze(boolean animateEnabled, int speed, JLabel visitedLabel) {

        LinkedList<Cell> cellQueue = new LinkedList<>();
        Cell selectedCell = cellArray[0][0];
        Random rand = new Random();
        boolean keepGoing = true;
        visitedCount = 0;

        // Animated version
        if (animateEnabled) {
            isGenerating = true;
            ActionListener timerListener = new ActionListener() {
                LinkedList<Cell> cellQueue = new LinkedList<>();
                Cell selectedCell = cellArray[0][0];
                boolean keepGoing = true;
                @Override
                public void actionPerformed(ActionEvent e) {
                    if (keepGoing) {
                        visitedArray[selectedCell.row][selectedCell.col] = true;

                        visitedCount++;
                        visitedLabel.setText("Visited: " + Math.round((visitedCount / (rows*columns)) * 100)  + "% of cells.");

                        cellQueue.push(selectedCell);

                        selectedCell.setBackground(Color.blue);
                        LinkedList<Cell> possibleNeighbors = getPossibleNeighbors(selectedCell);

                        if (possibleNeighbors.isEmpty()) {
                            while (!cellQueue.isEmpty()) {
                                Cell tempCell = cellQueue.pop();
                                possibleNeighbors = getPossibleNeighbors(tempCell);
                                if (!possibleNeighbors.isEmpty()) {
                                    selectedCell = tempCell;
                                    break;
                                }
                                if (tempCell == null) {
                                    keepGoing = false;
                                }
                            }
                        }
                        if (!possibleNeighbors.isEmpty()) {
                            int randIndex = rand.nextInt(possibleNeighbors.size());
                            Cell randNeighbor = possibleNeighbors.get(randIndex);
                            breakWall(selectedCell, randNeighbor);
                            selectedCell = randNeighbor;
                        } else {
                            isGenerating = false;
                            keepGoing = false;
                        }
                    }
                    else {
                        mazeTimer.stop();
                    }
                }
            };
            mazeTimer = new Timer(speed, timerListener);
            mazeTimer.start();

        // Non-animated version
        } else {
            isGenerating = false;
            while (keepGoing) {
                visitedArray[selectedCell.row][selectedCell.col] = true;

                visitedCount++;
                visitedLabel.setText("Visited: " + Math.round((visitedCount / (rows*columns)) * 100) +"% of cells.");

                cellQueue.push(selectedCell);
                selectedCell.setBackground(Color.blue);
                LinkedList<Cell> possibleNeighbors = getPossibleNeighbors(selectedCell);

                if (possibleNeighbors.isEmpty()) {
                    while (!cellQueue.isEmpty()) {
                        Cell tempCell = cellQueue.pop();
                        possibleNeighbors = getPossibleNeighbors(tempCell);
                        if (!possibleNeighbors.isEmpty()) {
                            selectedCell = tempCell;
                            break;
                        }
                        if (tempCell == null) {
                            keepGoing = false;
                        }
                    }
                }
                if (!possibleNeighbors.isEmpty()) {
                    int randIndex = rand.nextInt(possibleNeighbors.size());
                    Cell randNeighbor = possibleNeighbors.get(randIndex);
                    breakWall(selectedCell, randNeighbor);
                    selectedCell = randNeighbor;
                } else {
                    keepGoing = false;
                }
            }
        }
    }

    // Mazegen: gets possible random neighbors of current cell
    public LinkedList<Cell> getPossibleNeighbors(Cell c) {
        LinkedList<Cell> neighbors = new LinkedList<>();

        // left
        if ( ((c.col - 1) < columns && (c.col - 1 >= 0)) && (c.row < rows && c.row >= 0 ) ){
            if (visitedArray[c.row][c.col - 1] == false) {
                neighbors.add(cellArray[c.row][c.col - 1]);
            }
        }

        // right
        if ( ((c.col + 1) < columns && (c.col + 1 >= 0)) && (c.row < rows && c.row >= 0 ) ){
            if (visitedArray[c.row][c.col+1] == false) {
                neighbors.add(cellArray[c.row][c.col + 1]);
            }
        }

        // bottom
        if ( ((c.col) < columns && (c.col >= 0)) && (c.row+1 < rows && c.row + 1 >= 0 ) ){
            if (visitedArray[c.row+1][c.col] == false) {
                neighbors.add(cellArray[c.row + 1][c.col]);
            }
        }

        // top
        if ( ((c.col) < columns && (c.col >= 0)) && (c.row - 1 < rows && c.row - 1 >= 0 ) ){
            if (visitedArray[c.row-1][c.col] == false) {
                neighbors.add(cellArray[c.row -1 ][c.col]);
            }
        }
        return neighbors;
    }

    // Mazegen: break wall
    public void breakWall(Cell selected, Cell neighbor) {

        // break the "left" wall of the selected cell
        if (selected.row == neighbor.row && neighbor.col == selected.col - 1) {

            int[] selectedEdges = selected.edges;
            int[] neighborEdges = neighbor.edges;

            selected.setLeft(0);
            neighbor.setRight(0);

            selected.setBorder(BorderFactory.createMatteBorder(selectedEdges[0], selectedEdges[1], selectedEdges[2], selectedEdges[3], Color.WHITE));
            neighbor.setBorder(BorderFactory.createMatteBorder(neighborEdges[0], neighborEdges[1], neighborEdges[2], neighborEdges[3], Color.WHITE));

        }

        // "right"
        if (selected.row == neighbor.row && neighbor.col == selected.col + 1) {
            int[] selectedEdges = selected.edges;
            int[] neighborEdges = neighbor.edges;

            selected.setRight(0);
            neighbor.setLeft(0);

            selected.setBorder(BorderFactory.createMatteBorder(selectedEdges[0], selectedEdges[1], selectedEdges[2], selectedEdges[3], Color.WHITE));
            neighbor.setBorder(BorderFactory.createMatteBorder(neighborEdges[0], neighborEdges[1], neighborEdges[2], neighborEdges[3], Color.WHITE));

        }

        // "top"
        if (neighbor.row == selected.row - 1 && neighbor.col == selected.col) {
            int[] selectedEdges = selected.edges;
            int[] neighborEdges = neighbor.edges;

            selected.setTop(0);
            neighbor.setBottom(0);

            selected.setBorder(BorderFactory.createMatteBorder(selectedEdges[0], selectedEdges[1], selectedEdges[2], selectedEdges[3], Color.WHITE));
            neighbor.setBorder(BorderFactory.createMatteBorder(neighborEdges[0], neighborEdges[1], neighborEdges[2], neighborEdges[3], Color.WHITE));

        }

        // "bottom"
        if (neighbor.row == selected.row + 1 && neighbor.col == selected.col) {
            int[] selectedEdges = selected.edges;
            int[] neighborEdges = neighbor.edges;
            selected.setBottom(0);
            neighbor.setTop(0);

            selected.setBorder(BorderFactory.createMatteBorder(selectedEdges[0], selectedEdges[1], selectedEdges[2], selectedEdges[3], Color.WHITE));
            neighbor.setBorder(BorderFactory.createMatteBorder(neighborEdges[0], neighborEdges[1], neighborEdges[2], neighborEdges[3], Color.WHITE));

        }
    }

    // Solving: Solving the maze
    public void solveMaze(boolean solveEnabled, int speed, JLabel visitedLabel) {
        visitedCount = 0;

        // Animated version
        if (solveEnabled) {
            Stack<Cell> cellQueue = new Stack<>();
            visitedArrSolver = new boolean[rows][columns];

            visitedCount++;
            visitedLabel.setText("Visited: " + Math.round((visitedCount / (rows*columns)) * 100) + " % of cells.");

            isSolving = true;
            ActionListener solveListener = new ActionListener() {
                Cell selectedCell = cellArray[0][0];
                Cell endCell = cellArray[rows-1][columns-1];

                @Override
                public void actionPerformed(ActionEvent e) {

                    if (selectedCell != endCell) {
                        visitedArrSolver[selectedCell.row][selectedCell.col] = true;

                        visitedCount++;
                        visitedLabel.setText("Visited: " + Math.round((visitedCount / (rows*columns)) * 100) + "% of cells.");

                        cellQueue.push(selectedCell);
                        LinkedList<Cell> accessibleNeighbors = getAccessibleNeighbors(selectedCell);

                        if (accessibleNeighbors.isEmpty()) {
                            while (!cellQueue.isEmpty()) {
                                Cell tempCell = cellQueue.pop();
                                tempCell.setBackground(Color.gray);
                                accessibleNeighbors = getAccessibleNeighbors(tempCell);
                                if (!accessibleNeighbors.isEmpty()) {
                                    selectedCell = tempCell;
                                    break;
                                }
                            }
                        }
                        Cell randNeighbor = accessibleNeighbors.get(0);
                        selectedCell.setBackground(Color.orange);
                        selectedCell = randNeighbor;
                    } else {
                        isSolving = false;
                        solveTimer.stop();
                    }
                }
            };
            solveTimer = new Timer(speed, solveListener);
            solveTimer.start();
        }

        // Non-animated version
        else {
            isSolving = false;
            Stack<Cell> cellQueue = new Stack<>();
            Cell selectedCell = cellArray[0][0];
            Cell endCell = cellArray[rows-1][columns-1];
            boolean keepGoing = true;
            visitedArrSolver = new boolean[rows][columns];
            selectedCell.setBackground(Color.orange);

            while (selectedCell != endCell) {
                visitedArrSolver[selectedCell.row][selectedCell.col] = true;
                visitedCount++;
                visitedLabel.setText("Visited: " + Math.round((visitedCount / (rows*columns)) * 100) + "% of cells.");

                cellQueue.push(selectedCell);
                LinkedList<Cell> accessibleNeighbors = getAccessibleNeighbors(selectedCell);

                if (accessibleNeighbors.isEmpty()) {
                    while (!cellQueue.isEmpty()) {
                        Cell tempCell = cellQueue.pop();
                        tempCell.setBackground(Color.gray);
                        accessibleNeighbors = getAccessibleNeighbors(tempCell);
                        if (!accessibleNeighbors.isEmpty()) {
                            selectedCell = tempCell;
                            break;
                        }

                    }
                }

                Cell randNeighbor = accessibleNeighbors.get(0);
                selectedCell.setBackground(Color.orange);
                selectedCell = randNeighbor;
            }
            cellArray[rows-1][columns-1].setBackground(Color.orange);
        }
    }

    // Solving: get neighbors without wall
    public LinkedList<Cell> getAccessibleNeighbors(Cell c) {
        LinkedList<Cell> neighbors = new LinkedList<>();

        // right
        if ( ((c.col + 1) < columns && (c.col + 1 >= 0)) && (c.row < rows && c.row >= 0 ) ){
            if (visitedArrSolver[c.row][c.col+1] == false) {
                if (c.edges[3] == 0) {
                    neighbors.add(cellArray[c.row][c.col + 1]);
                }
            }
        }

        // bottom
        if ( ((c.col) < columns && (c.col >= 0)) && (c.row+1 < rows && c.row + 1 >= 0 ) ){
            if (visitedArrSolver[c.row + 1][c.col] == false) {
                if (c.edges[2] == 0) {
                    neighbors.add(cellArray[c.row + 1][c.col]);
                }
            }
        }

        // left
        if ( ((c.col - 1) < columns && (c.col - 1 >= 0)) && (c.row < rows && c.row >= 0 ) ){
            if (visitedArrSolver[c.row][c.col - 1] == false) {
                if (c.edges[1] == 0) {
                    neighbors.add(cellArray[c.row][c.col - 1]);
                }
            }
        }

        // top
        if ( ((c.col) < columns && (c.col >= 0)) && (c.row - 1 < rows && c.row - 1 >= 0 ) ){
            if (visitedArrSolver[c.row - 1][c.col] == false) {
                if (c.edges[0] == 0) {
                    neighbors.add(cellArray[c.row - 1][c.col]);
                }
            }
        }





        return neighbors;
    }

    // Maintenance: setting row and column sizes for grid
    public void setRows(int r) {
        rows = r;
        cellArray = new Cell[rows][columns];
        visitedArray = new boolean[rows][columns];
    }
    public void setColumns(int c) {
        columns = c;
        cellArray = new Cell[rows][columns];
        visitedArray = new boolean[rows][columns];
    }

    // Maintenance: maze timer functions
    public void stopMazeTimer() { mazeTimer.stop(); }
    public void startMazeTimer() { mazeTimer.start(); }
    public boolean mazeTimerRunning() { return mazeTimer.isRunning(); }

    // Maintenance: solve timer functions
    public void stopSolveTimer() { solveTimer.stop(); }
    public void startSolveTimer() { solveTimer.start(); }
    public boolean solveTimerRunning() { return solveTimer.isRunning(); }

    // Maintenance: solve/gen status
    public boolean isGenerating() { return isGenerating; }
    public boolean isSolving() { return isSolving; }
    public void setSolveFalse() { isSolving = false; };
}
