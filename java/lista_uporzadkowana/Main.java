import java.util.Iterator;

import structures.OrderedList;

class Main {
  public static void main(String[] args) {
    OrderedList<Integer> ol = new OrderedList<>();
    ol.insert(4);
    System.out.println(ol);
    System.out.println("size: " + ol.size());
    ol.insert(5);
    System.out.println(ol);
    ol.insert(2);
    System.out.println(ol);
    ol.insert(3);
    System.out.println(ol);
    ol.insert(1);
    System.out.println(ol);
    System.out.println("size: " + ol.size());
    System.out.println("min: " + ol.min());
    System.out.println("max: " + ol.max());
    try {
      System.out.println("at 0: " + ol.at(0));
      System.out.println("at 2: " + ol.at(2));
      System.out.println("at 4: " + ol.at(4));
      System.out.println("at 6: " + ol.at(6));
    } catch (IndexOutOfBoundsException e) {
      System.out.println("wyjątek (at 6)");
    }
    ol.remove(2);
    System.out.println(ol);
    System.out.println("size: " + ol.size());
    ol.remove(5);
    System.out.println(ol);
    ol.remove(1);
    System.out.println(ol);
    System.out.println("size: " + ol.size());
    System.out.println("min: " + ol.min());
    System.out.println("max: " + ol.max());

    System.out.println("search 3: " + ol.search(3));
    System.out.println("search 5: " + ol.search(5));
    System.out.println("index 0: " + ol.index(0));
    System.out.println("index 3: " + ol.index(3));
    System.out.println("index 4: " + ol.index(4));
    System.out.println("index 5: " + ol.index(5));

    ol.insert(4);
    ol.insert(7);
    ol.insert(1);
    ol.insert(9);

    System.out.println(ol);

    for (Integer i : ol) {
      System.out.println(i);
    }

    System.out.println("Iterator");
    Iterator<Integer> iter = ol.iterator();

    System.out.println("next: " + iter.next());
    System.out.println("remove");
    iter.remove();
    System.out.println(ol);
    System.out.println("next: " + iter.next());
    System.out.println("next: " + iter.next());
    System.out.println("remove");
    iter.remove();
    System.out.println(ol);
    System.out.println("next: " + iter.next());
    System.out.println("next: " + iter.next());
    System.out.println("remove");
    iter.remove();
    System.out.println(ol);
    System.out.println(iter.hasNext());
  }
}