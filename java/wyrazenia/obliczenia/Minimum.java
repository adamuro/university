package obliczenia;

public class Minimum extends OperatorDwuArg {
  public Minimum(Wyrazenie wl, Wyrazenie wp) {
    super(wl, wp);
  }

  @Override
  public int oblicz() {
    return Math.min(this.wyrazenieLewe.oblicz(), this.wyrazeniePrawe.oblicz());
  }

  @Override
  public String toString() {
    return "min(" + this.wyrazenieLewe.toString() + ", " + this.wyrazeniePrawe.toString() + ")";
  }
}
