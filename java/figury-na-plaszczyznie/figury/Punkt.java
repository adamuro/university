package figury;

public class Punkt {
  private double x, y;

  public Punkt(double x, double y) {
    this.x = x;
    this.y = y;
  }

  // Dodany konstruktor kopiujący
  public Punkt(Punkt p) {
    this.x = p.x;
    this.y = p.y;
  }

  public boolean rowny(Punkt p) {
    return this.x == p.x && this.y == p.y;
  }

  public double nachylenieWzgledem(Punkt p) {
    if (this.x == p.x) {
      return this.y > p.y ? Double.POSITIVE_INFINITY : Double.NEGATIVE_INFINITY;
    }

    return (p.y - this.y) / (p.x - this.x);
  }

  public void przesun(Wektor v) {
    this.x += v.dx;
    this.y += v.dy;
  }

  public void obroc(Punkt p, double kat) {
    double sin = Math.sin(kat);
    double cos = Math.cos(kat);

    double x = this.x - p.x;
    double y = this.y - p.y;

    double xObrocone = (x * cos) - (y * sin);
    double yObrocone = (x * sin) + (y * cos);

    this.x = xObrocone + p.x;
    this.y = yObrocone + p.y;
  }

  public void odbij(Punkt p) {
    this.x = (2 * p.x) - this.x;
    this.y = (2 * p.y) - this.y;
  };

  @Override
  public String toString() {
    return "(" + this.x + ", " + this.y + ")";
  }
}
