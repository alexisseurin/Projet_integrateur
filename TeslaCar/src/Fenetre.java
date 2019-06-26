import javax.swing.JFrame;

public class Fenetre extends JFrame {
	private InFenetre e = new InFenetre();
	public int point;

	public Fenetre(int x, int y, String a) {
		this.setTitle(a);
		this.setSize(x, y);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setContentPane(e);
		this.setVisible(true);
	}

	public void coo(String i) {
		switch (i) {
		case "4":
			e.x = 90;
			e.y = 90;
			break;
		case "3":
			e.x = 90;
			e.y = 200;
			break;
		case "2":
			e.x = 90;
			e.y = 340;
			break;
		case "1":
			e.x = 90;
			e.y = 510;
			break;
		case "5":
			e.x = 230;
			e.y = 90;
			break;

		case "6":
			e.x = 230;
			e.y = 200;
			break;

		case "7":
			e.x = 530;
			e.y = 200;
			break;

		case "8":
			e.x = 530;
			e.y = 90;
			break;

		case "9":
			e.x = 670;
			e.y = 90;
			break;

		case "10":
			e.x = 760;
			e.y = 90;
			break;

		case "11":
			e.x = 760;
			e.y = 340;
			break;

		case "12":
			e.x = 670;
			e.y = 340;
			break;

		case "13":
			e.x = 670;
			e.y = 420;
			break;

		case "14":
			e.x = 230;
			e.y = 420;
			break;

		case "15":
			e.x = 230;
			e.y = 510;
			break;

		case "16":
			e.x = 760;
			e.y = 510;
			break;

		}
	}
}
