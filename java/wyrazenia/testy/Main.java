package testy;

import java.util.ArrayList;
import java.util.List;

import obliczenia.Dodawanie;
import obliczenia.Dzielenie;
import obliczenia.Liczba;
import obliczenia.Logarytm;
import obliczenia.Minimum;
import obliczenia.Mnozenie;
import obliczenia.Modulo;
import obliczenia.Odejmowanie;
import obliczenia.Wyrazenie;
import obliczenia.ZmianaZnaku;
import obliczenia.Zmienna;
import struktury.Para;
import struktury.ZbiorListowy;

public class Main {
  public static void main(String[] args) {
    /* Zbiór listowy */
    ZbiorListowy zl = new ZbiorListowy();
    Para p1 = new Para("x", 1);
    Para p2 = new Para("y", 2);
    Para p3 = new Para("y", 3);
    Para p4 = new Para("z", 4);

    zl.wstaw(p1);
    zl.wypisz();

    zl.wstaw(p2);
    zl.szukaj("x").equals(p1);
    zl.szukaj("y").equals(p2);
    zl.wypisz();

    zl.szukaj("x").equals(p1);
    zl.wypisz();

    zl.wstaw(p3);
    zl.wypisz();

    zl.wstaw(p4);
    zl.wypisz();

    zl.usun("z");
    zl.wypisz();

    try {
      ZbiorListowy zl2 = (ZbiorListowy)zl.clone();
      zl2.wypisz();
    } catch (CloneNotSupportedException error) {
      System.out.println(error.getMessage());
    }

    /* Wyrazenia */
    List<Wyrazenie> wyrazenia = new ArrayList<>();
    wyrazenia.add(new Dodawanie(new Liczba(3), new Liczba(5)));
    wyrazenia.add(new Mnozenie(
      new ZmianaZnaku(
        new Odejmowanie(
          new Liczba(2),
          new Zmienna("x")
        )
      ),
      new Zmienna("y")
    ));
    wyrazenia.add(new Dzielenie(
      new Odejmowanie(
        new Mnozenie(
          new Liczba(3), 
          new Liczba(11)
        ), 
        new Liczba(1)
      ), 
      new Dodawanie(
        new Zmienna("y"), 
        new Liczba(5)
      )
    ));
    wyrazenia.add(new Minimum(
      new Mnozenie(
        new Dodawanie(
          new Zmienna("x"), 
          new Liczba(13)
        ), 
        new Zmienna("x")
      ),
      new Modulo(
        new Odejmowanie(
          new Liczba(1), 
          new Zmienna("x")), 
        new Liczba(2)
      )
    ));
    wyrazenia.add(new Logarytm(new Liczba(2), new Liczba(4)));
    wyrazenia.add(new Logarytm(new Liczba(3), new Liczba(20)));

    Zmienna.zbior.wstaw(new Para("x", 2));
    Zmienna.zbior.wstaw(new Para("y", 7));

    for (Wyrazenie wyrazenie : wyrazenia) {
      System.out.println(wyrazenie.toString() + " = " + wyrazenie.oblicz());
    }
  }
}