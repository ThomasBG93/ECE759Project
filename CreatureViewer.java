import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class CreatureViewer {
	
    // private static final int WIDTH = 100;
    // private static final int HEIGHT = 100;
    
    public static void main(String[] args) 
    {
    	int len = 0;

		try {
            // Parse the string argument into an integer value.
            len = Integer.parseInt(args[0]);
        }
        catch (ArrayIndexOutOfBoundsException wrongindex)
        {
        	System.out.println("Usage: java CreatureViewer size");
            System.exit(1);

        }
        catch (NumberFormatException nfe) 
        {
            // The first argument isn't a valid integer.  Print
            // an error message, then exit with an error code.
            System.out.println("Usage: size should be a integer");
            System.exit(1);
        }
	    

		JFrame frame = new JFrame();
		int fameSize = 0;

		if(len<=100)
			fameSize = len*11;
		else if(len<=500)
			fameSize = len*6;
		else
			fameSize = len;

		frame.setSize(fameSize,fameSize);
		frame.setTitle("Creatures");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setBackground(Color.black);
		CreatureComponent creature1 = new CreatureComponent(len);
		frame.add(creature1);
		
		frame.setVisible(true);
		
        try
	    {
			BufferedImage image = new BufferedImage(fameSize, fameSize, BufferedImage.TYPE_INT_RGB);
			Graphics2D graphics2D = image.createGraphics();
			//graphics2D.scale(10.0, 10.0);
			frame.paint(graphics2D);
		//            ImageIO.write(image,"png", new File("C:\\Users\\Brian.Brian\\Documents\\ece759\\project\\image.png"));
	    }
        	catch(Exception exception)
	    {
		//code
	    }
        
        //refresh
        boolean a = true;
        while(a)
	    {
			frame.validate();
			frame.repaint();
	    }
	        
	}
    
}
