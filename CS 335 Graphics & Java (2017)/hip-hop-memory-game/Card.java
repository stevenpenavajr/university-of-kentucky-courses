/*
* Steven Penava
* Dr. Brent Seales
* CS 335: Program 0
* 09/20/2017
*
* Card Class
*/

// Imports
import javax.swing.*;

// Extends JButton because a card is technically a button
public class Card extends JButton {

    // - HELPER VARIABLES -------------------------------------------------------------------------------------->
    private ClassLoader imageLoader = getClass().getClassLoader();
    private Icon texture;
    private Icon picture;
    private int id;
    private int uniqueID;
    ImageIcon textureImageIcon = new ImageIcon(imageLoader.getResource("assets/Back1.jpg"));  // Icon that hides real images

    // - CONSTRUCTORS ------------------------------------------------------------------------------------------>
    public Card() { super(); }

    public Card(ImageIcon hiddenPicture) {
        super();
        texture = textureImageIcon;
        super.setIcon(texture);
        picture = hiddenPicture;
    }

    // - GETTERS & SETTERS ------------------------------------------------------------------------------------->
    public int getPairID() { return id; }
    public void setPairID(int i) { id = i; }

    public void setUniqueID(int i) { uniqueID = i; }
    public int getUniqueID() { return uniqueID; }

    public Icon getPicture() { return picture; }
    public Icon getTexture() { return texture; }
}
    // - END --------------------------------------------------------------------------------------------------->

