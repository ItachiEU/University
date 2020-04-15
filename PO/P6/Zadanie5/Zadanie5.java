
public class Zadanie5 {
   public static void main(String[] args) {
      int[] tab = { 10, 9, 8, 7, 6, -5, -4, -3, -2, 101, 102 };
      MergeSort sort = new MergeSort(tab, 0, tab.length - 1);
      Thread thread = new Thread(sort);
      try {
         thread.start();
         thread.join();
      } catch (InterruptedException err) {
         err.printStackTrace();
      }

      System.out.println("Result: ");
      for (int i = 0; i < tab.length; i++) {
         System.out.print(tab[i] + " ");
      }
   }
}