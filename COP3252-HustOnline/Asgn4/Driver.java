/*
 *
 * Lopez Tobi, Iho
 * COP-3252
 * Assignment 4
 * Date February 9th 2020
 *
 */



import java.util.*;


public class Driver{
    
    
    private static Random randm = new Random();
    
    private static Knight Javalot = new Knight();
    private static Knight Sir = new Knight();
    
    
    private static boolean done = false;
    
    public static void main (String[] args) {
        
        while (!done)
        {
            Scanner in = new Scanner(System.in);
            
            System.out.print("Welcome to Knight Fight");
            System.out.print("\n");
            
            Knight Javalot = newKnight();
            
            System.out.print("Auto generated opinent? Please enter Y or N: ");
            System.out.print("\n");
            
            String choice = in.nextLine();
            
            switch(choice)
            {
                case "y":
                    Sir = new Knight();
                    break;
                case "n":
                    Sir = newKnight();
                    break;
                case "Y":
                    Sir = new Knight();
                case "N":
                    Sir = newKnight();
            }
            
            System.out.printf( Javalot.toString() );
            System.out.printf("\n\n          VS.\n\n");
            System.out.printf( Sir.toString() );
            
            System.out.printf("Enter fight to start fight, enter exit to end: ");
            choice = in.nextLine();
            
            switch(choice) {
                case "fight":
                    Knight winner = Fight(Javalot, Sir);
                    Winner(winner);
                    break;
                case "exit":
                    break;
            }
            System.out.printf("To play again enter play, to exit enter exit: ");
            choice = in.nextLine();
            switch(choice) {
                case "play":
                    break;
                case "exit":
                    done = true;
                    break;
            }
        }
    }
    
    
public static Knight newKnight () {
        
        Scanner in = new Scanner(System.in);
        
        System.out.printf("Enter the Knight's name: ");
        String name = in.nextLine();
        
        System.out.printf("Knights weapon: \n");
        System.out.printf("1) Long Sword\n");
        System.out.printf("2) Battle Axe\n");
        System.out.printf("3) Spear\n");
        System.out.printf("4) Warhammer\n");
        System.out.printf("Your choice my liege? : ");
        
        int choice = in.nextInt();
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
    System.out.printf("Select armor: \n");
    System.out.printf("1) Leather\n");
    System.out.printf("2) Metal\n");
    System.out.printf("Your choice my liege? : ");
    choice = in.nextInt();
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
    
public static void Winner (Knight k) {
        System.out.printf("\n\n    THE WINNER IS:\n");
        System.out.printf( k.toString() );
    }
    
public static Knight Fight (Knight kn1, Knight kn2) {
    
        Knight[] randomChoice = new Knight[2];
        randomChoice[0] = kn1;
        randomChoice[1] = kn2;
        
        Knight turn = randomChoice[ randm.nextInt(2) ];
        
        Knight flag;
        if( turn == kn1 )
            flag = kn2;
        else
            flag = kn1;
        
        Knight winner;
        
        while(kn1.GetHealth() > 0 && kn2.GetHealth() > 0) {
            flag.fight(turn);
            
            
            if (turn == kn1 && flag == kn2) {
                turn = kn2;
                flag = kn1;
            }
            else if (turn == kn2 && flag == kn1) {
                turn = kn1;
                flag = kn2;
            }
        }
        
        if ( kn1.GetHealth() <= 0 )
            winner = kn2;
        else
            winner = kn1;
        
        return winner;
    }
    
    
   
    
    
    
    
}
