# minishell42
## Simple shell that behaves like bash and contains these commands built-in :

◦ echo with option ’-n’.  
◦ cd with only a relative or absolute path.  
◦ pwd without any options.  
◦ export without any options.  
◦ unset without any options.  
◦ env without any options and any arguments.  
◦ exit without any options.  

## and works with these delimiters :

• ; in the command separates commands like in bash.  
• ' and " work like in bash except for multiline commands.  
• Redirections < > “>>” work like in bash except for file descriptor aggregation.  
• Pipes | work like in bash.  
• Backslash \ work like in bash.  
• Environment variables ($ followed by characters) work like in bash.  
• $? work like in bash.  
• ctrl-C, ctrl-D and ctrl-\ have the same result as in bash.  

## Some Sources :

https://cdn.discordapp.com/attachments/769898609562746880/776364046945353748/Chapter5-WritingYourOwnShell.pdf.  
https://cdn.discordapp.com/attachments/769898609562746880/776363294013128734/Shells_SystemCalls_Signals.ppt.  
https://stackoverflow.com/questions/27161412/how-does-copy-on-write-work-in-fork?rq=1.  
https://medium.com/@ssreehari/building-a-bash-like-application-e17122609be4.  
https://linux.die.net/man/2/execve.  
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf.  
https://cdn.discordapp.com/attachments/769898609562746880/772885775821439036/Shells_SystemCalls_Signals.ppt.  
https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/.  

## NB:
◊ Maybe you will find some special cases doesn't work, please report if there are any.
