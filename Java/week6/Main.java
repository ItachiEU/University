import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

import java.util.Random;

public class Main extends JFrame implements KeyListener {
   int curX;
   int curY;
   JLayeredPane layeredPane;
   JPanel mapa;
   JLabel player;
   int xAdjustment;
   int yAdjustment;
   MazeGenerator maze;

   public Main() {
      maze = new MazeGenerator(21, 21);
      Dimension boardSize = new Dimension(950, 950);
      layeredPane = new JLayeredPane();
      getContentPane().add(layeredPane);
      layeredPane.setPreferredSize(boardSize);
      layeredPane.addKeyListener(this);
      layeredPane.setFocusable(true);
      layeredPane.requestFocus();

      mapa = new JPanel();
      layeredPane.add(mapa, JLayeredPane.DEFAULT_LAYER);
      mapa.setLayout(new GridLayout(19, 19));
      mapa.setPreferredSize(boardSize);
      mapa.setBounds(0, 0, boardSize.width, boardSize.height);

      for (int i = 0; i < 21; i++) {
         for (int j = 0; j < 21; j++) {
            System.out.print(maze.maze[i][j] + " ");
         }
         System.out.println();
      }

      for (int i = 0; i < 19 * 19; i++) {
         JPanel square = new JPanel(new BorderLayout());
         mapa.add(square);
         int x = i / 19, y = i % 19;
         square.setBackground(maze.maze[x + 1][y + 1] == '#' ? Color.black : Color.white);
         if (i == 19 * 19 - 1)
            square.setBackground(Color.green);
      }

      // Add our Knight

      JLabel piece = new JLabel(new ImageIcon("knight.png"));
      JPanel panel = (JPanel) mapa.getComponent(0);
      panel.add(piece);
      this.curX = 1;
      this.curY = 1;
   }

   public void keyPressed(KeyEvent e) {
   }

   public void keyReleased(KeyEvent e) {
      if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
         if (curX + 1 > 19 || maze.maze[curY][curX + 1] != ' ') {
            return;
         }
         curX += 1;
         if (player == null) {
            Component c = mapa.findComponentAt(10, 10);
            player = (JLabel) c;
            layeredPane.add(player, JLayeredPane.DRAG_LAYER);
         }
         xAdjustment = 50;
         yAdjustment = 0;
         player.setLocation(player.getX() + xAdjustment, player.getY() + yAdjustment);
         player.setSize(player.getWidth(), player.getHeight());
         // to do
      } else if (e.getKeyCode() == KeyEvent.VK_LEFT) {
         if (curX - 1 < 1 || maze.maze[curY][curX - 1] != ' ') {
            return;
         }
         curX -= 1;
         if (player == null) {
            Component c = mapa.findComponentAt(10, 10);
            player = (JLabel) c;
            layeredPane.add(player, JLayeredPane.DRAG_LAYER);
         }
         xAdjustment = -50;
         yAdjustment = 0;
         player.setLocation(player.getX() + xAdjustment, player.getY() + yAdjustment);
         player.setSize(player.getWidth(), player.getHeight());
         // to do
      } else if (e.getKeyCode() == KeyEvent.VK_DOWN) {
         if (curY + 1 > 19 || maze.maze[curY + 1][curX] != ' ') {
            return;
         }
         curY += 1;
         if (player == null) {
            Component c = mapa.findComponentAt(10, 10);
            player = (JLabel) c;
            layeredPane.add(player, JLayeredPane.DRAG_LAYER);
         }
         xAdjustment = 0;
         yAdjustment = 50;
         player.setLocation(player.getX() + xAdjustment, player.getY() + yAdjustment);
         player.setSize(player.getWidth(), player.getHeight());
         // to do
      } else if (e.getKeyCode() == KeyEvent.VK_UP) {
         if (curY - 1 < 1 || maze.maze[curY - 1][curX] != ' ') {
            return;
         }
         curY -= 1;
         if (player == null) {
            Component c = mapa.findComponentAt(10, 10);
            player = (JLabel) c;
            layeredPane.add(player, JLayeredPane.DRAG_LAYER);
         }
         xAdjustment = 0;
         yAdjustment = -50;
         player.setLocation(player.getX() + xAdjustment, player.getY() + yAdjustment);
         player.setSize(player.getWidth(), player.getHeight());
         // to do
      }
      if (player.getX() == 900 && player.getY() == 900) {
         System.out.println("Gratulacje");
      }
   }

   public void keyTyped(KeyEvent e) {
   }

   public static void main(String[] args) {
      JFrame frame = new Main();
      frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
      frame.pack();
      frame.setResizable(true);
      frame.setLocationRelativeTo(null);
      frame.setVisible(true);
   }
}

class MazeGenerator {
   public char[][] maze;
   private int x;
   private int y;
   Random random;

   public MazeGenerator(int x, int y) {
      maze = new char[x][y];
      random = new Random();
      this.x = x;
      this.y = y;
      for (int i = 0; i < x; i++)
         for (int j = 0; j < y; j++)
            maze[i][j] = '#';
      visit(1, 1);
   }

   boolean inBounds(int x, int y) {
      if (x < 0 || x >= this.x)
         return false;
      if (y < 0 || y >= this.y)
         return false;
      return true;
   }

   void visit(int x, int y) {
      maze[x][y] = ' ';
      int[] dirs = new int[4];
      for (int i = 0; i < 4; i++)
         dirs[i] = i;

      for (int i = 0; i < 4; i++) {
         int r = random.nextInt(3);
         int temp = dirs[r];
         dirs[r] = dirs[i];
         dirs[i] = temp;
      }

      for (int i = 0; i < 4; i++) {
         int dx = 0, dy = 0;
         switch (dirs[i]) {
            case 0:
               dy = -1;
               break;
            case 1:
               dy = 1;
               break;
            case 2:
               dx = 1;
               break;
            case 3:
               dx = -1;
               break;
         }
         int x2 = x + dx * 2;
         int y2 = y + dy * 2;
         if (inBounds(x2, y2)) {
            if (maze[x2][y2] == '#') {
               maze[x2 - dx][y2 - dy] = ' ';
               visit(x2, y2);
            }
         }
      }
   }
}