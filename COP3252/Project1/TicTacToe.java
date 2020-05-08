/*
 *
 * Lopez Tobi, Iho
 * COP-3252
 * Project 1
 * Date March 9th 2020
 *
 */

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Color;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;



// https://cs.fit.edu/~mmahoney/cis5200/TicTacToe.java
// https://www.javacodegeeks.com/2012/02/java-swing-tic-tac-toe.html


public class TicTacToe implements ActionListener{
	
	private JButton buttons[] = new JButton[9];
	private int turnCount = 0;
	
	private int[][] winCombo = new int[][]{
			{0,1,2},{3,4,5},{6,7,8},
			{0,3,6},{1,4,7},{2,5,8},
			{0,4,8},{2,4,6}
	};
	private boolean win = false;
	private boolean AI = false;
	
	public TicTacToe(){
		JFrame window = new JFrame();
		setUpWindow(window);
		
		for(int i = 0; i < 9; ++i)
			buttons[i].addActionListener(this);
		int dialogueButton = JOptionPane.YES_NO_OPTION;
		int dialogueResult = JOptionPane.showConfirmDialog(null, "Play against computer?",null, dialogueButton);
		if(dialogueResult == JOptionPane.YES_OPTION)
			AI = true;
	}
	
	private void setUpWindow(JFrame window){
		
		
		JPanel grid = new JPanel();
		
		JLabel title = new JLabel("FSU");
        title.setOpaque(true);
        title.setBackground(Color.darkGray);
		title.setHorizontalAlignment(SwingConstants.CENTER);
        
		JLabel footer = new JLabel("Iho Lopez Tobi");
        footer.setOpaque(true);
        footer.setBackground(Color.lightGray);
        
		footer.setHorizontalAlignment(SwingConstants.CENTER);
        grid.setBackground(Color.darkGray);
		
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		grid.setLayout(new GridLayout(3,3));
		for(int i = 0; i < 9; ++i){
			buttons[i] = new JButton();
			grid.add(buttons[i]);
		}
		
		window.add(title, BorderLayout.PAGE_START);
		window.add(grid, BorderLayout.CENTER);
		window.add(footer, BorderLayout.PAGE_END);
		window.setSize(300,300);
		window.setVisible(true);
       
        //window.setBackground(Color.white);
	}
	
	public static void main(String[] args){
		new TicTacToe();
	}
    
    

	public void actionPerformed(ActionEvent arg0) {
		String letter = "";
		if(turnCount % 2 == 0)
			letter = "X";
		else	
			letter = "O";
		
		JButton pressedButton = (JButton) arg0.getSource();
		pressedButton.setText(letter);
		pressedButton.setEnabled(false);
		
        
		
		for(int i = 0; i < 8; ++i){
			if(buttons[(winCombo[i][0])].getText() == buttons[(winCombo[i][1])].getText() &&
			   buttons[(winCombo[i][1])].getText() == buttons[(winCombo[i][2])].getText() &&
			   buttons[(winCombo[i][0])].getText() != ""){
				win = true;
			}
		}
		++turnCount;
		
		JFrame window = (JFrame) SwingUtilities.windowForComponent(pressedButton);
		if(win){
			
			playAgain(window, letter + " wins!");
		} else if(!win && turnCount == 9){
			playAgain(window, "Tie Game!");
		}
		
		if(AI && (turnCount % 2) == 1 && !win){
			boolean clicked = false;
			
			for(int index = 0; index < 8; ++index){
				if(buttons[(winCombo[index][0])].getText() == buttons[(winCombo[index][1])].getText() && buttons[(winCombo[index][0])].getText() != ""){
					if(buttons[(winCombo[index][2])].isEnabled()){
						buttons[(winCombo[index][2])].doClick();
						clicked = true;
					}
					break;
				} else if(buttons[(winCombo[index][1])].getText() == buttons[(winCombo[index][2])].getText() && buttons[(winCombo[index][1])].getText() != ""){
					if(buttons[(winCombo[index][0])].isEnabled()){
						buttons[(winCombo[index][0])].doClick();
						clicked = true;
					}
					break;
				} else if(buttons[(winCombo[index][0])].getText() == buttons[(winCombo[index][2])].getText() && buttons[(winCombo[index][0])].getText() != ""){
					if(buttons[(winCombo[index][1])].isEnabled()){
						buttons[(winCombo[index][1])].doClick();
						clicked = true;
					}
					break;
				} 
			}
			
			if(!clicked){
				
				int max = 8;
				int seed = (int)(Math.random() * max);
				for(int i = 0; i < 9; ++i){
					if(buttons[seed+i].isEnabled()){
						buttons[seed+i].doClick();
						clicked = true;
						break;
					}	
				}
			}
		}
	}
    
	
	public void playAgain(JFrame window, String message){
		int dialogueButton = JOptionPane.YES_NO_OPTION;
		int dialogueResult = JOptionPane.showConfirmDialog(null, message + "\nWould you like to play again?",null, dialogueButton);
		if(dialogueResult == JOptionPane.YES_OPTION){
			window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			window.setVisible(false);
			window.dispose();
			new TicTacToe();
		} else {
			window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			window.setVisible(false);
			window.dispose();
		}
	}
}
