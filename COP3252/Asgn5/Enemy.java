/*
 *
 * Lopez Tobi, Iho
 * COP-3252
 * Assignment 5
 * Date March 19th 2020
 *
 */


import java.util.*;

public abstract class Enemy {
  // Fields
  private String weapons[] = {"Confussion and infection",
                              "Stay at home and die from borrigness",
                              "Fear of running out of toilet paper",
                              "Going on a world tour while being exposed to the virus",
                              "Shortness of Breath",
                              "Absolutely nothing at all"};
  private int weaponDamage[] = {new Random().nextInt(10)+50,  // add back the
                                new Random().nextInt(10)+60,  // minimum damage
                                new Random().nextInt(10)+70,  // minimum damage
                                new Random().nextInt(10)+80,  // so the range is
                                new Random().nextInt(10)+90, // [90, 100)
                                new Random().nextInt(10)+90}; // [90, 100)

  private String name;
  private int health;
  private int weapon;

 
  public void takeDamage(int d) throws InvalidDamageException {
    int newHealth = getHealth() - d;

    if (newHealth < 0)
      throw new InvalidDamageException();
    else
      setHealth(newHealth);
  }

  public static Enemy getRandomEnemy() {
    int randEnemy = new Random().nextInt(3);

    Enemy enemies[] = {new CoronaVirus(),
                       new Quarentine(),
                       new SpringBreak()};

    return enemies[ randEnemy ];
  }

  public void setName(String n) {
    name = n;
  }

  public String getName() {
    return name;
  }

  public void setHealth(int h) {
    health = h;
  }

  public int getHealth() {
    return health;
  }

  public void setWeapon(int w) {
    weapon = w;
  }

  public String getWeapon() {
    return weapons[weapon];
  }

  public int getWeaponAsInt() {
    return weapon;
  }

  public int getWeaponDamage() {
    return weaponDamage[weapon];
  }

  /*  public String toString(){
   
        String output;
        output= "Enemy's Name: " + getName() + "\n"
        + "Enemy's Health: " + getHealth() + "\n"
        + "Enemy's Weapon: " + getWeapon() + "\n"
       // + "Enemy's Armor: "  + getArmor()  + "\n"
        ;
   
        return output;
    }
*/

  // Abstract Methods
  abstract public void fight(Knight opp);
}
