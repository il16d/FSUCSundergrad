/**
 * Lopez Tobi, Iho
 * COP-3252
 * Assignment 3
 * Date January 24th 2020
 * Knights class
 */



import javax.swing.JOptionPane;

public class Knight
{
	private String name;
	private int health;
	private int battles;
	private int age;
	private int gold;
	private Stars star;
	
	public Knight()
	{
        name = "Mister";
        health = 100;
        battles = 0;
        age = 9;
        gold = 0;
        star = new Stars(); //
	}
	
    public String GetName()
    {
        return name;
    }
    public int GetHealth()
    {
        return health;
    }
    public int GetBattles()
    {
        return battles;
    }
    public int GetAge()
    {
        return age;
    }
    public int GetGold()
    {
        return gold;
    }
    public Stars GetStars()
    {
        return star;
    }
    
    
    public void getUserInput(){
       
        
        SetName(JOptionPane.showInputDialog(
                                            "Enter your Knight's name", "Sir Jav-a-lot"));
        
        SetHealth(Integer.parseInt(JOptionPane.showInputDialog(
                                                               "How healty is " + name + " ?", "94")));
        
        SetBattles(Integer.parseInt(JOptionPane.showInputDialog(
                                                                   "How many battles has " + name + " won?", "6")));
        
        SetAge(Integer.parseInt(JOptionPane.showInputDialog(
                                                            "How old is " + name + "?", "9")));
        
        SetGold(Integer.parseInt(JOptionPane.showInputDialog(
                                                               "How much gold has " + name + " looted?", "1234")));
    }
    
	public void SetName(String Name)
	{
		
        name = Name;
	}
	
	public void SetHealth( int Health)
	{
        health = Health;
	}
	
	public void SetBattles(int Battles)
	{
        battles = Battles;
	}
	
	public void SetAge(int Age)
	{
        age = Age;
	}
	
	public void SetGold(int Gold)
	{
        gold = Gold;
	}
	
	public void SetStars()
	{
		star = new Stars();
	}
	
	
	// **END OF SET AND GET METHODS**
	
    
    public void PopupOutput(){
        
        String output;
        output= "Knight Name: " + GetName() + "\n"
        + "Knight Health: " + GetHealth() + "\n"
        + "Knight Battles: " + GetBattles() + "\n"
        + "Knight Age: " + GetAge() + "\n"
        + "Knight Gold: " + GetGold() + "\n"
        + star.printStars();
        
        JOptionPane.showMessageDialog(null, output);
    }
    
	public void exit()
	{
		JOptionPane.showMessageDialog(null, "Kamelot awaits! ",
				GetName(), 1);
	}
	
}
