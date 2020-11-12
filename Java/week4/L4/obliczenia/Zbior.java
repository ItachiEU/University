package obliczenia;

public class Zbior extends ZbiorTemplate {
   private Para[] tablica;

   public Zbior() {
      tablica = new Para[8];
   }

   public int getSize() {
      return tablica.length;
   }

   @Override
   public Para szukaj(String k) {
      for (int i = 0; i < tablica.length; i++) {
         if (tablica[i] != null && tablica[i].klucz == k)
            return tablica[i];
      }
      throw new IllegalArgumentException("Nie znaleziono klucza: " + k);
   }

   @Override
   public void wstaw(Para p) {
      for (int i = 0; i < tablica.length; i++) {
         if (tablica[i] != null && tablica[i].equals(p))
            throw new IllegalArgumentException("W tablicy jest juz para o tym kluczu.");
      }
      if (this.ile() == tablica.length) {
         // Nie znaleźlismy miejsca, wiec musimy powiekszyc wektor
         Para[] temp = new Para[tablica.length * 2];
         for (int i = 0; i < tablica.length; i++)
            temp[i] = tablica[i];
         temp[tablica.length] = p;
         tablica = temp;
      }
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] == null) {
            tablica[i] = p;
            return;
         }
   }

   @Override
   public void usun(String k) {
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] != null && tablica[i].klucz == k)
            tablica[i] = null;
      // Sprawdzamy czy trzeba zmniejszyc tablice
      if (this.ile() < tablica.length / 4) {
         Para[] temp = new Para[(tablica.length + 1) / 2];
         int counter = 0;
         for (int i = 0; i < tablica.length; i++)
            if (tablica[i] != null)
               temp[counter++] = tablica[i];
         tablica = temp;
      }
   }

   @Override
   public double czytaj(String k) {
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] != null && tablica[i].klucz == k)
            return tablica[i].getValue();
      throw new IllegalArgumentException("Nie ma w tablicy pary o takim kluczu: " + k);
   }

   public boolean istnieje(String k) {
      Para tmp = (new Para(k, 0.0));
      for (int i = 0; i < tablica.length; i++) {
         if (tmp.equals(tablica[i]))
            return true;
      }
      return false;
   }

   @Override
   public void ustaw(Para p) {
      for (int i = 0; i < tablica.length; i++)
         if (p.equals(tablica[i])) {
            tablica[i] = p;
            return;
         }
      wstaw(p);
   }

   @Override
   public void czysc() {
      for (int i = 0; i < tablica.length; i++)
         tablica[i] = null;
      tablica = new Para[2];
   }

   @Override
   public int ile() {
      int res = 0;
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] != null)
            res++;
      return res;
   }

}
