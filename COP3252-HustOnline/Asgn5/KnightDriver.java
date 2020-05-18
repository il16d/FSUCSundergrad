/*
 *
 * Lopez Tobi, Iho
 * COP-3252
 * Assignment 5
 * Date March 19th 2020
 *
 */

import java.util.*;

public class KnightDriver {
  private static Random rand = new Random();

  private static boolean over = false;
  private static boolean end_forest = false;
  private static boolean ready = false;
  private static boolean first_time = true;
  private static String choice;

  // My main method
  public static void main(String[] args) {
    while (!over) {
      Scanner in = new Scanner(System.in);

      System.out.printf("Welcome to KnightFight!\n");
      Knight k = createKnight();
      int numEnemies = 0;

      while(!ready) {
        System.out.printf("Are you ready to venture into the forest? (y|n): ");
        choice = in.nextLine();

        switch(choice) {
          case "y":
            ready = true;
            break;
          case "n":
            k = createKnight();
            break;
        }
      }
      while(!end_forest) {
        if (first_time) {
          numEnemies = 2;
          first_time = false;
        }
        else
          numEnemies = k.getVisibleEnemies();

        if (numEnemies > 0) {
          System.out.printf("\n\n%s continues into the darkness. While traveling\n", k.getName());
          System.out.printf("%s ran into a fight! %s needs to defeat %d enemies to\nmake it out alive!\n", k.getName(), k.getName(), numEnemies);

          Enemy enemies[] = new Enemy[numEnemies];

          for (int i = 0; i < numEnemies; i++) {
            enemies[i] = Enemy.getRandomEnemy();
          }

          for (int i = 0; i < numEnemies; i++) {
            System.out.printf("\n%s starts fighting %s.\n", k.getName(), enemies[i]);
            String winner = knightFight(k, enemies[i]);

            if (winner == "enemy") {
              System.out.printf("%s was defeated by %s. RIP\n", k.getName(), enemies[i]);
              end_forest = true;
              over = true;
              break;
            }
            else
              System.out.printf("%s defeated %s.\n", k.getName(), enemies[i]);
          }

          System.out.printf("\n\nPress any key to continue...");
          in.nextLine();
           
           // Enemystats(enemies);
        }
        else {
          System.out.printf("%s didn't see any more enemies and made it through the forest!\n", k.getName());
          end_forest = true;
            
        }
      }

      System.out.printf("\n\nRestart game(r) or Quit the game(q)? (r|q): ");
      choice = in.nextLine();
      switch(choice) {
        case "r":
          end_forest = false;
          over = false;
          ready = false;
          first_time = true;
          break;
        case "q":
          over = true;
              declareWinner(k);
              
          break;
      }
    }
  }

  public static void declareWinner (Knight k) {
    System.out.printf("\n\n    THE STATS ARE:\n");
    System.out.printf( k.toString());
      
  }
/*  public static void Enemystats (Enemy[] k) {
        System.out.printf("\n\n    THE STATS ARE:\n");
      
            System.out.printf( k.toString());}*/
        
    


  public static String knightFight (Knight k, Enemy e) {

    String winner = "";

    boolean semaphore = true;

    while(k.getHealth() > 0 && e.getHealth() > 0) {
      if (semaphore) {
        e.fight(k);
        semaphore = false;
      }
      else {
        k.fight(e);
        semaphore = true;
      }
    }

    if ( k.getHealth() <= 0 )
      winner = "enemy";
    else
      winner = "knight";

    return winner;
  }

  public static Knight createKnight () {
    Scanner in = new Scanner(System.in);

    System.out.printf("Enter the name of your Knight: ");
    String name = in.nextLine();
    System.out.printf("\n\n\n\n");

    System.out.printf("Now select your weapon! (Choose number)\n");
    System.out.printf("1) Long Sword\n");
    System.out.printf("2) Battle Axe\n");
    System.out.printf("3) Spear\n");
    System.out.printf("4) Warhammer\n");

    int choice = 0;
    boolean valid = false;

    while (!valid) {
      try {
        System.out.printf("Your choice my liege? : ");
        choice = in.nextInt();
        valid = true;

        if (choice > 4) {
          throw new Exception("That weapon is not available");
        }
      }
      catch(Exception e) {
        System.out.printf(e + "\n");
        valid = false;
      }
    }

    int weapon;

    switch(choice) {
      case 1:
        weapon = 1;
        break;
      case 2:
        weapon = 2;
        break;
      case 3:
        weapon = 3;
        break;
      case 4:
        weapon = 4;
        break;
      default:
        weapon = 1;
        break;
    }

    System.out.printf("Now select your armor! (Choose number)\n");
    System.out.printf("1) Leather\n");
    System.out.printf("2) Chain Maille\n");

    choice = 0;
    valid = false;

    while (!valid) {
      try {
        System.out.printf("Your choice my liege? : ");
        choice = in.nextInt();
        valid = true;

        if (choice > 2) {
          throw new Exception("That armor is not available");
        }
      }
      catch(Exception e) {
        System.out.printf(e + "\n");
        valid = false;
      }
    }

    int armor;

    switch(choice) {
      case 1:
        armor = 1;
        break;
      case 2:
        armor = 2;
        break;
      default:
        armor = 1;
        break;
    }

    return new Knight(name, weapon, armor);
  }
}
