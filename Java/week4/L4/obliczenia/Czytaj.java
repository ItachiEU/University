package obliczenia;

import java.util.Scanner;

public class Czytaj extends Instrukcja {
   private String zmienna;
   Scanner skan;

   public Czytaj(String nazwa) {
      this.zmienna = nazwa;
      this.skan = new Scanner(System.in);
   }

   public void wykonaj() {
      int value = skan.nextInt();
      (new Deklaracja(zmienna, value)).wykonaj();
      skan.close();
   }
}
