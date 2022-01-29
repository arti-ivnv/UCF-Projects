// Artem Ivanov
// COP4600
// HW 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 1000

// Getting input from the shell
char *getting_in (void)
{
  char *buffer = NULL;
  char str[MAX_ARGS];

  buffer = calloc(MAX_ARGS,sizeof(char));

  printf("# ");
  scanf("%[^\n]%*c", str);

  strcpy(buffer,str);

  if (strlen(buffer) != 0)
  {
    return buffer;
  }
  else
  {
    return NULL;
  }
}

// Splitting an input string into command and arguments
void splitParse (char *in_string, char **parsed)
{
  int i;

  for (i = 0; i < MAX_ARGS; i++)
  {
    parsed[i] = strsep(&in_string, " ");
    if (parsed[i] == NULL)
    {
      break;
    }

    if (strlen(parsed[i]) == 0)
    {
      i--;
    }
  }
}

// Determining if the command is valid or not
// Returns execution code
int commands (char **parsed)
{
  int num_comms = 7;
  char *reserved[100];

  reserved[0] = "movetodir";
  reserved[1] = "whereami";
  reserved[2] = "history";
  reserved[3] = "byebye";
  reserved[4] = "start";
  reserved[5] = "background";
  reserved[6] = "exterminate";

  for(int i = 0; i < num_comms; i++)
  {
    if (parsed[0] == NULL)
    {
      printf("No parrsed [DEB]\n");
      break;
    }

    if (strcmp(reserved[i], parsed[0]) == 0)
    {
      return i;
    }
    else if (strcmp(reserved[i], parsed[0]) != 0 && i == (num_comms - 1))
    {
      return -1;
    }
    else
    {
      continue;
    }
  }
}

// Showing a current directory
void whereami(void)
{
  char directory[1024];
  getcwd(directory, sizeof(directory));
  printf("You are in: %s\n", directory);
  return;
}

// Terminating a shell
void buybuy(void)
{
  exit(0);
}

// Moving in specific directory
void movetodir(char *parsed)
{
  if (chdir(parsed) == 0)
  {
    return;
  }
  else
  {
    printf("Error: Directory '%s' not founded\n", parsed);
  }
}

// Shows history, to erase history use -c as an ardument
void history(char *in_string, char **history_buf, int i)
{
  for (int j = 0; j <= i; j++)
  {
    printf("%s\n", history_buf[j]);
  }
  return;
}

// Kills specific process
void exterminate(char **in_args)
{
  int result = 0;
  pid_t kill_result;

  if (atoi(in_args[1]) == 0)
  {
    printf("ERROR: Improper PID\n");
    return;
  }

  kill_result = kill(atoi(in_args[1]), SIGKILL);

  if (kill_result == 0)
  {
    printf("SUCCESS\n");
  }
  else
  {
    printf("FAIL\n");
  }
}

// Executing a program
void start(char **in_args)
{
  pid_t pid, wpid;
  int result, i = 2, j = 0;
  char *path = in_args[1];
  char *args[MAX_ARGS];

  while(in_args[i] != NULL)
  {
    args[j] = in_args[i];
    i++;
    j++;
  }

  pid = fork();

  if (pid == 0)
  {
    // Child process
    if (execv(path, args) == -1)
    {
      printf("Error: Child process\n");
      return;
    }
    // fork failed
    else if (pid < 0)
    {
      printf("Error: fork failed\n");
      return;
    }
    // Parent process
    else
    {
      do
      {
        wpid = waitpid(pid,&result, WUNTRACED);
      } while(!WIFEXITED(result) && !WIFSIGNALED(result));
    }
  }
}

// runs process, output its PID and return to the promt
void background(char **in_args)
{
  pid_t pid;
  int result, i = 2, j = 0;
  char *path = in_args[1];
  char *args[MAX_ARGS];

  while(in_args[i] != NULL)
  {
    args[j] = in_args[i];
    i++;
    j++;
  }

  pid = fork();

  if (pid == 0)
  {
    // Child process
    if (execv(path, args) == -1)
    {
      printf("Error: Child process\n");
      return;
    }
    // fork failed
    else if (pid < 0)
    {
      printf("Error: fork failed\n");
      return;
    }
    // Parent process
    else
    {
      printf("%d\n", pid);
      return;
    }
  }
}

int main(void)
{
  char *in_string,*in_copy, *in_args[MAX_ARGS], *history_buf[MAX_ARGS];
  int execFlag = 0, exec, i = 0, j = 0;

  *history_buf = calloc(1000, sizeof(char*));
  in_copy = calloc(MAX_ARGS,sizeof(char));

  for(j = 0; j < 1000; j++)
  {
    history_buf[j] = calloc(MAX_ARGS, sizeof(char));
  }

  while (1)
  {
    in_string = getting_in();
    if (in_string != NULL)
    {
      strcpy(in_copy, in_string);
      splitParse(in_string, in_args);
      exec = commands(in_args);

      switch (exec)
      {
        case 0:
          if (in_args[1] == NULL)
          {
            printf("Error: path missing\n");
            printf("Please enter 'movetodir [directory]'\n");
          }
          else
          {
            strcpy(history_buf[i],in_copy);
            movetodir(in_args[1]);
            i++;
          }
          break;
        case 1:
          strcpy(history_buf[i],in_copy);
          whereami();
          i++;
          break;
        case 2:
          strcpy(history_buf[i],in_copy);
          // Checks if we are erasing a history
          if (in_args[1] != NULL)
            {
              if (strcmp(in_args[1],"-c") == 0)
              {
                i = 0;
                break;
              }
              else
              {
                printf("Error: Invalid arg for history\n");
              }
            }
          history(in_string, history_buf,i);
          i++;
          break;
        case 3:
          strcpy(history_buf[i],in_copy);
          buybuy();
          i++;
          break;
        case 4:
          strcpy(history_buf[i],in_copy);
          start(in_args);
          i++;
          break;
        case 5:
          strcpy(history_buf[i],in_copy);
          background(in_args);
          i++;
          break;
        case 6:
          strcpy(history_buf[i],in_copy);
          exterminate(in_args);
          i++;
          break;
        default:
          printf("Error: Command not founded\n");
      }
      continue;
    }
    else
    {
      printf("Error: unfortunately this shell does not support empty lines.\n");
      break;
    }
  }

  return 0;
}
