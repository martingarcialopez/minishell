TEST_ARRAY=(
'################		    BUILTINS			#################'
#### PWD ####
'pwd'
'unset PWD ; pwd'
#### ECHO ####
'echo | cat -e'
'echo hola buenos dias | cat -e'
'echo -n hola que tal bocadillo digital | cat -e'
#### ENV ####
'env'
#### EXPORT ####
'export Z=z ; echo $Z'
'export A=a B=b C=c; echo $A$B$C'
'export z zz= zzz=asd ; echo $z$zz$zzz ; env ; export | grep z'
'export _=a; echo $_'
'export A=a=a=a=a=a; echo $A'
'export A B C; echo $A$B$C'
#### UNSET ####
'unset'
'export A=a ; unset A ; echo $A'
'export A=a B=b C=c ; unset A asd B asd ; echo $A$B$C'
#### CD ####
'cd ; pwd'
'unset HOME ; cd ; pwd'
'cd .; pwd'
'cd ..; pwd'
'cd ..; cd - ; pwd; echo $OLDPWD'
'unset OLDPWD; cd - ; pwd; echo $OLDPWD'
'cd ' /'; pwd'
'cd ../../ ; pwd'
'cd ../../../../../../.. ; pwd'
'mkdir -m 500 d ; cd d'
#### EXIT ####
'exit'
'exit 42'
'exit 21 42'
'################		COMMAND EXECUTION	    #################'
'ls'
'/bin/ls'
'./lscp'
'cd dir ; ../lscp'
'cd dir/encoreuneautre ; ../../lscp'
'df -h | head -2'
'idontexist'
'./meneither'
'./d1'
'touch ucantexecme.e ; chmod 000 ucantexecme.e ; ./ucantexecme.e'
#'################		    PARSING		    #################'
#';'
#';;'
#';pwd;pwd;'
#'    pwd ; pwd;    pwd;pwd        ;'
'################		QUOTES			    #################'
'echo "$HOME"'
"echo '\$HOME'"
"echo \" '\$PWD' \\\"\$PWD\\\" '\$PWD' \""
"echo \"\\\$HOME\""
"echo \"'\$'\""
"echo \\\\\n"
"echo \"semicolon will not ; stop me\""
'bash -c "i am not a command" "im the program name"'
'################		PIPES			    #################'
'echo 5 + 3 | bc'
'ls | wc | wc -l | bc'
'echo "cat traveler" | cat | cat | cat | cat | cat | cat'
'################		REDIRECTIONS		    #################'
'> d ; ls'
'pwd > d ; cat d'
'ls > d -l; cat d'
'echo entre el clavel y la rosa > d su majestad es coja; cat d'
'> d echo cucu cantaba la rana; cat d'
'echo "redirection party trick" > d > e > f ; ls ; cat f'
'>> d; ls'
'pwd >> d; cat d'
'echo double the redirection double the fun >> d ; cat d'
'pwd >> d ; echo apendicitis >> d ; cat d'
'pwd >> d ; ls >> d -l ; cat d'
'echo entre el clavel y la rosa >> d su majestad es coja ; cat d'
'>> d echo cucu cantaba la rana; cat d'
'echo "party trick x2" >> d >> e >> f ; ls ; cat f')



GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
YELLOW=$(tput setaf 3)
ROSITA=$(tput setaf 5)
NC=$(tput sgr0)

make

rm -rf a b diff.txt

mkdir dir && mkdir dir/encoreuneautre
printf "%s\n" "creating directories ${ROSITA}dir$NC && ${ROSITA}dir/encoreuneautre$NC from $PWD..."

cp $(which ls) lscp
printf "%s\n" "copying ${ROSITA}$(which ls)$NC to ${ROSITA}lscp$NC..."

printf "\n\t\t\t ${YELLOW}[  MINISHELL UNIT TEST  ]$NC\n\n\n"

for val in "${TEST_ARRAY[@]}"
do
    if [[ "$val" == *####* ]]; then
	printf "%s\n" "${NC}$val"
	continue 
    fi
    bash -c "$val" minishell &> a
    RET1=$?
    rm -rf d e f
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
    rm -rf d e f
done

printf "\n\n\t\t\'cat diff.txt | less\'  for detailed information\n\n"

rm -rf a b d lscp ucantexecme.e dir dir/encoreuneautre
