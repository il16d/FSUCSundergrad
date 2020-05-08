/**
 * Lopez Tobi, Iho
 * COP-3252
 * Assignment 3
 * Date January 24th 2020
 * Stars class
 */



import javax.swing.JOptionPane;

public class Stars {

	private int rows;
	private int columns;
	private String Skycharacter;
	private String Sky;

	public Stars() {
		
        //rows=10; // this will not allow for user input to change
        //columns=10; // ^^same as above T.T
        //rows = setRows(); // will not work because these are void funcs duhhhh
        //columns = setColumns(); // same!!! omg
        this.setRows();
        this.setColumns();
        
		Skycharacter= "*";
	}


    
    public String getSky()
    {
        buildSky();
        return Sky;
    }
    
    public int getRows()
    {
        return rows;
    }
    
    public int getColumns()
    {
        return columns;
    }
    
    
	public void setRows()
	{
       
        rows = Integer.parseInt(JOptionPane.showInputDialog(
                                                            "Rows of stars?", "10"));
        
	}

	public void setColumns()
	{
        columns = Integer.parseInt(JOptionPane.showInputDialog(
                                                               "Columns of stars?", "10"));
	}

	public String buildSky()
	{
		Sky = "";

		for (int j = 0; j < getRows(); j++)
		{
			if (j % 2 == 1)
				Sky = Sky + " ";

			for (int i = 0; i < getColumns(); i++)
			{
				Sky = Sky + Skycharacter + " ";
			}
			Sky = Sky + "\n";
		}
        return Sky;}
    

public String printStars()
    {
		return buildSky();
		
      
	}
}
