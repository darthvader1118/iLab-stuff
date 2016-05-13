/*prints all the files associated with any word*/
int so(char *str, hashTable *ht) {
  char *word;
  FileNode *fptr; /* Iterates through filenames  */

  if (strcmp(strtok(str, " "), "so") != 0) {
    printf("I did not get 'so' inside sa function!!\n");
    return 1;
  }

  /* goes through each word in input */
  while ((word = strtok(NULL, " "))) {
    for (ptr = getFiles(word, root); ptr != NULL;
        ptr = ptr->next) {
      insert_to_list(t, ptr->filename);
    }
  }

  /* Means we got no matches */
  if (t->files == NULL) {
    printf("No matches found.\n");
    destroyTree(t);
    return 1;
  }

  /* prints all the filenames */
  for (ptr = t->files; ptr->next != NULL; ptr = ptr->next)
    printf("%s, ", ptr->filename);
  if (ptr)
    printf("%s\n", ptr->filename);

  destroyTree(t);
  return 0;
}

/*prints all the files associated with ALL the words*/
int sa(char *str, tnode root) {
  char *word;
  int count = 0;
  lnode ptr; /* Iterates through filenames  */
  tnode t = create_tnode(); /*lets us keep a list*/

  if (strcmp(strtok(str, " "), "sa") != 0) {
    return 1;
  }


  /* goes through each word in input */
  while ((word = strtok(NULL, " "))) {
    /* goes through each filename for associated word */
    for (ptr = getFiles(word, root); ptr != NULL;
        ptr = ptr->next) {
      insert_to_list(t, ptr->filename);
    }
    count++;
  }



  /* prints all the filenames */
  for (ptr = t->files; ptr != NULL && ptr->count != count; ptr = ptr->next);
  if (ptr != NULL) {
    printf("%s", ptr->filename);
    for (ptr = ptr->next; ptr != NULL; ptr = ptr->next) {
      if(ptr->count == count)
        printf(", %s", ptr->filename);
    }
    printf("\n");
  }
  else {
    printf("No matches found\n");
  }

  destroyTree(t);
  return 0;
}
