import java.util.Calendar;
import structures.OrderedList;

public class Test {
   public static void main(String args[]) {
      OrderedList<Integer> lista = new OrderedList<Integer>(1);
      lista.insert(2);
      lista.insert(3);
      System.out.println(lista);

      System.out.println(lista.min());
      System.out.println(lista.max());

      System.out.println(lista.search(3));
      System.out.println(lista.search(4));

      System.out.println(lista.index(3));
      System.out.println(lista.index(4));

      System.out.println(lista.at(2));
      System.out.println(lista.at(3));

      lista.remove(2);
      System.out.println(lista);

      for (Integer el : lista)
         System.out.print(el + " ");
      System.out.println();
      System.out.println("==============================");

      OrderedList<String> lista2 = new OrderedList<String>("abc");

      lista2.insert("ghi");
      lista2.insert("def");

      System.out.println(lista2);

      System.out.println(lista2.min());
      System.out.println(lista2.max());

      System.out.println(lista2.search("def"));
      System.out.println(lista2.search("test"));

      System.out.println(lista2.index("def"));
      System.out.println(lista2.index("test"));

      System.out.println(lista2.at(2));
      System.out.println(lista2.at(3));

      lista2.remove("abc");
      System.out.println(lista2);

      for (String el : lista2)
         System.out.print(el + " ");
      System.out.println();

      System.out.println("==============================");

      OrderedList<Calendar> lista3 = new OrderedList<Calendar>(Calendar.getInstance());
      try {
         Thread.sleep(1000);
      } catch (InterruptedException ex) {
         Thread.currentThread().interrupt();
      }

      lista3.insert(Calendar.getInstance());

      try {
         Thread.sleep(1000);
      } catch (InterruptedException ex) {
         Thread.currentThread().interrupt();
      }
      lista3.insert(Calendar.getInstance());

      // System.out.println(lista3);

      // System.out.println(lista3.min());
      // System.out.println(lista3.max());

      // System.out.println(lista3.at(2));
      // System.out.println(lista3.at(3));

      // for (Calendar el : lista3)
      // System.out.print(el + " ");
      // System.out.println();

      System.out.println("==============================");

   }
}
