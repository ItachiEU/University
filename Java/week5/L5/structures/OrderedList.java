package structures;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class OrderedList<T extends Comparable<T>> implements OrderedSequence<T>, Iterable<T> {

   private class Node<T extends Comparable<T>> {
      private Node<T> next;
      private T data;

      public Node(T el) {
         this.data = el;
      }

      public Node() {

      }
   }

   private Node<T> start;

   public OrderedList(T el) {
      start = new Node<T>(el);
   }

   @Override
   public void insert(T el) {
      Node<T> pointer = start;
      if (el.compareTo(start.data) < 0) {
         Node<T> nowy = new Node<T>(el);
         nowy.next = start;
         start = nowy;
         return;
      }
      while (pointer.next != null) {
         if (el.compareTo(pointer.next.data) < 0) {
            Node<T> nowy = new Node<T>(el);
            nowy.next = pointer.next;
            pointer.next = nowy;
            return;
         }
         pointer = pointer.next;
      }
      if (el.compareTo(pointer.data) > 0)
         pointer.next = new Node<T>(el);
   }

   @Override
   public void remove(T el) {
      if (!this.search(el))
         return;

      if (start.data == el) {
         start = start.next;
         return;
      }

      Node<T> pointer = start;
      while (pointer.next != null) {
         if (el == pointer.next.data) {
            pointer.next = pointer.next.next;
            return;
         }
         pointer = pointer.next;
      }

      if (pointer.data == el)
         pointer = null;
   }

   @Override
   public T min() {
      return start.data;
   }

   @Override
   public T max() {
      Node<T> pointer = start;
      while (pointer.next != null) {
         pointer = pointer.next;
      }
      return pointer.data;
   }

   @Override
   public T at(int pos) {
      int index = 0;
      Node<T> pointer = start;
      while (pointer.next != null) {
         if (index == pos)
            return pointer.data;
         pointer = pointer.next;
         index++;
      }
      return index == pos ? pointer.data : null;
   }

   @Override
   public boolean search(T el) {
      Node<T> pointer = start;
      while (pointer.next != null) {
         if (pointer.data == el)
            return true;
         pointer = pointer.next;
      }
      return pointer.data == el ? true : false;
   }

   @Override
   public int index(T el) {
      if (!this.search(el))
         return -1;
      int index = 0;
      Node<T> pointer = start;
      while (pointer.next != null) {
         if (pointer.data == el)
            return index;
         pointer = pointer.next;
         index++;
      }
      return index;
   }

   @Override
   public String toString() {
      Node<T> pointer = start;
      String res = "";
      while (pointer.next != null) {
         res += pointer.data + "->";
         pointer = pointer.next;
      }
      res += pointer.data;
      return res;
   }

   class ListIterator implements Iterator<T> {
      Node<T> current;
      OrderedList<T> list;

      public ListIterator(OrderedList<T> list) {
         this.list = list;
         this.current = list.start;
      }

      public boolean hasNext() {
         return current == null ? false : true;
      }

      public T next() {
         T data = current.data;
         current = current.next;
         return data;
      }

      public void remove() {
         list.remove(current.data);
      }
   }

   public Iterator<T> iterator() {
      return new ListIterator(this);
   }
}