package struktury;

public class ZbiorNaTablicyDynamicznej extends Zbior {
   private Para[] tablica;

   public ZbiorNaTablicyDynamicznej() {
      tablica = new Para[2];
   }

   public int getSize() {
      return tablica.length;
   }

   @Override
   public Para szukaj(String k) throws Exception {
      for (int i = 0; i < tablica.length; i++) {
         if (tablica[i] != null && tablica[i].klucz == k)
            return tablica[i];
      }
      throw new IllegalArgumentException("Nie ma takiej pary w zbiorze.");
   }

   @Override
   public void wstaw(Para p) throws Exception {
      for (int i = 0; i < tablica.length; i++) {
         if (tablica[i] != null && tablica[i].equals(p))
            throw new IllegalArgumentException("W tablicy jest juz para o tym kluczu.");
      }
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] == null) {
            tablica[i] = p;
            return;
         }
      // Nie znaleźlismy miejsca, wiec musimy powiekszyc wektor
      Para[] temp = new Para[tablica.length * 2];
      for (int i = 0; i < tablica.length; i++)
         temp[i] = tablica[i];
      temp[tablica.length] = p;
      tablica = temp;
   }

   @Override
   public void usun(String k) throws Exception {
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
   public double czytaj(String k) throws Exception {
      for (int i = 0; i < tablica.length; i++)
         if (tablica[i] != null && tablica[i].klucz == k)
            return tablica[i].getValue();
      throw new IllegalArgumentException("Nie ma w tablicy pary o takim kluczu.");
   }

   @Override
   public void ustaw(Para p) throws Exception {
      try {
         this.szukaj(p.klucz);
         for (int i = 0; i < tablica.length; i++) {
            if (tablica[i] != null && tablica[i].klucz == p.klucz)
               tablica[i] = p;
         }
      } catch (Exception e) {
         this.wstaw(p);
      }
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
