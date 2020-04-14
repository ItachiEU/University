import java.util.Collections;
import java.util.Scanner;

public class Zadanie1 {

   public static void main(String[] args) {
      System.err.println("Implementacja listy");
      Zadanie1 test = new Zadanie1();
      test.test();
   }

   public void test() {
      Lista<Integer> lista = new Lista<Integer>();
      lista.add(7);
      lista.add(12);
      lista.add(3);
      System.out.print(lista.PopFirst() + "\n");
      lista.PrintList();
   }

   // IMPLEMENTACJA LISTY ORAZ JEJ FUNKCJI:
   public class Lista<T extends Comparable> {
      private Lista<T> first;
      private Lista<T> next;
      private T value;

      public void add(T a) {
         if (first == null) {
            first = new Lista<T>();
            first.value = a;
            first.next = null;
         } else {
            if (first.value.compareTo(a) > 0) {
               Lista<T> nowa = new Lista<T>();
               nowa.value = first.value;
               first.value = a;
               nowa.next = first.next;
               first.next = nowa;
            } else {
               Lista<T> pointer = first;
               while (pointer.next != null) {
                  if (pointer.next.value.compareTo(a) > 0)
                     break;
                  pointer = pointer.next;
               }
               Lista<T> nowa = new Lista<T>();
               nowa.value = a;
               nowa.next = pointer.next;
               pointer.next = nowa;
            }
         }
      }

      public T PopFirst() {
         T val = first.value;
         if (first.next != null) {
            first = first.next;
         } else {
            first = null;
         }
         return val;
      }

      public void PrintList() {
         if (first == null) {
            System.out.print("The list is empty.");
            return;
         }
         Lista<T> temporary = first;
         while (temporary != null) {
            System.out.print(temporary.value + " ");
            temporary = temporary.next;
         }
      }
   }
}