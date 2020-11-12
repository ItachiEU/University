package test;

import struktury.*;

public class Test1 {
   public void run() {
      ZbiorNaTablicy z = new ZbiorNaTablicy(3);
      Para test1;
      try {
         test1 = z.szukaj("test1");
      } catch (Exception e) {
         System.out.println(e);
      }
      try {
         z.wstaw(new Para("test", 1.0));
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
      System.out.println(z.ile());
   }
}