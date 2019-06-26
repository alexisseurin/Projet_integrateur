import java.util.Enumeration;

import gnu.io.CommPortIdentifier;

public class CommPortTest {

	public static void main(String[] args) {
		System.out.println(" Program Started!!! ");

		CommPortIdentifier serialPortId;

		Enumeration enumComm;

		enumComm = CommPortIdentifier.getPortIdentifiers();

		while (enumComm.hasMoreElements()) {
			serialPortId = (CommPortIdentifier) enumComm.nextElement();
			if (serialPortId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				System.out.println(serialPortId.getName());
			}
		}

		System.out.println(" Program Finished Sucessfully ");
	}

}