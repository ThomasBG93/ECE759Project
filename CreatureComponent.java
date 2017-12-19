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
	
	//private static final int SIZE = 10000;
	//private static final int COL = 100;
	//private static final int STEP = 2;
	private int len;
	private int size;

	public CreatureComponent(int length)
	{
		this.len = length;
		this.size = length*length;
	}

	public static int[] readFile(int sizer)
	{
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
		// System.out.println("All good reading file");
		int val = 0;
		int i = 0;
		int[] matrix = new int[sizer];
		byte[] buffer = new byte[4];
		int byteread;
		System.out.println(sizer + " read is: ");

		try (
			//open the file as required
			InputStream inputStream = new FileInputStream(inputFileName);
		     ) 
		{

			//read 4 bytes at a time, first byte is enough for us, range 00-ff
			for(i = 0; i < sizer; i++) {
				inputStream.read(buffer);
				matrix[i] = buffer[0];			
			}

			// for(i = 0; i<16; i++)
			// {
			// 	System.out.printf(" " + matrix[i]);
			// }

		} catch (IOException ex) {
		    ex.printStackTrace();
		}

		// System.out.printf(" \n");
		
			
		in.close();
		return matrix;
	}
	
	public void paintComponent(Graphics g)
	{
		Graphics2D g2 = (Graphics2D) g;
		
		int[] arr = readFile(size);
		//read matrices from file
		Creatures[] creats = new Creatures[size];
		int i = 0, j=0;
		//g2.setColor(Color.BLUE);
		int scaleSize= 0 ;

		if(len<=100)
			scaleSize = 11;
		else if(len<=500)
			scaleSize = 6;
		else
			scaleSize = 1;

		g2.scale(scaleSize, scaleSize);

		//Color myColor = new Color(0,255,0);
		
		for(i=0;i<size;i++) {
			creats[i] = new Creatures();
		}	
		//int cnt = 0;

		//draw out each point based on its life time, red is max life, 
		//blue is lowest life, but still alive
		for(i=0; i < len; i++) {
			for(j=0; j < len; j++) {
				if(arr[i*len + j] >= 1) {
					//cnt++;
					Color myColor = new Color( (arr[i*len + j]) * 2,0, (127-arr[i*len + j])* 2 );
					g2.setColor(myColor);
					creats[i*len + j].draw(g2, j, i);
				}
			}
		}
		//System.out.println(cnt);
		
	}
	
	
	
	
	

}
