package main;
import java.util.ArrayList;

public class Zad2 {
    public interface IShape {}

    public static class Square implements IShape {
        public Square(double sideLength) {
            this.sideLength = sideLength;
        }
        public double sideLength;
    }

    public static class Triangle implements IShape {
        public Triangle(double a, double b, double c) {
            this.a = a;
            this.b = b;
            this.c = c;
        }
        public double a, b, c;
    }

    public interface IShapeFactoryWorker {
        boolean acceptsParameters(String name, double... sideLengths);
        IShape Create(double... sideLengths);
    }

    public static class SquareWorker implements IShapeFactoryWorker {
        @Override
        public boolean acceptsParameters(String name, double... sideLengths) {
            return name.equalsIgnoreCase("square") && sideLengths.length == 1;
        }

        @Override
        public IShape Create(double... sideLengths) {
            return new Square(sideLengths[0]);
        }
    }

    public static class TriangleWorker implements IShapeFactoryWorker {
        @Override
        public boolean acceptsParameters(String name, double... sideLengths) {
            return name.equalsIgnoreCase("triangle") && sideLengths.length == 3;
        }

        @Override
        public IShape Create(double... sideLengths) {
            return new Triangle(sideLengths[0], sideLengths[1], sideLengths[2]);
        }
    }

    public static class ShapeFactory {
        private ArrayList<IShapeFactoryWorker> workers;

        public ShapeFactory() {
            workers = new ArrayList<>();
            workers.add(new SquareWorker());
        }

        public void registerWorker(IShapeFactoryWorker worker) {
            workers.add(worker);
        }

        public IShape createShape(String name, double... sideLengths) {
            for (IShapeFactoryWorker worker : workers) {
                if(worker.acceptsParameters(name, sideLengths)) {
                    return worker.Create(sideLengths);
                }
            }
            return null;
        }
    }
}
