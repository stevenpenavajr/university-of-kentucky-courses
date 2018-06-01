/*
* Steven Penava
* Dr. Brent Seales
* CS 335: Program 0
* 09/20/2017
*
* MemoryGame Class
*/

// Imports
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import javax.swing.*;

// Subclass of JFrame; uses ActionListener interface
public class MemoryGame extends JFrame implements ActionListener, WindowListener {

    // - HELPER VARIABLES -------------------------------------------------------------------------------------->
    private JPanel labelPanel, boardPanel;
    private Board gameBoard;
    ArrayList<Card> clickedCards = new ArrayList<Card>(); // for previous/current card access
    Container contentPane = getContentPane();

    // Variables for stat tracking
    boolean match = false;
    int numClicks = 0;
    int timerCtr = 0;
    int timeS = 0;
    int timeDs = 0;
    int errorCount = 0;
    int numMatches = 0;
    int numGuesses = 0;
    Timer gameTimer;
    String[] userData = new String[3];

    // Program navigation button creation
    JButton restart = new JButton("Restart");
    JButton quit = new JButton("Quit");
    JLabel errors = new JLabel("Errors: 0");
    JLabel timeDisplay = new JLabel("Time: 0.0");
    JButton start = new JButton("Start");
    JLabel guesses = new JLabel("Guesses: 0");
    JLabel matches = new JLabel("Matches: 0");


    // - CONSTRUCTOR ------------------------------------------------------------------------------------------->
    public MemoryGame() {
        super("Rap Album Memory Game");

        // Allocating JPanels
        labelPanel = new JPanel();
        boardPanel = new JPanel();

        // Handling game panel
        gameBoard = new Board(24, this);
        boardPanel.setLayout(new GridLayout(4,6,2,0));
        gameBoard.fillBoardWithCards(boardPanel);
        addCardActionListeners();
        super.addWindowListener(this);

        // Handling label panel
        labelPanel.setLayout(new GridLayout(1, 4, 2, 2));
        labelPanel.add(start);
        labelPanel.add(restart);
        labelPanel.add(quit);
        labelPanel.add(errors);
        labelPanel.add(timeDisplay);
        labelPanel.add(guesses);
        labelPanel.add(matches);

        // Button enabled/disabled configuration
        toggleButtons("disable");
        start.setEnabled(true);

        // Event handling for restart
        restart.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gameBoard.resetBoard();
                boardPanel.removeAll();
                for (JButton button: gameBoard.getCards()) {
                    boardPanel.add(button);
                }
                gameBoard.resetBoard();
                clickedCards.clear();
                boardPanel.revalidate();
                boardPanel.repaint();
                timeS = 0;
                timeDs = 0;
                errorCount = 0;
                numGuesses = 0;
                gameTimer.start();
                errors.setText("Errors: " + errorCount);
                guesses.setText("Guesses: " + numGuesses);
                // matches reset happens in game timer action listener
            }
        });

        // Event handling for quit
        quit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                showExitDialog();
            }
        });

        // Event handling for start
        start.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                toggleButtons("enable");
                start.setEnabled(false);

                gameTimer = new Timer(100, new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        timeS++;
                        timeDs++;
                        timeDisplay.setText("Time: " + timeS/10 + "." + timeDs);
                        if (timeDs == 9) {
                            timeDs = 0;
                        }
                        if (numMatches == 12) {
                            gameTimer.stop();
                            String errorsString = String.valueOf(errorCount);
                            Object[] options = {"OK"};
                            int n = JOptionPane.showOptionDialog(null,
                                    "You finished with " + errorCount + " error(s) and " + numGuesses + " guesses " + " in " + timeS/10 + "." + timeDs + " seconds. Click restart to play again." ,"You won!",
                                    JOptionPane.PLAIN_MESSAGE,
                                    JOptionPane.QUESTION_MESSAGE,
                                    null,
                                    options,
                                    options[0]);
                            errorCount = 0;
                            numMatches = 0;
                            numGuesses = 0;
                            errors.setText("Errors: " + errorCount);
                            guesses.setText("Guesses: " + numGuesses);
                            matches.setText("Matches: " + numMatches);
                            timeDisplay.setText("Time: 0.0");
                        }
                    }
                });
                gameTimer.start();
            }
        });

        // Adding objects to the content pane for use
        contentPane.add(labelPanel, BorderLayout.NORTH);
        contentPane.add(boardPanel, BorderLayout.SOUTH);

        // Window maintenance
        setSize(1000, 675);
        super.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE); // prepare for exit dialog
        super.setLocationRelativeTo(null);
        setVisible(true);
    }

    // - HELPER FUNCTIONS -------------------------------------------------------------------------------------->

    // Giving Memory Game the ability to detect card clicks
    private void addCardActionListeners() {
        for (Card c : gameBoard.getCards()) {
            c.addActionListener(this);
        }
    }

    // Display exit dialog before quitting
    private void showExitDialog() {
        String options[] = {"Yes","No"};
        int PromptResult = JOptionPane.showOptionDialog(null,"Are you sure you want to quit the game?","Exit Memory Game",JOptionPane.DEFAULT_OPTION,JOptionPane.WARNING_MESSAGE,null,options,options[1]);
        if(PromptResult==JOptionPane.YES_OPTION) {
            System.exit(0);
        }
    }

    // Initial load button toggling
    private void toggleButtons(String mode) {
        if (mode == "enable") {
            for (Card c : gameBoard.getCards()) {
                c.setEnabled(true);
            }
            restart.setEnabled(true);
        }
        else if (mode == "disable") {
            for (Card c : gameBoard.getCards()) {
                c.setEnabled(false);

            }
            restart.setEnabled(false);
            start.setEnabled(false);
        }
    }

    // - GAME PLAY --------------------------------------------------------------------------------------------->
    public void actionPerformed(ActionEvent e) {
        Card currCard = (Card)e.getSource();
        currCard.setIcon(currCard.getPicture());
        numClicks += 1;
        timerCtr = 0;

        clickedCards.add(currCard);

        if (numClicks % 2 == 0) {

            numGuesses++;
            guesses.setText("Guesses: " + numGuesses);

            Card mostRecent = clickedCards.get(clickedCards.size() - 1);
            Card secondToLast = clickedCards.get(clickedCards.size() - 2);

            if (mostRecent.getPairID() == secondToLast.getPairID()) {
                if (mostRecent.getUniqueID() != secondToLast.getUniqueID()) {
                    numMatches++;
                    matches.setText("Matches: " + numMatches);
                    mostRecent.setEnabled(false);
                    secondToLast.setEnabled(false);
                }
                else {
                    mostRecent.setIcon(mostRecent.getTexture());
                    secondToLast.setIcon(secondToLast.getTexture());
                    errorCount++;
                    errors.setText("Errors: " + errorCount);
                }
            }
            else {
                mostRecent.setEnabled(false);
                secondToLast.setEnabled(false);
                errorCount++;
                errors.setText("Errors: " + errorCount);
                Timer t = new Timer(1000, new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        timerCtr += 1;
                        if (timerCtr == 1) {
                            mostRecent.setIcon(mostRecent.getTexture());
                            secondToLast.setIcon(secondToLast.getTexture());
                            mostRecent.setEnabled(true);
                            secondToLast.setEnabled(true);
                        }
                    }
                });
                t.start();
                t.setRepeats(false);
            }
        }
    }

    // - DRIVER ------------------------------------------------------------------------------------------------>
    public static void main(String args[]) {
        MemoryGame Game = new MemoryGame();
    }

    // - WINDOW LISTENER FUNCTIONS ----------------------------------------------------------------------------->
    @Override
    public void windowClosed(WindowEvent e) { }

    @Override
    public void windowOpened(WindowEvent e) { }

    @Override
    public void windowClosing(WindowEvent e) {
       showExitDialog();
    } // window close event

    @Override
    public void windowIconified(WindowEvent e) { }

    @Override
    public void windowDeiconified(WindowEvent e) { }

    @Override
    public void windowActivated(WindowEvent e) { }

    @Override
    public void windowDeactivated(WindowEvent e) { }
}
    // - END --------------------------------------------------------------------------------------------------->
