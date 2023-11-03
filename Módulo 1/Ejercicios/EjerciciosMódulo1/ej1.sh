#!/bin/bash
#Archivo cron_task.sh
	
	find / -ctime -1 >> `date +%Y-%j`

