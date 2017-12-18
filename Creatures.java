
import java.awt.Graphics2D;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;


public class Creatures {
	public void draw(Graphics2D g2, int x, int y)
	{
		Point2D.Double pt = new Point2D.Double(x+1, y+1);
		Line2D.Double ln = new Line2D.Double(pt, pt);
		
		g2.draw(ln);
	}
}
