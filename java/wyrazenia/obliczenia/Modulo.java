package obliczenia;

public class Modulo extends OperatorDwuArg {
  public Modulo(Wyrazenie wl, Wyrazenie wp) {
    super(wl, wp);
  }

  @Override
  public int oblicz() {
    return this.wyrazenieLewe.oblicz() % this.wyrazeniePrawe.oblicz();
  }

  @Override
  public String toString() {
    return "(" + this.wyrazenieLewe.toString() + " % " + this.wyrazeniePrawe.toString() + ")";
  }
}