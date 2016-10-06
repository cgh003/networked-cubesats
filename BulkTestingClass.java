import static org.junit.Assert.assertEquals;

import java.io.File;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

import javax.tools.JavaCompiler;
import javax.tools.ToolProvider;

import org.junit.Before;
import org.junit.Test;

public class BulkTestingClass {
    static String inputDirectory;
    static String outputDirectory;
    static Scanner input;
    static File[] files;
    static ArrayList<String> classNames;
	LifeDShihPeriod7 test;
	
	 static String[] cases = {"3,5,7,8,5,8,0", "3,5,7,8,5,8,1,2,2,7,5,7,1,0", "2,2,6,5,7,4,8,6,8,3,7,4,0", 
		      "8,7,5,3,4,5,2,4,3,6,5,8,5,4,8,7,4,5,8,6,6,8,2,0", "6,6,4,3,2,3,8,6,5,5,5,8,3,7,1,5,3,4,1,0","3,5,7,8,5,8,0,2,4,2,5",
		          "6,4,4,6,6,6,8,6,5,0"};
	 static String[] answer = {"A-11, B-10, C-15", "A-1, B-17, C-7", "A-START, B-16, C-START", 
	          "A-13, B-END, C-START", "A-1, B-START, C-10","A-11, B-10, C-15",
	          "A-5, B-8, C-START"};
	 
	 
	public static void main(String[] args){
		testAll();
	}
	 private static void initialization(){
         input = new Scanner(System.in);
        System.out.println("Enter the path from which to test files from! Format = C:/Users/) ");
        System.out.print("PATH --> ");
        inputDirectory = input.nextLine();
      
        files = new File(inputDirectory).listFiles();
    }
	 
	  public static void extractFiles() {
	        initialization();
	        for (File file : files) {
	        //	 Path source = Paths.get(file.getAbsolutePath());
	        	 classNames.add(file.getName());
	        	// System.out.println(file.getName());
	        }
	        System.out.println("Operation complete");
	  }
	  
	  public static void testAll(){
		  initialization();
		  for(File file : files){
			  try {
				//  File sourceFile = new File("/Library/Java/jdk1.7.0_79.jdk/Contents/Home", file.getPath());
				  JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
				  compiler.run(null, null, null, file.getPath());
				  
				Class<?> amazing = Class.forName(file.getName().substring(0, file.getName().length()-5));
				Constructor<?> constructor = amazing.getConstructor(String.class);
				Object test = constructor.newInstance("file50.txt");
			//	Method method = test.getClass().getMethod("play", String.class);
				Method method = test.getClass().getMethod("displayStore");
				System.out.println("TESTING: " + amazing.getName());
			//	System.out.println("Living in Row 9 ---> " +  method.invoke(test, 9));
				
				method.invoke(test);
		      
			  }catch(Exception e){
				  e.printStackTrace();
			  }
		  }
	  }
	  
	  
	    
	   
	
	

}
