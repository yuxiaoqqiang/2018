package example;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.util.Scanner;
/**
 * Maze Game
 *
 * INFO1103 Assignment 2 
 * 2017 Semester 1
 *
 * The Maze Game.
 * In this assignment you will be designing a maze game.
 * You will have a maze board and a player moving around the board.
 * The player can step left, right, up or down.
 * However, you need to complete the maze within a given number of steps.
 *
 * As in any maze, there are walls that you cannot move through. If you try to
 * move through a wall, you lose a life. You have a limited number of lives.
 * There is also gold on the board that you can collect if you move ontop of it.
 *
 * Please implement the methods provided, as some of the marks are allocated to
 * testing these methods directly.
 *
 * @author YOU :)
 * @date April, 2017
 *
 */
public class MazeGame {
	
    /* You can put variables that you need throughout the class up here.
     * You MUST INITIALISE ALL of these class variables in your initialiseGame
     * method.
     */

    // A sample variable to show you can put variables here.
    // You would initialise it in initialiseGame method.
    // e.g. Have the following line in the initialiseGame method.
    // sampleVariable = 1;
    static int sampleVariable;
    static int live;
    static int step;
    static int gold;
    static int line;
    static String[] board;
    
    static int playerx;
    static int playery;
    static int desx;
    static int desy;
    
    /**
     * Initialises the game from the given configuration file.
     * This includes the number of lives, the number of steps, the starting gold
     * and the board.
     *
     * If the configuration file name is "DEFAULT", load the default
     * game configuration.
     *
     * NOTE: Please also initialise all of your class variables.
     *
     * @args configFileName The name of the game configuration file to read from.
     * @throws IOException If there was an error reading in the game.
     *         For example, if the input file could not be found.
     */
    public static void initialiseGame(String configFileName) throws IOException {
        // TODO: Implement this method.
    	readTxtFile(configFileName);
    	/*
    	3 20 0 4
		#@ ##  &4#
		##  # ## #
		###  3#
		#######  #
		*/
    }

    /**
     * Save the current board to the given file name.
     * Note: save it in the same format as you read it in.
     * That is:
     *
     * <number of lives> <number of steps> <amount of gold> <number of rows on the board>
     * <BOARD>
     *
     * @args toFileName The name of the file to save the game configuration to.
     * @throws IOException If there was an error writing the game to the file.
     */
    public static void saveGame(String toFileName) throws IOException {
        // TODO: Implement this method.
    	String state = "";
    	state = live + " " + step + " " + gold + " " + line;
    	File file = new File(toFileName);
        if (!file.isFile() || !file.exists()) {
        	System.out.println("Error: Could not save the current game configuration to " + "toFileName");
        	return;
        }
    	writeTxtToFile(state, toFileName);
    	int i = 0;
    	for(i = 0; i < line; i++){
    		writeTxtToFile(board[i], toFileName);
    	}
    	System.out.println("Successfully saved the current game configuration to '" + toFileName + "'.");
    
    }

    /**
     * Gets the current x position of the player.
     *
     * @return The players current x position.
     */
    public static int getCurrentXPosition() {
        // TODO: Implement this method.
		
		
        return 0;
    }

    /**
     * Gets the current y position of the player.
     *
     * @return The players current y position.
     */
    public static int getCurrentYPosition() {
        // TODO: Implement this method.
		
        return 0;
    }

    /**
     * Gets the number of lives the player currently has.
     *
     * @return The number of lives the player currently has.
     */
    public static int numberOfLives() {
        // TODO: Implement this method.
        return 0;
    }

    /**
     * Gets the number of remaining steps that the player can use.
     *
     * @return The number of steps remaining in the game.
     */
    public static int numberOfStepsRemaining() {
        // TODO: Implement this method.
        return 0;
    }

    /**
     * Gets the amount of gold that the player has collected so far.
     *
     * @return The amount of gold the player has collected so far.
     */
    public static int amountOfGold() {
        // TODO: Implement this method.
        return 0;
    }


    /**
     * Checks to see if the player has completed the maze.
     * The player has completed the maze if they have reached the destination.
     *
     * @return True if the player has completed the maze.
     */
    public static boolean isMazeCompleted() {
        // TODO: Implement this method.
    	if(playerx == desx && playery == desy && step >= 0)
    		return true;
        return false;
    }

    /**
     * Checks to see if it is the end of the game.
     * It is the end of the game if one of the following conditions is true:
     *  - There are no remaining steps.
     *  - The player has no lives.
     *  - The player has completed the maze.
     *
     * @return True if any one of the conditions that end the game is true.
     */
    public static boolean isGameEnd() {
    	if(isMazeCompleted() == true){
    		System.out.println("Congratulations! You completed the maze!");
    		System.out.println("Your final status is:");
    		printStatus();
    		return true;
    	}
    	if(step == 0 && live != 0){
    		System.out.println("Oh no! You have no steps left.");
    		System.out.println("Better luck next time!");
    		return true;
    	}	
    	else if(live == 0 && step != 0){
    		System.out.println("Oh no! You have no lives left.");
    		System.out.println("Better luck next time!");
    		return true;
    	}
    	else if(live == 0 && step == 0){
    		System.out.println("Oh no! You have no lives and no steps left.");
    		System.out.println("Better luck next time!");
    		return true;
    	}
    	return false;
        // TODO: Implement this method.
       
    }

    /**
     * Checks if the coordinates (x, y) are valid.
     * That is, if they are on the board.
     *
     * @args x The x coordinate.
     * @args y The y coordinate.
     * @return True if the given coordinates are valid (on the board),
     *         otherwise, false (the coordinates are out or range).
     */
    public static boolean isValidCoordinates(int x, int y) {
        // TODO: Implement this method.
    	if((x >= 0 && x < board[0].length()) && (y >= 0 && y < line)){
    		return true;
    	}
        return false;
    }

    /**
     * Checks if a move to the given coordinates is valid.
     * A move is invalid if:
     *  - It is move to a coordinate off the board.
     *  - There is a wall at that coordinate.
     *  - The game is ended.
     *
     * @args x The x coordinate to move to.
     * @args y The y coordinate to move to.
     * @return True if the move is valid, otherwise false.
     */
    public static boolean canMoveTo(int x, int y) {
        // TODO: Implement this method.
    	if(isValidCoordinates(x, y)){
    		if(board[y].charAt(x) != '#')
    			return true;
    	}
        return false;
    }

    /**
     * Move the player to the given coordinates on the board.
     * After a successful move, it prints "Moved to (x, y)."
     * where (x, y) were the coordinates given.
     *
     * If there was gold at the position the player moved to,
     * the gold should be collected and the message "Plus n gold."
     * should also be printed, where n is the amount of gold collected.
     *
     * If it is an invalid move, a life is lost.
     * The method prints: "Invalid move. One life lost."
     *
     * @args x The x coordinate to move to.
     * @args y The y coordinate to move to.
     */
    public static boolean moveTo(int x, int y) {
        // TODO: Implement this method.
    	step--;
    	if(!canMoveTo(x,y)){
    		live--;
    		System.out.println("Invalid move. One life lost.");
    		return false;
    	}
    	else{
    		System.out.println("Moved to (" + x + ", " + y +").");
    		if(board[y].charAt(x) > '0' && board[y].charAt(x) <= '9'){
    			gold += (board[y].charAt(x)-'0');
    			System.out.println("Plus " + (board[y].charAt(x)-'0') +" gold.");
    		}
    		return true;
    	}
    }

    /**
     * Prints out the help message.
     */
    public static void printHelp() {
        // TODO: Implement this method.
    	System.out.println("Usage: You can type one of the following commands.");
    	System.out.println("help         Print this help message.");
    	System.out.println("board        Print the current board.");
    	System.out.println("status       Print the current status.");
    	System.out.println("left         Move the player 1 square to the left.");
    	System.out.println("right        Move the player 1 square to the right.");
    	System.out.println("up           Move the player 1 square up.");
    	System.out.println("down         Move the player 1 square down.");
    	System.out.println("save <file>  Save the current game configuration to the given file.");
    }

    /**
     * Prints out the status message.
     */
    public static void printStatus() {
        // TODO: Implement this method.
    	System.out.println("Number of live(s): " + live);
    	System.out.println("Number of step(s) remaining: " + step);
    	System.out.println("Amount of gold: " + gold);
    }

    /**
     * Prints out the board.
     */
    public static void printBoard() {
        // TODO: Implement this method.
    	int i;
    	for(i = 0; i < line; i++){
    		System.out.println(board[i]);
    	}
    }

    /**
     * Performs the given action by calling the appropriate helper methods.
     * [For example, calling the printHelp() method if the action is "help".]
     *
     * The valid actions are "help", "board", "status", "left", "right",
     * "up", "down", and "save".
     * [Note: The actions are case insensitive.]
     * If it is not a valid action, an IllegalArgumentException should be thrown.
     *
     * @args action The action we are performing.
     * @throws IllegalArgumentException If the action given isn't one of the
     *         allowed actions.
     */
    public static void performAction(String action) throws IllegalArgumentException {
        // TODO: Implement this method.
    	String[] arr = action.split("\\s+");
    	arr[0] = exChange(arr[0]);
    	if(arr.length == 1){
	    	switch(arr[0]){
	    		case "help":
	    			printHelp();
	    			break;
	    		case "board":
	    			printBoard();
	    			break;
	    		case "status":
	    			printStatus();
	    			break;
	    		case "left":
	    			if(moveTo(playerx-1, playery)){
	    				playerx--;
	    				upDate(arr[0]);
	    			}
	    			break;
	    		case "right":
	    			if(moveTo(playerx+1, playery)){
	    				playerx++;
	    				upDate(arr[0]);
	    			}
	    			break;
	    		case "up":
	    			if(moveTo(playerx, playery-1)){
	    				playery--;
	    				upDate(arr[0]);
	    			}
	    			break;
	    		case "down":
	    			if(moveTo(playerx, playery+1)){
	    				playery++;
	    				upDate(arr[0]);
	    			}
	    			break;
	    		default:
	    			System.out.println("Error: Could not find command '" + action + "'.");
	    			System.out.println("To find the list of valid commands, please type 'help'.");
	    	}
    		
    	}
    	else{
    		if(arr[0].equals("save") && arr.length == 2){
				try {
					saveGame(arr[1]);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
    		}
    		else{
    			System.out.println("Error: Could not find command '" + action + "'.");
    			System.out.println("To find the list of valid commands, please type 'help'.");
    		}
    	}
    }

    /**
     * The main method of your program.
     *
     * @args args[0] The game configuration file from which to initialise the
     *       maze game. If it is DEFAULT, load the default configuration.
     */
    public static void main(String[] args) {
        // Run your program (reading in from args etc) from here.
    	String order = null;
    	if(args.length == 0){
    		System.out.println("Error: Too few arguments given. Expected 1 argument, found 0.");
    		System.out.println("Usage: MazeGame [<game configuration file>|DEFAULT]");
    		System.exit(0);
    	}
    	else if(args.length > 1){
    		System.out.println("Too many arguments given. Expected 1 argument, found " + args.length + ".");
    		System.out.println("Usage: MazeGame [<game configuration file>|DEFAULT]");
    		System.exit(0);
    	}
    	if(args[0].equals("DEFAULT")){
    		live = 3;
    		step = 20;
    		gold = 0;
    		line = 4;
    		board = new String[line];
    		board[0] = "#@ ##  &4#";
    		board[1] = "##  # ## #";
    		board[2] = "###  3#   ";
    		board[3] = "#######  #";
    		playerx = 7;
    		playery = 0;
    		desx = 1;
    		desy = 0;
    	}
    	else{
    		try {
    			initialiseGame(args[0]);
    		} catch (IOException e) {
    			// TODO Auto-generated catch block
    			e.printStackTrace();
    		}
    	}
    	Scanner sc = new Scanner(System.in);
    	while(true){
    		try{
		    	order = sc.nextLine();
		    	if(!order.equals(""))
		    		performAction(order);
		    	if(isGameEnd())
		    		break;
    		}catch(Exception e){
    			System.out.println("You did not complete the game.");
    			System.exit(0);
    		}
    	}
    	sc.close();
    }
 
    public static void writeTxtToFile(String strcontent, String toFileName) {
        String strContent = strcontent + "\r\n";
        try {
            File file = new File(toFileName);
            RandomAccessFile raf = new RandomAccessFile(file, "rwd");
            raf.seek(file.length());
            raf.write(strContent.getBytes());
            raf.close();
        } catch (IOException e) {
        	e.printStackTrace();
        }
    }
    
    
    public static void readTxtFile(String filePath){
        try {
            String encoding="UTF-8";
            File file=new File(filePath);
            if(file.isFile() && file.exists()){ 
                InputStreamReader read = new InputStreamReader(
                new FileInputStream(file),encoding);
                BufferedReader bufferedReader = new BufferedReader(read);
                String lineTxt = null;
                int i = 0;
                int j = 0;
                while((lineTxt = bufferedReader.readLine()) != null){
                	if(i == 0){
	                	String [] arr = lineTxt.split("\\s+");
	                	live = Integer.parseInt(arr[0]);
	                	step = Integer.parseInt(arr[1]);
	                	gold = Integer.parseInt(arr[2]);
	                	line = Integer.parseInt(arr[3]);
	                	board = new String[line];
                	}
                	else{
                		board[i-1] = lineTxt;
                		for(j = 0; j < board[i-1].length(); j++){
                			if(board[i-1].charAt(j) == '&'){
                				playerx = j;
                				playery = i-1;
                			}
                			else if(board[i-1].charAt(j) == '@'){
                				desx = j;
                				desy = i-1; 
                			}
                		}
                	}
                	i++;
                }
                read.close();
	        }else{
	            System.out.println("Could not load the game configuration from '" + filePath + "'.");
	        }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static void upDate(String des){
    	StringBuilder strBuilder;
		StringBuilder strBuilder2;
    	switch(des){
    		case "up":
    			strBuilder = new StringBuilder(board[playery]);
    			strBuilder2 = new StringBuilder(board[playery+1]);
    			strBuilder.setCharAt(playerx,'&');
    			strBuilder2.setCharAt(playerx,'.');
    			board[playery] = strBuilder.toString();
    			board[playery+1] = strBuilder2.toString();
    			break;
    		case "down":
    			strBuilder = new StringBuilder(board[playery]);
    			strBuilder2 = new StringBuilder(board[playery-1]);
    			strBuilder.setCharAt(playerx,'&');
    			strBuilder2.setCharAt(playerx,'.');
    			board[playery] = strBuilder.toString();
    			board[playery-1] = strBuilder2.toString();
    			break;
    		case "left":
    			strBuilder = new StringBuilder(board[playery]);
    			strBuilder.setCharAt(playerx,'&');
    			strBuilder.setCharAt(playerx+1,'.');
    			board[playery] = strBuilder.toString();
    			break;
    		case "right":
    			strBuilder = new StringBuilder(board[playery]);
    			strBuilder.setCharAt(playerx,'&');
    			strBuilder.setCharAt(playerx-1,'.');
    			board[playery] = strBuilder.toString();
    			break;	
    	}
    }
    
    public static String exChange(String str){  
        StringBuffer sb = new StringBuffer();  
        if(str!=null){  
            for(int i=0;i<str.length();i++){  
                char c = str.charAt(i);  
                if(Character.isUpperCase(c)){  
                    sb.append(Character.toLowerCase(c));  
                }
                else{
                	sb.append(c);
                }
            }  
        }  
          
        return sb.toString();  
    }  
}