/* ------- file: -------------------------- options.c ---------------

       Version:       rh2.0
       Author:        Han Uitenbroek (huitenbroek@nso.edu)
       Last modified: Wed Mar 25 14:46:56 2009 --

       --------------------------                      ----------RH-- */

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "rh.h"
#include "error.h"
#include "inputs.h"


#define PROCLOGFILE "scratch/procLog_cpu-%06d_%s.txt"



/* --- Function prototypes --                          -------------- */


/* --- Global variables --                             -------------- */

extern CommandLine commandline;
extern char messageStr[];




/* ------- begin -------------------------- setOptions.c ------------ */

void setOptions(int argc, char *argv[], int iproc, int quiet)
{
  const  char routineName[] = "setOptions";
  static char logfileName[MAX_LINE_SIZE], wavetable[MAX_LINE_SIZE];
    
  int Noption;
  
  
  Option theOptions[] = {
    {"help", 1, FALSE, "", NULL, NULL, "Prints this message"},
    {"input", 1, TRUE, "keyword.input",
       commandline.keyword_input,
       setcharValue, "File name for input keywords"},
    {"logfile", 1, TRUE, "",
       logfileName,
       setcharValue, "File name log file"},
    {"quiet", 1, FALSE, "FALSE", &commandline.quiet, setboolValue,
       "Turns off warning messages"},
    {"showkeywords", 1, FALSE, "FALSE", &commandline.showkeywords,
       setboolValue,
       "Show keyword values with current keyword input file"}
  };
  Noption = sizeof(theOptions) / sizeof(Option);

  parse(argc, argv, Noption, theOptions);
  sprintf(logfileName, PROCLOGFILE, iproc,getenv("USER"));
  strcpy(commandline.logfileName, logfileName);
  if(quiet) commandline.quiet = TRUE;
  
  
  if (strlen(logfileName) > 0) {
    if(!commandline.quiet){
      
      if ((commandline.logfile = fopen(logfileName, "w")) == NULL) {
	sprintf(messageStr, "Unable to open log file %s", logfileName);
	Error(ERROR_LEVEL_2, routineName, messageStr);
      }
      setvbuf(commandline.logfile, NULL, _IOLBF, BUFSIZ);
    }
  } else
    commandline.logfile = stderr;

  commandline.wavetable = (strlen(wavetable) > 0) ? wavetable : NULL;
}
/* ------- end ---------------------------- setOptions.c ------------ */
