/*
 *
 * Lopez Tobi, Iho
 * COP-3252
 * Assignment 5
 * Date March 19th 2020
 *
 */


import java.util.Random;

public class Knight {
  private Random rand = new Random();
  private String weapons[] = {"Wooden Club",
                              "Long Sword",
                              "Battle Axe",
                              "Spear",
                              "Warhammer",
                              "Magic Staff"};
    
  private int weaponDamage[] = {new Random().nextInt(10)+50,  // add back the
                                new Random().nextInt(10)+60,  // minimum damage
                                new Random().nextInt(10)+70,  // minimum damage
                                new Random().nextInt(10)+80,  // so the range is
                                new Random().nextInt(10)+90, // [90, 100)
                                new Random().nextInt(10)+90}; // [90, 100)
  private String armors[] = {"Leather",
                              "Chain Maille"};
  /*the indices of this array match the indices
   * armors (1st dimen.) and then weapons (2nd dimen.)*/
  private int armorCounterDamage[][] = {
    {5, 10, 10, 15, 5, 0},
    {10, 30, 30, 20, 25, 0}
  };

  private String name;
  private int health;
  private int weapon;
  private int armor;

  public Knight(String nm, int w, int a) {
    setName(nm);
    setHealth(rand.nextInt(100) + 400); // range [400, 500)
    setWeapon(w - 1);
    setArmor(a - 1);
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

  public String getArmor() {
    return armors[armor];
  }

  public int getArmorAsInt() {
    return armor;
  }

  public int setArmor(int a) {
    return armor = a;
  }

  public int getVisibleEnemies() {
    return rand.nextInt(4);
  }

  public void fight (Enemy opp) {
    int damage = opp.getWeaponDamage()
      - armorCounterDamage[ getArmorAsInt() ][ opp.getWeaponAsInt() ];

    int newHealth = getHealth() - damage;
    setHealth(newHealth);

    System.out.printf("The %s attacks %s with %s and causes %d damage. %s's health is now %d\n", opp.getName(), getName(),opp.getWeapon(),damage, getName(), newHealth);
      
  }
    
    public String toString(){
        
        String output;
        output= "Knight Name: " + getName() + "\n"
        + "Knight Health: " + getHealth() + "\n"
        + "Knight Weapon: " + getWeapon() + "\n"
        + "Knight Armor: "  + getArmor()  + "\n"
       // + "Enemy's Name: " + opp.getName() + "\n"
        /*+ "Enemy's Health: " + opp.getHealth() + "\n"
        + "Enemy's Weapon: " + opp.getWeapon() + "\n"
        + "Enemy's Armor: "  + opp.getArmor()  + "\n"*/;
        
        return output;
        
        //JOptionPane.showMessageDialog(null, output);
    }
    
    public String toString(Enemy opp){
       
            
            String output;
            output= "Enemy's Name: " + opp.getName() + "\n"
            + "Enemy's Health: " + opp.getHealth() + "\n"
            + "Enemy's Weapon: " + opp.getWeapon() + "\n"
            // + "Enemy's Armor: "  + getArmor()  + "\n"
            ;
            
            return output;
        }

        
        
    
}
