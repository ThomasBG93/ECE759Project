import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class CreatureViewer {
	
    private static final int WIDTH = 100;
    private static final int HEIGHT = 100;
    
    public static void main(String[] args) {
	JFrame frame = new JFrame();
	frame.setSize(WIDTH*11,HEIGHT*11);
	frame.setTitle("Creatures");
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.getContentPane().setBackground(Color.black);
	
	CreatureComponent creature1 = new CreatureComponent();
	frame.add(creature1);
	
	frame.setVisible(true);
	
        try
	    {
		BufferedImage image = new BufferedImage(WIDTH*11, HEIGHT*11, BufferedImage.TYPE_INT_RGB);
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
		//try {
		//    Thread.sleep(millis);
		//} catch (InterruptedException e) {
		    // TODO Auto-generated catch block
		//    e.printStackTrace();
		//}
		frame.validate();
		frame.repaint();
	    }
        
    }
    
}
