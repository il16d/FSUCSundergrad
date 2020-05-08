/*
 Iho Lopez Tobi
 COP3252
 January 11th 2020
 Sir class where the constructor is hosted and print function
 */


public class Sir {
    
//attributes definition
  public String name;
  public int health;
  public int battles;
  public int age;
  public int gold;
    
//constructor
  public Sir(String n, int h, int b, int a, int g) {
    name = n;
    health = h;
    battles = b;
    age = a;
    gold = g;
      }
    
//print function to display the attributes to the screen
   public void print(){
       System.out.printf("\n");
       System.out.printf("Name:     %s\n", name);
       System.out.printf("Health:   %s\n", health);
       System.out.printf("Battles:  %s\n", battles);
       System.out.printf("Age:      %s\n", age);
       System.out.printf("Gold:     %s\n", gold);
       System.out.printf("Average gold: %s\n", gold/battles);
       
        
    }
}
