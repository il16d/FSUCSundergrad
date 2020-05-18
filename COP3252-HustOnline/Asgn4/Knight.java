/*
 *
 * Lopez Tobi, Iho
 * COP-3252
 * Assignment 4
 * Date February 9th 2020
 *
 */


//import javax.swing.JOptionPane;
import java.util.Random;

public class Knight
{
    private String name;
    private int health;
    private int weapon;
    private int armor;
   // private int gold;
   // private Stars star;
    
    /*
     1) Long Sword
     
     2) Battle Axe
     
     3) Spear
     
     4) Warhammer
     */
    private int armorDamage[][] = {
    {10, 10, 15, 5},
    {30, 30, 20, 25}};
    
    private String armors[] = {"Leather", "Metal"};
    private Random randm = new Random();
    private String WHEAPON[] = {"Long Sword", "Battle Axe", "Spear", "Warhammer"};
    private String Fname[] = {"Stan", "Archer", "Bart"};
    private int Wdamage[] = {new Random().nextInt(10)+60, new Random().nextInt(10)+70,new Random().nextInt(10)+80,new Random().nextInt(10)+90};
    
    
    
    public Knight()
    {
        Random ranodm = new Random();
        
        SetName(Fname[ranodm.nextInt(3)] );
        SetHealth(ranodm.nextInt(100)+400);
        SetWeapon(ranodm.nextInt(4));
        setArmor( ranodm.nextInt(2) );
        
    }
    
    public Knight(String N, int H, int A)
    {
        
        SetName(N);
        SetHealth(randm.nextInt(100)+400);
        SetWeapon(H-1);
        setArmor(A - 1);
        
        
    }
    
    public String GetName()
    {
        return name;
    }
    public int GetHealth()
    {
        return health;
    }
    public String GetWeapon()
    {
        return WHEAPON[weapon];
    }
    
    public int GetWeaponpos()
    {
        return weapon;
    }
    
    
    public int getWDamage()
    {
        return Wdamage[weapon];
    }
    
    public String GetArmor() { //getArmor
        return armors[armor];
    }
    
    public int GetArmorpos() { //getarmorasint
        return armor;
    }
    
   
    
    public void SetName(String Name)
    {
        
        name = Name;
    }
    
    public void SetHealth( int Health)
    {
        health = Health;
    }
    
    public void SetWeapon(int Weapon)
    {
        weapon = Weapon;
    }
    
    
    public int setArmor(int a) {
        return armor = a;
    }
   
    // **END OF SET AND GET METHODS**
    
    
    
    public void fight (Knight k)
    {
        int life = k.getWDamage()-armorDamage[GetArmorpos()][k.GetWeaponpos()];
        int yalifenow = GetHealth()-life;
        SetHealth(yalifenow);
        
        System.out.printf("%s attacks %s with %d damage. %s's health is now %d\n", k.GetName(), GetName(), life, GetName(), yalifenow);
        
    }
    
    
    public String toString(){
        
        String output;
        output= "Knight Name: " + GetName() + "\n"
        + "Knight Health: " + GetHealth() + "\n"
        + "Knight Weapon: " + GetWeapon() + "\n"
        + "Knight Armor: "  + GetArmor()  + "\n";
        
        return output;
        
        //JOptionPane.showMessageDialog(null, output);
    }
    
   
    
}

