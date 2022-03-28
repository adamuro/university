/*
    Implementacja zaproponowana w treści jest niepoprawna,
    ponieważ jeśli zgodnie z zasadą LSP w kontekście użycia
    prostokątu zastąpimy go obiektem klasy kwadratu, to po
    przypisaniu mu długości jednego boku, wszystkie pozostałe
    również zostaną zmienione na podaną wartość.
 */

public class Zad4 {
    public interface Quadrangle {
        public abstract int Area();
    }

    public static class Rectangle implements Quadrangle {
        public int Width;
        public int Height;

        public Rectangle(int width, int height) {
            Width = width;
            Height = height;
        }

        @Override
        public int Area() {
            return Width * Height;
        }
    }

    public class Square implements Quadrangle {
        public int Side;

        public Square(int side) {
            Side = side;
        }

        @Override
        public int Area() {
            return Side * Side;
        }
    }

    public static class AreaCalculator {
        public int CalculateArea(Quadrangle quad) {
            return quad.Area();
        }
    }

    public static void main(String[] args) {
        int w = 4, h = 5;
        Quadrangle rect = new Rectangle(w, h);
        AreaCalculator calc = new AreaCalculator();

        System.out.format("Prostokąt o wymiarach %d na %d ma pole %d", w, h, calc.CalculateArea(rect));
    }
}
