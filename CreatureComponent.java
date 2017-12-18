import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.awt.geom.Point2D.Double;
//import java.io.File;
//import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.*;

import javax.swing.JComponent;

public class CreatureComponent extends JComponent
{
	
	private static final int SIZE = 10000;
	private static final int COL = 100;
	private static final int ROW = 100;
	//private static final int STEP = 2;
	
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
			//e.printStackTrace();
			System.out.println("GRAPH FILE: " + inputFileName + 
					" was not found.");
			System.exit(1);
		}
		System.out.println("All good reading file");
		int val = 0;
		int i = 0;
		int[] matrix = new int[size];
		byte[] buffer = new byte[4];
		int byteread;
		System.out.println("read is: ");
		try (
			InputStream inputStream = new FileInputStream(inputFileName);
		     ) {

			for(i = 0; i < size; i++) {

				inputStream.read(buffer);

				// if(i < 10)
				// 	System.out.println(buffer[0]+" " +buffer[1] + " " + buffer[2]+" " +buffer[3]); 
				//byteread = inputStream.read();

				//if(buffer[1] == 49)
					matrix[i] = buffer[0];
				//if(buffer[3] == 49)
				//	matrix[2*i + 1] = 1;
				// System.out.println("finish one set"); 
				
			}

			for(i = 0; i<16; i++)
			{
				System.out.printf(" " + matrix[i]);
			}
			// System.out.printf(" \n");
			// for(i = 16; i<32; i++)
			// {
			// 	System.out.printf(" " + matrix[i]);
			// }
			// System.out.printf(" \n");
			// for(i = 32; i<48; i++)
			// {
			// 	System.out.printf(" " + matrix[i]);
			// }
			// System.out.printf(" \n");
			// for(i = 48; i<64; i++)
			// {
			// 	System.out.printf(" " + matrix[i]);
			// }
		




		 //    while ((inputStream.read(buffer)) != -1) {
			// System.out.println((int)buffer[0]+" " +(int)buffer[1] + " " + (int)buffer[2]+" " +(int)buffer[3]); 

			// byteread = inputStream.read();
		    // }

		} catch (IOException ex) {
		    ex.printStackTrace();
		}









		// for(i = 0; i < size; i++) {
		// 	String line = in.nextLine();
		// 	byteRead = inputStream.read();
		// 	System.out.println(byteRead); 
		// 	val = Integer.parseInt(line);
		// 	matrix[i] = val;
		// 	if(i<10)
		// 	{
		// 		System.out.printf(" %d", matrix[i]);
		// 	}
		// }
		System.out.printf(" \n");
		
		
		
		in.close();
		return matrix;
	}
	
	public void paintComponent(Graphics g)
	{
		Graphics2D g2 = (Graphics2D) g;
		
		int[] arr = readFile();
		Creatures[] creats = new Creatures[SIZE];
		int i = 0, j=0;
		//g2.setColor(Color.BLUE);
		
		g2.scale(10.0, 10.0);

		//Color myColor = new Color(0,255,0);
		
		for(i=0;i<SIZE;i++) {
			creats[i] = new Creatures();
		}	
		int cnt = 0;
		for(i=0; i < COL; i++) {
			for(j=0; j < ROW; j++) {
				if(arr[i*ROW + j] >= 1) {
					cnt++;
					Color myColor = new Color( (arr[i*ROW + j]) * 2,0, (127-arr[i*ROW + j])* 2 );
					g2.setColor(myColor);
					creats[i*ROW + j].draw(g2, j, i);
				}
			}
		}
		System.out.println(cnt);
		
	}
	
	
	
	
	

}
