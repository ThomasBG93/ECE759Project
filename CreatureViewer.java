import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class CreatureViewer {
	
	private static final int WIDTH = 1000;
	private static final int HEIGHT = 1000;
	
	public static void main(String[] args) {
		JFrame frame = new JFrame();
		frame.setSize(WIDTH,HEIGHT);
		frame.setTitle("Creatures");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setBackground(Color.black);
		
		CreatureComponent creature1 = new CreatureComponent();
		frame.add(creature1);

		frame.setVisible(true);
		
        try
        {
            BufferedImage image = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
            Graphics2D graphics2D = image.createGraphics();
            frame.paint(graphics2D);
            ImageIO.write(image,"png", new File("C:\\Users\\Brian.Brian\\Documents\\ece759\\project\\image.png"));
        }
        catch(Exception exception)
        {
            //code
        }
	}
	
}
