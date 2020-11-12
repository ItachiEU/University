package test;

import struktury.*;

public class Test2 {
   public void run() {
      ZbiorNaTablicyDynamicznej z = new ZbiorNaTablicyDynamicznej();
      Para test1;
      try {
         test1 = z.szukaj("test1");
      } catch (Exception e) {
         System.out.println(e);
      }
      try {
         z.wstaw(new Para("test", 1.0));
         z.wstaw(new Para("tescior", 2.0));
         z.wstaw(new Para("tescik", 3.0));
         z.wstaw(new Para("testunio", 4.0));
      } catch (Exception e) {
         System.out.println(e);
      }
      try {
         test1 = z.szukaj("test");
         System.out.println(test1);
      } catch (Exception e) {
         System.out.println(e);
      }
      try {
         z.usun("test");
      } catch (Exception e) {
         System.out.println(e);
      }
      try {
         test1 = z.szukaj("test");
         System.out.println(test1);
      } catch (Exception e) {
         System.out.println(e);
      }
      try {
         z.ustaw(new Para("test", 1.0));
      } catch (Exception e) {
         System.out.println(e);
      }
      System.out.println("W tablicy jest tyle: " + z.ile());
      System.out.println("Rozmiar tablicy: " + z.getSize());
      try {
         z.usun("tescior");
         z.usun("tescik");
      } catch (Exception e) {
         System.out.println(e);
      }
      System.out.println("W tablicy jest tyle: " + z.ile());
      System.out.println("Rozmiar tablicy: " + z.getSize());
   }
}
