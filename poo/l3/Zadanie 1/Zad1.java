import javafx.scene.shape.Shape;

/*
1. Creator - obiekty klasy Triangle są tworzone przez klasę FactoryOfTriangle,
    co pozwala w przyszłości na zmianę typu zwracanych trójkątów na klasę
    dziedziczącą po Triangle.
2. Information Expert - Figury mają wszystkie informacje potrzebne do policzenia
     obwodu, dlatego posiadają metodę za to odpowiedzialną
3. Polymorphism - Pole i obwód trójkąta są obliczane w inny sposób niż dla kwadratu,
    dlatego obie klasy nadpisują te metody klasy bazowej
4. High Cohesion - Klasy są ze sobą ściśle sprzężone - fabryka tworzy obiekty figury,
    których pole jest obliczane przez klasę implementującą interfejs kalkulatora
5. Indirection - Porównywanie obwodów figur jest wykonywane pośrednio przez obiekt
    klasy PolygonPerimeterComparator
 */

public class Zad1 {
    public abstract static class RegularPolygon {
        public double sideLength;

        public RegularPolygon(double sideLength) {
            this.sideLength = sideLength;
        }

        public abstract double area(IAreaCalculator areaCalculator);
        public abstract double perimeter();
        public abstract void printInfo();
    }

    public static class Triangle extends RegularPolygon {
        public Triangle(double sideLength) {
            super(sideLength);
        }

        @Override
        public double area(IAreaCalculator areaCalculator) {
            return areaCalculator.calculateArea(sideLength);
        }

        @Override
        public double perimeter() {
            return sideLength * 3;
        }

        @Override
        public void printInfo() {
            System.out.format("Triangle with side length of %.2f\n", sideLength);
        }
    }

    public static class Square extends RegularPolygon {
        public Square(double sideLength) {
            super(sideLength);
        }

        @Override
        public double area(IAreaCalculator areaCalculator) {
            return areaCalculator.calculateArea(sideLength);
        }

        @Override
        public double perimeter() {
            return sideLength * 4;
        }

        @Override
        public void printInfo() {
            System.out.format("Square with side length if %.2f\n", sideLength);
        }
    }

    public interface IAreaCalculator {
        double calculateArea(double sideLength);
    }

    public static class TriangleAreaCalculator implements IAreaCalculator {
        @Override
        public double calculateArea(double sideLength) {
            return (sideLength * sideLength * Math.sqrt(3)) / 4;
        }
    }

    public static class SquareAreaCalculator implements IAreaCalculator {
        @Override
        public double calculateArea(double sideLength) {
            return sideLength * sideLength;
        }
    }

    public static class FactoryOfTriangle {
        public static Triangle create(double sideLength) {
            return new Triangle(sideLength);
        }
    }

    public static class PolygonPerimeterComparator {
        public static RegularPolygon getGreaterAreaPolygon(RegularPolygon p1, RegularPolygon p2) {
            if(p1.perimeter() > p2.perimeter())
                return p1;
            return p2;
        }
    }

    public static void main(String[] args) {
        RegularPolygon triangle = FactoryOfTriangle.create(4);
        RegularPolygon square = new Square(3.5);
        PolygonPerimeterComparator prc = new PolygonPerimeterComparator();
        RegularPolygon greaterPerimeterPolygon = prc.getGreaterAreaPolygon(triangle, square);
        triangle.printInfo();
        square.printInfo();
        System.out.format("Area of triangle: %.2f: \n", triangle.area(new TriangleAreaCalculator()));
        System.out.format("Perimeter of square: %.2f\n", square.perimeter());
        System.out.format("Polygon with greater perimeter is:\n");
        greaterPerimeterPolygon.printInfo();
    }
}
