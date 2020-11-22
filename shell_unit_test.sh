ARRAY=(
#### EXPORT ####
'export Z=z && echo $Z'
'export A=a && echo $A'
'export A=a B=b C=c; echo $A$B$C'
'export z zz= zzz=asd && echo $z$zz$zzz && env && export | grep z'
'export _=a; echo $_a'
'export A=a=a=a=a=a; echo $A'
'export A=a; echo $A'
'export A B C; echo $A$B$C'
#### UNSET ####
'unset'
'export A=a && unset A && echo $A'
'export A=a B=b C=c && unset A asd B asd ; echo $A$B$C'
#### ECHO ####
'echo | cat -e'
'echo hola buenos dias | cat -e'
'echo -n hola que tal bocadillo digital | cat -e'
#### PWD ####
'pwd'
'cd ; .. pwd'
'cd ../.. ; pwd'
'cd ../../.. ; pwd'
'cd ../../../ ; pwd'
'cd ../../../../ ; pwd'
'cd ../../../../.. ; pwd'
'cd / ; pwd'
'pwd | cat -e'
#### CD ####
'cd'
'cd .; pwd; echo $PWD'
'cd ..; pwd; echo $PWD'
'cd ..; cd - ; pwd; echo $OLDPWD'
'cd ; pwd'
'cd ; echo $PWD; pwd'
'unset OLDPWD; cd - ; pwd; echo $OLDPWD'
'cd ' /'; pwd; echo $PWD'
'mkdir -m 0500 d ; cd d')

make

(rm -f a) && (rm -f b) && (rm -f diff.txt)

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
YELLOW=$(tput setaf 3)
ROSITA=$(tput setaf 5)
NC=$(tput sgr0)

printf "\n\t\t\t ${YELLOW}[ MINISHELL UNIT TEST ]$NC\n\n"

for val in "${ARRAY[@]}"; do
    bash -c "$val" &> a
    RET1=$?
    ./minishell -c "$val" &> b
    RET2=$?
    DIFF=$(diff a b) 
    if [[ "$DIFF" == "" && $RET1 == $RET2 ]]
    then
	printf "%-80s[PASS]$NC\n" "${GREEN}$val"
    else
	printf "%-80s[FAIL]$NC\n" "${RED}$val"
	printf "%s\n" "${YELLOW}$val$NC" >> diff.txt
	printf "$ROSITA< bash       (exited with %d)$NC\n" "$RET1" >> diff.txt
	printf "$ROSITA> minishell  (exited with %d)\n---$NC" "$RET2" >> diff.txt
	diff a b >> diff.txt
	printf "%s\n\n" '---1c1' >> diff.txt
    fi
done

printf "\n\n\t\t\'cat diff.txt | less\'  for detailed information\n\n"

(rm -f a) && (rm -f b) && (rm -rf d)
