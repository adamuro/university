package figury;

public class Prosta {
  public final double a, b, c;

  public Prosta(double a, double b, double c) throws IllegalArgumentException {
    if (a == 0 && b == 0) {
      throw new IllegalArgumentException("Podane parametry prostej są nieprawidłowe");
    }

    this.a = a;
    this.b = b;
    this.c = c;
  }

  public static Prosta przesun(Prosta p, Wektor w) {
    return new Prosta(p.a, p.b, p.c - w.dx + w.dy);
  }

  public static boolean rownolegle(Prosta p1, Prosta p2) {
    return (p1.a * p2.b) - (p2.a * p1.b) == 0;
  }

  public static boolean prostopadle(Prosta p1, Prosta p2) {
    return (p1.a * p2.b) + (p2.a * p2.b) == 0;
  }

  public static Punkt przeciecie(Prosta p1, Prosta p2) throws IllegalArgumentException {
    if (rownolegle(p1, p2)) {
      throw new IllegalArgumentException("Podane proste są równoległe");
    }

    double d = (p1.a * p2.b) - (p2.a * p1.b);
    double x = ((p1.b * p2.c) - (p2.b * p1.c)) / d;
    double y = ((p1.a * p2.c) - (p2.a * p1.c)) / -d;

    return new Punkt(x, y);
  }
}