package figury;

public class Main {
  public static void main(String[] args) {
    Trojkat t = new Trojkat(new Punkt(0, 0), new Punkt(1, 2), new Punkt(3, 3));
    System.out.println(t);
    t.przesun(new Wektor(2, 1));
    System.out.println(t);
    t.obroc(new Punkt(1, 1), Math.PI / 2.0);
    System.out.println(t);
    t.odbij(new Punkt(0, 0));
    System.out.println(t);
  }
}