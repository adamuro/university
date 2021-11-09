package obliczenia;

public class Maksimum extends OperatorDwuArg {
  public Maksimum(Wyrazenie wl, Wyrazenie wp) {
    super(wl, wp);
  }

  @Override
  public int oblicz() {
    return Math.min(this.wyrazenieLewe.oblicz(), this.wyrazeniePrawe.oblicz());
  }

  @Override
  public String toString() {
    return "max(" + this.wyrazenieLewe.toString() + ", " + this.wyrazeniePrawe.toString() + ")";
  }
}
