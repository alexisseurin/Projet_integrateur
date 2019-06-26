import java.awt.Graphics;
import java.awt.Image;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

public class InFenetre extends JPanel {
	public int x = 50;
	public int y = 50;
	public int c = 30;

	public void paintComponent(Graphics g) {
		try {
			Image img = ImageIO.read(new File("map.png"));
			g.drawImage(img, 0, 0, this);
			g.drawImage(img, 0, 0, this);
			g.fillRect(x, y, c, c);
		} catch (IOException e) {
			e.printStackTrace();
		}
	};
}
