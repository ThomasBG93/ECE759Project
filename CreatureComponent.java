import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.awt.geom.Point2D.Double;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import javax.swing.JComponent;

public class CreatureComponent extends JComponent
{
	
	private static final int SIZE = 1000000;
	private static final int COL = 1000;
	private static final int ROW = 1000;
	private static final int STEP = 2;
	
	public static int[] readFile()
	{
		//Scanner console = new Scanner(System.in);
		//System.out.print("Input file: ");
		//String inputFileName = console.next();
		//System.out.print("Size of row: ");
		//String rowS = console.next();
		int row = ROW;
		//System.out.print("Size of col: ");
		//String colS = console.next();
		int col = COL;
		int size = SIZE;
		String inputFileName = "movingMatrix.txt";
		File inputFile = new File(inputFileName);
		Scanner in = null;
		try {
			in = new Scanner(inputFile);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		System.out.println("All good reading file");
		int val = 0;
		int i = 0;
		int[] matrix = new int[size];
		
		for(i = 0; i < size; i++) {
			String line = in.nextLine();
			val = Integer.parseInt(line);
			matrix[i] = val;
		}
		
		
		
		in.close();
		return matrix;
	}
	
	public void paintComponent(Graphics g)
	{
		Graphics2D g2 = (Graphics2D) g;
		int[] arr = readFile();
		Creatures[] creats = new Creatures[SIZE];
		int i = 0, j=0;
		g2.setColor(Color.RED);
		
		for(i=0;i<SIZE;i++) {
			creats[i] = new Creatures();
		}
		
		for(i=0; i < COL; i++) {
			for(j=0; j < ROW; j++) {
				if(arr[i*ROW + j] == 1) {
					creats[i*ROW + j].draw(g2, j, i);
				}
			}
		}
		
	}
	
	
	
	
	

}
