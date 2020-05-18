/*
 Iho Lopez Tobi
 COP3252
 January 11th 2020
 Assignment 2
 */

import java.util.Scanner;

public class Assignment2 {
  // My main method
  public static void main(String[] args) {
    Scanner k = new Scanner(System.in);

    System.out.printf("\n");

    System.out.printf("New Character\n");
      
    System.out.printf("Enter a name: ");
    String name = k.nextLine();
      
    System.out.printf("Enter health: ");
    int health = k.nextInt();

    System.out.printf("Enter number of battles: ");
    int battles = k.nextInt();
    
    System.out.printf("Enter age: ");
    int age = k.nextInt();
      
    System.out.printf("Enter gold: ");
    int gold = k.nextInt();
      
      
   
      
      
   Sir Javalot = new Sir(name, health, battles, age, gold);
   Javalot.print();
  }
}
