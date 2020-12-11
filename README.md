# minishell42
## Contributors

 - Omar BOUYKOURNE &nbsp;&nbsp;@su-omb &nbsp;	:   42login => `obouykou`
 - Yassin SLATI &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;@sltyassin&nbsp;&nbsp;: 	42login => `yslati`

## Subject

[minishell_subject](https://github.com/su-omb/minishell42/blob/main/en.subject.pdf)

## How to run

 1.  `make`  
 2.  `./minishell`
 3.  Run your commands

## Simple shell that behaves like bash and contains these commands built-in :

 1.  `echo` with option `-n`.   
 2.  `cd` with only a relative or absolute path.
 3.  `pwd` without any options.
 4.  `export` without any options.
 5.  `unset` without any options.
 6.  `env` without any options and any arguments.
 7.  `exit` without any options.

## and works with these delimiters :

 - Semicolon `;` in the command separates commands like in bash.
 -  Single quotes `'` and double quotes `"` work like in bash except for multiline commands.
 - Redirections `<` `>` `>>` work like in bash except for file descriptor aggregation.
 - Pipes `|` work like in bash.
 - Backslash `\` work like in bash.
 - Environment variables (`$` followed by characters) work like in bash.
 - `$?` work like in bash.
 - `ctrl-C`, `ctrl-D` and `ctrl-\` have the same result as in bash.

## Some Sources :

 - [Writing your own shell fundamentals](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
 - [Shell System Calls Signals](https://cdn.discordapp.com/attachments/769898609562746880/776363294013128734/Shells_SystemCalls_Signals.ppt)
 - [How does copy-on-write work in fork?](https://stackoverflow.com/questions/27161412/how-does-copy-on-write-work-in-fork?rq=1)
 - [ Building a Bash-like application](https://medium.com/@ssreehari/building-a-bash-like-application-e17122609be4)
 - [ execve() linux man](https://linux.die.net/man/2/execve)
 - [exit command status](https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/)


## NB:

 - Please, if you have other useful sources, you can send them to me, and thanks in advance.
 - Maybe you will find some special cases that doesn't work, please report if there are any.
