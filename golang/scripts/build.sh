
#!/bin/zsh

cd $1
$2 build -o $3 -buildmode c-archive .
cp $3 $4/