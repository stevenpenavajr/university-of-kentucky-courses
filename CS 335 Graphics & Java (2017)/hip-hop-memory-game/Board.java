/*
* Steven Penava
* Dr. Brent Seales
* CS 335: Program 0
* 09/20/2017
*
* Board Class
*/

// Imports
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

// Standalone board object
public class Board {

    // - HELPER VARIABLES -------------------------------------------------------------------------------------->
    private ClassLoader imageLoader = getClass().getClassLoader();
    private Card cards[];

    // - CONSTRUCTOR ------------------------------------------------------------------------------------------->
    public Board(int size, ActionListener AL) {
        cards = new Card[size];
        fillCardArray(cards, size);
    }

    // - MAINTENANCE FUNCTIONS --------------------------------------------------------------------------------->
    public void fillBoardWithCards(JPanel panel) {
        int[] indexes = new int[24];
        for (int i = 0; i < indexes.length; i++) {
            indexes[i] = i;
        }
        Random rnd = ThreadLocalRandom.current();
        for (int i = indexes.length - 1; i > 0; i--) {
            int index = rnd.nextInt(i + 1);
            int a = indexes[index];
            indexes[index] = indexes[i];
            indexes[i] = a;
        }
        for (int i = 0; i < indexes.length; i++) {
            panel.add(cards[indexes[i]]);
        }
    }

    private void fillCardArray(Card cards[], int size) {
        int imgIndex = 1;
        for (int i = 0; i < size; i += 2) {
            String frontPath = "assets/img" + imgIndex + ".jpg";
            ImageIcon img = new ImageIcon(imageLoader.getResource(frontPath));

            Card c1 = new Card(img);
            Card c2 = new Card(img);

            c1.setPairID(imgIndex);
            c2.setPairID(imgIndex);

            c1.setUniqueID(i+1); // unique IDs to handle re-clicking
            c2.setUniqueID(i*13);

            cards[i] = c1;
            cards[i + 1] = c2;
            imgIndex++;
        }
    }

    public void resetBoard() {
        for (Card c : cards) {
            c.setIcon(c.getTexture());
            c.setEnabled(true);
        }
        Collections.shuffle(Arrays.asList(cards));

    }

    // - GETTERS & SETTERS ------------------------------------------------------------------------------------->
    public Card[] getCards() { return cards; }
}
    // - END --------------------------------------------------------------------------------------------------->

