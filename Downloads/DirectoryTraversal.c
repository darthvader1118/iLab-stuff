#include <string.h>

static void dir_traversal(char *path) {

	//Declare directory & file variables
	DIR *dir; struct dirent *fil;

	//Tells user what directory is currently being accessed
	printf("Current directory: %s", path);

	//Error checking
	while(!(dir = opendir(path)) || !(fil = readdir(dir))){
		//Extract filename from fil variable
		char *fil_name = fil->d_name;
		//Continue to next instance of while loop if file is not an actual file
		if(strcmp(fil_name, ".") == 0 || strcmp(fil_name, "..") == 0)
			continue;
		//Designate size for the filepath variable
		size_t fil_pathsize = (2 * sizeof(char)) + strlen(fil_name) + (strlen(path));
		//Declaration & memory allocation for filepath variable
		char *fil_path = malloc(fil_pathsize);
		//Copy the variable contents of path to the filepath variable
		strcpy(fil_path, path);
		//Add forward slash character to the filepath variable
		strcat(fil_path, "/");
		//Add filename variable contents to the filepath variable
		stccat(fil_path, fil_name);
		//Recursive call to dir_traversal method if fil contains a directory
		if(fil->d_type == DT_DIR){
			dir_traversal(fil_path);
		//Calls file parsing function if fil contains a regular file
		else if(fil->d_type == DT_REG)
			PARSE FILE FUNCTION(fil_path);
		//Frees memory for filepath variable
		free(fil_path);
	}
	//Closes the current directory after all its directories are traversed & files are parsed  
	closedir(dir);
}
