package obliczenia;

import java.util.Scanner;

public class Cin extends Instrukcja {
   private String zmienna;
   Scanner skan;

   public Cin(String nazwa) {
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
