import main.Zad2.*;
import org.junit.Test;

public class ShapeFactoryTest {
    @Test
    public void CreateShape() {
        ShapeFactory factory = new ShapeFactory();
        IShape square = factory.createShape("square", 5);
        assert square != null && square.getClass() == Square.class;
    }

    @Test
    public void CreateInvalidShape() {
        ShapeFactory factory = new ShapeFactory();
        IShape triangle = factory.createShape("triangle", 3, 4, 5);
        assert triangle == null;
    }

    @Test
    public void AddNewFactoryWorker() {
        ShapeFactory factory = new ShapeFactory();
        factory.registerWorker(new TriangleWorker());
        IShape triangle = factory.createShape("triangle", 1, 2, 3);
        assert triangle != null && triangle.getClass() == Triangle.class;
    }

    @Test
    public void CreateDifferentShapes() {
        ShapeFactory factory = new ShapeFactory();
        factory.registerWorker(new TriangleWorker());
        IShape square = factory.createShape("square", 4);
        IShape triangle = factory.createShape("triangle", 1, 2, 3);
        assert square != triangle && !square.equals(triangle);
    }
}
