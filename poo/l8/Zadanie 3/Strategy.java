import com.fasterxml.jackson.databind.ObjectMapper;
import com.mongodb.MongoClient;
import com.mongodb.MongoClientURI;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.MongoDatabase;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.FileInputStream;
import java.util.Map;

public class Strategy {
    public class DataAccessHandler {
        private IDataAccessStrategy strategy;

        public void execute() {
            this.strategy.openConnection();
            this.strategy.getData();
            this.strategy.processData();
            this.strategy.closeConnection();
        }
    }

    public interface IDataAccessStrategy {
        void openConnection();
        void getData();
        void processData();
        void closeConnection();
    }

    public class DatabaseAccessStrategy implements IDataAccessStrategy {
        private String clientURI;
        private String databaseName;
        private String collectionName;
        private MongoClient mongoClient;
        private MongoCursor cursor;

        public DatabaseAccessStrategy(String clientURI, String databaseName, String collectionName) {
            this.clientURI = clientURI;
            this.databaseName = databaseName;
            this.collectionName = collectionName;
        }

        @Override
        public void openConnection() {
            this.mongoClient = new MongoClient(new MongoClientURI(this.clientURI));
        }

        @Override
        public void getData() {
            MongoDatabase database = this.mongoClient.getDatabase(this.databaseName);
            MongoCollection collection = database.getCollection(this.collectionName);
            FindIterable data = collection.find();
            this.cursor = data.iterator();
        }

        @Override
        public void processData() {
            Integer sum = 0;
            try {
                ObjectMapper mapper = new ObjectMapper();
                while (this.cursor.hasNext()) {
                    String json = (String) this.cursor.next();
                    Map<String, Object> map = mapper.readValue(json, Map.class);
                    sum += (Integer) map.get("value");
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }

            System.out.println(sum);
        }

        @Override
        public void closeConnection() {
            this.cursor.close();
            this.mongoClient.close();
        }
    }

    public class XMLAccessStrategy implements IDataAccessStrategy {
        private String fileName;
        private FileInputStream XMLInputStream;
        private Document document;
        private NodeList nodeList;

        public XMLAccessStrategy(String fileName) {
            this.fileName = fileName;
        }

        @Override
        public void openConnection() {
            try {
                DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
                this.XMLInputStream = new FileInputStream(this.fileName);
                this.document = documentBuilder.parse(this.XMLInputStream);
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }

        @Override
        public void getData() {
            this.nodeList = this.document.getElementsByTagName("*");
        }

        @Override
        public void processData() {
            String longestNodeName = "";
            for (int i = 0; i < nodeList.getLength(); i++) {
                Node node = nodeList.item(i);
                if(node.getNodeType() == Node.ELEMENT_NODE) {
                    if(node.getNodeName().length() > longestNodeName.length()) {
                        longestNodeName = node.getNodeName();
                    }
                }
            }

            System.out.println(longestNodeName);
        }

        @Override
        public void closeConnection() {
            try {
                this.XMLInputStream.close();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }
}
