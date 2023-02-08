deps=$(spack dependents $1)
for d in deps
do
    echo $d
done
ls -lah
