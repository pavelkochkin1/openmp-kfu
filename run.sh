# !/bin/zsh

############################################################
# Help                                                     #
############################################################
Help()
{
   # Display Help
   echo "Compiling and running .cpp files with openmp library."
   echo
   echo "Syntax: sh run.sh [-h|-f]"
   echo "options:"
   echo "   f     File to compile and run."
   echo "   h     Print this Help."
   echo
   echo "Author: Pavel Kochkin <kochkin27@gmail.com>"
   echo
}

############################################################
############################################################
# Main program                                             #
############################################################
############################################################

while getopts :hf: option;
do
    case $option in
        h) # Display Help
            Help
            exit;;
        f) # Enter a file name
            file_name=$OPTARG;;
        \?) # Invalid option
            exit;;
    esac
done

if [ ! -z "$file_name" ]; then
    clang++ -Xclang -fopenmp -lomp $file_name -o ${file_name%.*}

    ./${file_name%.*}

    rm ${file_name%.*}
fi