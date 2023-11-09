# Linux-Shell


## **System Description:**

The shell a software which is used to execute commands which are used to communicate with the system. It is mostly used execute operations/instructions on files and directories. We pass in commands and their arguments and internally the system calls the ‘system()’ function to execute them. It creates threads/forks in order to execute the commands while running the main shell.
In this Assignment, we have execute commands using fork()/exec() as well as threads()/system() families of functions.

## **Assumptions:**  

1. There are only two flags which are implemented per command.  
2. The flags must be specified immediately after the command, e.g., ‘rm -i filename’ is legal however ‘rm filename -i’ is not legal.  
3. Home directory is ‘/home/js’ .  
4. Printing files in column format along with their file numbers (arbitrary) is allowed.  
5. Special character interpretation of strings in echo is disabled.  
6. There are no flags for pwd.  
7. Blank spaces ‘ ‘ are treated as arguments to provide protection and accuracy, therefore output may change if many unnecessary blank spaces are provided.  
8. Two flags cannot be used simultaneously.
9. ‘ls’ does not print out directories. ‘ls -a’ can be used to view all files including directories.
10. Everything after ‘date’ in the date command can be treated as a flag.
11. Using unnecessary special characters is not allowed. Also putting forward slashes at the end of a command is not allowed, i.e. like, dir/file/, rather dir/file .  

In general, an instruction will look like the following:  
**<command/command&t> [-flag] [arguments]**  

**Note:** In order to display that the file is being called through thread/fork, I have printed statements that indicate how the program is being executed before the execution of the program begins.  

**Note:** The file path must be respecified in the ‘shell.c’ file in order for exec() and system() to enable execution of the command file.  

**Note:** Commands can handle multiple arguments however care must be taken to not exceed the malloced memory (around 100).  



### **1. echo**

#### Flags handled:  

-n : does not print a newline.  

–-help : prints out the help page for echo.  



#### Edge Cases:  

1. echo “<string>”  
Doesn’t print out the double quotes.  

2. echo -invalid_flag  
Prints out that the flag is invalid along with the flag.  

3. echo “string” “string1”  
Prints out both the strings.  




### **2. pwd**

#### Flags handled: No flags handled.  

#### Edge Cases:  

1. pwd any_random_string  
Prints the current working directory regardless of what is passed as an argument.  

If we change the directory, pwd works properly.  








### **3. cd**

#### Flags handled:  

.. : changes the working directory to the parent directory of the current directory.  

~ : changes the working directory to the home directory.  

/ : changes the working directory to the root directory.  


#### Edge Cases:  

1. cd  
changes the working directory to the home directory.  


2. cd invalid_location  
Prints out “No such file or directory” along with the directory name that is not found.  





### **4. ls**

#### Flags handled:  

-a : prints out all the files present in the directory.  

-r : prints out the files present in the directory in reverse order.  

#### Edge Cases:  

1. ls invalid_location  
Prints out “Invalid location” along with the directory name that is invalid but works for the valid locations.  

2. ls -invalid_flag  
Prints out “Invalid command” along with the flag that is invalid.  

3. ls  
Prints out all the (regular) files present in the current working directory.  

4. ls filename  
Prints out “Invalid location” as a file is not openable.  








### **5. date**

#### Flags handled:  

-u : prints out the UTC Time  

-I : prints out the date in Indian Standard format, that is, in YYYY/MM/DD  


#### Edge Cases:  

1. date -invalid_flag  
Prints out “Invalid flag” along with the flag that is invalid.  

2. date any_non_flag_string  
Prints out “Invalid flag” as it takes in only a flag and no arguments (that is, everything afer the command ‘date’ is treated as a flag).  

3. date  
When no argument is provided, it prints the date-time of the system.  

**Note:** Date time of the system is set to UTC.  





### **6. cat**

#### Flags handled:  

-n : prints out the number of each line in the file.  

-e : prints a ‘$’ symbol at the end of each line in the file.  


#### Edge Cases:  

1. cat file_doesnt_exist  
Prints out “File not found” along with the filename that is not found.  

2. cat directory1/file1 directory2/file2  
Prints out both files file1 and file2 provided the paths exist. If a path does not exist then, then it is printed out that the path/file does not exist, however the path which does exist will work as normal.  

3. cat -invalid_flag  
Prints out that the flag is invalid along with the flag.  

4. cat directory/ filename  
Since spaces are treated as arguments (to provide protection and accuracy), cat will not be able to read this file as ‘ ‘ will be treated as an invalid path name.  

5. cat  
If no argument is provided then it prints out the same.  

6. cat directory/  
Gracefully ignores this as it was expecting a filename but never got one.  







### **7. mkdir**

#### Flags handled:  

-v : prints out a message informing the user of whether the directory has been created or not.  

-p : allows creation of parent directories as per requirement.  

#### Edge Cases:  

1. mkdir -p directory_exists/directory_doesnt_exist  
This will not throw any errors (that is, if a directory already exists).  

2. mkdir directory_already_exists  
Prints out that the directory was not able to be created (since it already exists).  

3. mkdir -invalid_flag  
Prints out that the flag is invalid along with the flag.  

4. mkdir -p dir1/dir2/  dir3  
Creates the directories properly, however it tells the user that it could not create a directory due to the blank spaces.  

5. mkdir&t -v adir bdir cdir/ddir  
Prevents the last directory from being created but creates the other two directories.  

6. mkdir  
If no argument is provided then it prints out the same.  







### **8. rm**

#### Flags handled:  

-i : Asks the user for confirmation before deleting a file, if ‘y’ is entered then the file is deleted otherwise it is not.  

-v : prints out a message informing the user of whether the file has been deleted or not  


#### Edge Cases:  

1. rm file_doesnt_exist  
Prints out that the file does not exist and therefore could not be deleted  

2. rm directory1/file1 directory2/file2  
Deletes both file1 and file2 from their respective directories provided the paths exist.  
If a path does not exist, then it is printed out that the path does not exist, however the path which does exist will work as normal.  

3. rm -invalid_flag  
Prints out that the flag is invalid along with the flag.  


4. rm directory_name  
Doesn’t allow deletion of directories.  

5. rm directory/ filename  
Since spaces are treated as arguments (to provide protection), rm will not be able to delete this file.  


6. rm  
If no argument is provided then it prints out the same.  




