import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

public class SerialTest implements SerialPortEventListener {

	SerialPort serialPort;
	/** The port we’re normally going to use. */
	private static final String PORT_NAMES[] = { "/dev/tty.usbserial-A9007UX1 ", // Mac OS X

			"COM7", // Windows
	};

	private BufferedReader input;
	private OutputStream output;
	private static final int TIME_OUT = 2000;
	private static final int DATA_RATE = 9600;

	public void initialize() {
		CommPortIdentifier portId = null;
		Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

//First, Find an instance of serial port as set in PORT_NAMES.
		while (portEnum.hasMoreElements()) {
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
			for (String portName : PORT_NAMES) {
				if (currPortId.getName().equals(portName)) {
					portId = currPortId;
					break;
				}
			}
		}
		if (portId == null) {
			System.out.println(" Could not find COM port. ");
			return;
		}

		try {
			serialPort = (SerialPort) portId.open(this.getClass().getName(), TIME_OUT);
			serialPort.setSerialPortParams(DATA_RATE, SerialPort.DATABITS_8, SerialPort.STOPBITS_1,
					SerialPort.PARITY_NONE);

// open the streams
			input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
			output = serialPort.getOutputStream();

			serialPort.addEventListener(this);
			serialPort.notifyOnDataAvailable(true);
		} catch (Exception e) {
			System.err.println(e.toString());
		}
	}

	public synchronized void close() {
		if (serialPort != null) {
			serialPort.removeEventListener();
			serialPort.close();
		}
	}

	public synchronized void serialEvent(SerialPortEvent oEvent) {

		String url = "jdbc:mysql://localhost/teslacar?zeroDateTimeBehavior=CONVERT_TO_NULL&serverTimezone=UTC&autoReconnect=true&useSSL=false";
		String login = "root";
		String passwd = "";
		Connection cn = null;
		Statement st = null;

		if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
			try {
				String inputLine = null;
				if (input.ready()) {
					inputLine = input.readLine();

					String[] chunks = inputLine.split(" , ");

					System.out.println(inputLine);

					try {

						java.text.DecimalFormat df = new java.text.DecimalFormat("0.##");

						// Charger le driver
						Class.forName("com.mysql.jdbc.Driver");

						cn = DriverManager.getConnection(url, login, passwd);

						st = cn.createStatement();

						double n = (double) (Math.random() * 2.5);

						String resultat = df.format(n);

						// System.out.println(resultat);
						// System.out.println("Test de connection");

						String sql = "INSERT INTO donnee(vitesse, position) VALUES ('" + resultat + "' " + "," + "'"
								+ inputLine + "')";

						st.executeUpdate(sql);

					} catch (SQLException e) {
						e.printStackTrace();

					} catch (ClassNotFoundException e) {
						e.printStackTrace();
					} finally {
						try {
							cn.close();
							st.close();

						} catch (SQLException e) {
							e.printStackTrace();
						}
					}

					// System.out.println(chunks[0] + " \t " + chunks[1] + " \t " + chunks[2] + " \t
					// ");
				}

			} catch (Exception e) {
				System.err.println(e.toString());
			}
		}
// Ignore all the other eventTypes, but you should consider the other ones.
	}

	public static void main(String[] args) throws Exception {

		SerialTest main = new SerialTest();
		main.initialize();
		Thread t = new Thread() {
			public void run() {
//the following line will keep this app alive for 1000 seconds,
//waiting for events to occur and responding to them (printing incoming messages to console).
				try {
					Thread.sleep(1000000);
				} catch (InterruptedException ie) {
				}
			}
		};
		t.start();
		System.out.println(" Started ");
	}
}