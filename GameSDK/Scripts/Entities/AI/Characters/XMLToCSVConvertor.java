import java.io.File;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import org.supercsv.io.CsvListWriter;
import org.supercsv.io.ICsvListWriter;
import org.supercsv.prefs.CsvPreference;
public class XMLToCSVConvertor 
{
	 public static void main(String args[]) throws Exception 
	 {
		 try 
		 {	
	         
			 File inputFile = new File("C:/Users/Salil Kanetkar/Downloads/datadata.xml");
	         DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
	         DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
	         Document doc = dBuilder.parse(inputFile);
	         doc.getDocumentElement().normalize();

	         //Extracting the player position
	         NodeList nList = doc.getElementsByTagName("player_pos");
	         System.out.println("----------------------------");
	         Node nNode = nList.item(0);
	         Element eElement = (Element) nNode;
	         NodeList nList1 = eElement.getElementsByTagName("Pos");
	         String posX[] = new String[nList1.getLength()];
	         String posY[] = new String[nList1.getLength()];
	         String posZ[] = new String[nList1.getLength()];
	         for(int temp = 0; temp < nList1.getLength(); temp++) 
	         {
	        	 Node nNode1 = nList1.item(temp);
	        	 //System.out.println("\nCurrent Element :" + nNode1.getNodeName());
	        	 if (nNode1.getNodeType() == Node.ELEMENT_NODE) 
	        	 {
	                 Element eElement1 = (Element) nNode1;
	                 String[] data = (eElement1.getAttribute("pos")).split(",");
	                 posX[temp] = data[0];
	                 posY[temp] = data[1];
	                 posZ[temp] = data[2];
	        	 }
	         }
//	         
//	         //Extracting the player direction
//	         nList = doc.getElementsByTagName("player_direction");
//	         System.out.println("----------------------------");
//	         nNode = nList.item(0);
//	         eElement = (Element) nNode;
//	         nList1 = eElement.getElementsByTagName("Dir");
//	         for(int temp = 0; temp < nList1.getLength(); temp++) 
//	         {
//	        	 Node nNode1 = nList1.item(temp);
//	        	 System.out.println("\nCurrent Element :" + nNode1.getNodeName());
//	        	 if (nNode1.getNodeType() == Node.ELEMENT_NODE) 
//	        	 {
//	                 Element eElement1 = (Element) nNode1;
//	                 System.out.println("Position : " + eElement1.getAttribute("dir"));
//	        	 }
//	         }	         
//	         
//	         //Extracting the player velocity
//	         nList = doc.getElementsByTagName("player_vel");
//	         System.out.println("----------------------------");
//	         nNode = nList.item(0);
//	         eElement = (Element) nNode;
//	         nList1 = eElement.getElementsByTagName("Vel");
//	         for(int temp = 0; temp < nList1.getLength(); temp++) 
//	         {
//	        	 Node nNode1 = nList1.item(temp);
//	        	 System.out.println("\nCurrent Element :" + nNode1.getNodeName());
//	        	 if (nNode1.getNodeType() == Node.ELEMENT_NODE) 
//	        	 {
//	                 Element eElement1 = (Element) nNode1;
//	                 System.out.println("Position : " + eElement1.getAttribute("vel"));
//	        	 }
//	         }	         
	         
	      } 
		 catch (Exception e) 
		 {
	        e.printStackTrace();
		 }
	 }
}
