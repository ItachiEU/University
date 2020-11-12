package obliczenia;

import java.util.Scanner;

public class Read extends Instrukcja {
   private String zmienna;
   Scanner skan;

   public Read(String nazwa) {
      this.zmienna = nazwa;
      this.skan = new Scanner(System.in);
   }

   @Override
   public void wykonaj() {
      int value = skan.nextInt();
      (new Deklaracja(zmienna, new Liczba(value))).wykonaj();
      skan.close();
   }

}
