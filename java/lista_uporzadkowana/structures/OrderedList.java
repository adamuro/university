package structures;

import java.util.Iterator;

public class OrderedList<T extends Comparable<T>> implements OrderedSequence<T>, Iterable<T> {
  private class Node<TN extends Comparable<TN>> {
    private Node<TN> next;
    private TN data;

    public Node(Node<TN> next, TN data) {
      this.next = next;
      this.data = data;
    }

    public boolean insert(TN el) {
      if (el.compareTo(this.data) == 0) return false;

      if (el.compareTo(this.data) < 0) {
        this.next = new Node<TN>(this.next, this.data);
        this.data = el;
      } else if (this.next == null) {
        this.next = new Node<TN>(null, el);
      } else {
        return this.next.insert(el);
      }

      return true;
    }

    public boolean remove(TN el) {
      if (this.next == null) return false;

      if (this.next.data.compareTo(el) == 0) {
        this.next = this.next.next;
      } else {
        return this.next.remove(el);
      }

      return true;
    }

    public TN max() {
      if (this.next == null) return this.data;

      return this.next.max();
    }

    public TN at(int pos) throws IndexOutOfBoundsException {
      if (pos == 0) return this.data;
      if (this.next == null) throw new IndexOutOfBoundsException();

      return this.next.at(pos - 1);
    }

    public boolean search(TN el) {
      if (el.compareTo(this.data) == 0) return true;
      if (this.next == null) return false;

      return this.next.search(el);
    }

    public int index(TN el, int i) {
      if (el.compareTo(this.data) == 0) return i;
      if (el.compareTo(this.data) < 0 || this.next == null) return -1;

      return this.next.index(el, i + 1);
    }
  }

  private Node<T> head;
  private int size;

  /* Użycie StringBuildera */
  @Override
  public String toString() {
    Node<T> node = this.head;
    StringBuilder stringBuilder = new StringBuilder("[");
    while(node.next != null) {
      stringBuilder.append(node.data + ", ");
      node = node.next;
    }

    stringBuilder.append(node.data + "]");
    return stringBuilder.toString();
  }

  @Override
  public void insert(T el) throws NullPointerException {
    if (el == null) throw new NullPointerException();

    if (this.head == null) {
      this.head = new Node<T>(null, el);
      this.size += 1;
    } else if (this.head.insert(el)) {
      this.size += 1;
    }
  }

  @Override
  public void remove(T el) throws NullPointerException {
    if (el == null) throw new NullPointerException();
    if (this.head == null) return;

    if (this.head.data.compareTo(el) == 0) {
      this.head = this.head.next;
      this.size -= 1;
    } else if (this.head.remove(el)) {
      this.size -= 1;
    }
  }

  @Override
  public T min() {
    if (this.head == null) return null;

    return this.head.data;
  }

  @Override
  public T max() {
    if (this.head == null) return null;
    
    return this.head.max();
  }

  @Override
  public T at(int pos) throws IndexOutOfBoundsException {
    if (this.head == null) throw new IndexOutOfBoundsException();
    if (pos < 0) throw new IndexOutOfBoundsException();

    return this.head.at(pos);
  }

  @Override
  public boolean search(T el) throws NullPointerException {
    if (el == null) throw new NullPointerException();
    if (this.head == null) return false;
    
    return this.head.search(el);
  }

  @Override
  public int index(T el) throws NullPointerException {
    if (el == null) throw new NullPointerException();

    return this.head.index(el, 0);
  }

  @Override
  public int size() {
    return this.size;
  }

  /* Poprawiona klasa iteratora */
  private class OrderedListIterator implements Iterator<T> {
    private Node<T> currentNode;
    private Node<T> lastNode;

    @Override
    public boolean hasNext() {
      if (this.currentNode == null) {
        return OrderedList.this.head != null;
      }

      return this.currentNode.next != null;
    }

    @Override
    public T next() {
      if (this.currentNode == null) {
        this.currentNode = OrderedList.this.head;
      } else if (this.lastNode == null) {
        this.lastNode = this.currentNode;
        this.currentNode = this.currentNode.next;
      } else {
        this.currentNode = this.currentNode.next;
        if (this.lastNode.next != this.currentNode) {
          this.lastNode = this.lastNode.next;
        }
      }
      return this.currentNode.data;
    }

    @Override
    public void remove() {
      if (this.lastNode == null) {
        OrderedList.this.head = OrderedList.this.head.next;
        this.currentNode = null;
      } else {
        Node<T> searchNode = OrderedList.this.head;
        while (searchNode.data != this.lastNode.data) {
          searchNode = searchNode.next;
        }

        searchNode.next = searchNode.next.next;
      }
    }
  }

  @Override
  public Iterator<T> iterator() {
    return new OrderedListIterator();
  }
}