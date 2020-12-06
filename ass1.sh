#!/bin/bash

function create {
	read -p "\nEnter filename: " filename
	if [ -f "$filename" ] 
	then
		echo "Database already exists"	
		echo "File contents are:"
		cat $filename
		echo "--------------------------------------------------"
		echo "Check your file below:"
		ls -alps
		echo "--------------------------------------------------"
	else
		echo "Creating a new database"
		touch "$filename"
		echo "|       Name          |           Age       | " >> $filename			    
		echo "New database created!!!"
	fi 
}

function view {
	if [ -f "$filename" ];
	then
		echo "File $filename found"
		echo "Contents of file are:- "
		cat $filename

	else
		echo -e "File not found"
		echo "\n\n"
	fi
}

function insert {
	echo -e "Name of the person: "
	read name
	echo -e "Age of the person: "
	read Age
	echo -e "Do you want to enter these values:"
	echo -e "Name: $name ; Age.: $Age \n"
	echo -e "1/0: "
	read answer
	if [ $answer = "1" ]
	then
		echo -e "$name \t\t\t $Age" >> "$filename"
	else
		echo "Name: $name ; Age: $Age NOT written to book"
	fi	
}

function Delete {
	
	if [ -f "$filename" ];
	then 
		read -p "Enter the name you want to delete:-  " name
		if grep -q $Age $filename
		then
			sed -in "/$name/d" $filename 
			echo -e "Record deleted sucessfully"
		else 
			echo -e "Record not found"
		fi
	else 
		echo -e "file does not exist"
	fi
}

function Modify {
	read -p "Age: " Age
  val=($(grep -i $Age $filename))
  if grep -q $Age $filename
  then
    echo Record Found:
    read -p "New Age: " val[1]
    sed -in "/$Age/d" $filename
    echo ${val[*]} >> $filename
    cat $filename
  else
    echo Record Not Found!
  fi
			
}

 function Search {
	 read -p "Enter the name of record you want to search: " name
	 val = `$(grep -i $name $filename)`
	 if grep -q $name $filename
	 then 
	 	echo -e "record found"
	else 
		echo -e "Record not found"
	fi
}

function menu {
	clear
	echo
	echo -e "\t\t\tAdmin Menu\n"
	echo -e "\t1. Create database"
	echo -e "\t2. view Database"
	echo -e "\t3. insert"
	echo -e "\t4. Delete"
	echo -e "\t5. Modify"
	echo -e "\t6. Search"
	echo -e "\t0. Exit"
	echo -en "\t\tEnter an Option: "
	read -n 1 option
	echo -e ""
}

while [ 1 ]
do
	menu
	case $option in
	0)
	break ;;
	1)
	create ;;

	2)
	view ;;

	3)
	insert ;;
	
	4)
	Delete;;
	
	5)
	Modify;;

	6)
	Search;;

	*)
	clear
	echo "Sorry, wrong selection";;
	esac
	echo -en "\n\n\t\t\tHit any key to continue"
	read -n 1 line
done
clear
